/* 
 * File:   server.h
 * Author: marssola
 *
 * Created on 24 de Agosto de 2016, 16:56
 */

#ifndef SERVER_H
#define SERVER_H

#include <sys/types.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <stddef.h>
#include <fcntl.h>
#include <glob.h>
#include <sys/stat.h>
#include <pthread.h>
#include <time.h>

#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <netinet/tcp.h>
#include <arpa/inet.h>
#include <resolv.h>
#include <mysql/mysql.h>

#include "../lib/log.h"
#include "../lib/debug.h"
#include "../lib/lmysql.h"

/*  ************** Structs ************** 
 * 
 * Struct hosts_connected
 *  ip = Endereço de IP do Agente
 *  port = Número da Porta que o Agente utilizou para se conectar com o Servidor
 *  conn = Número do Socket da conexão do Server com o Agente, caso não esteja mais conectado, será definido valor 0
 *  listen = indica que a função *listenAgent (thread) está ativa. Quando se encerra a conexão com o Agente, esse função é encerrada, finalizando a thread, com isso o valor é setado para 0
 *  write = indica que a função *writedbAgent (thread) está ativa. Quando se encerra a conexão com o Agente, e não possui mais arquivos de logs correspondentes ao Agente, essa função é encerrada, finalizando a thread, com isso o valor é setado para 0
 *  action = variável que indica que a thread *listenAgent está atuando (recebendo dados do Agente e armazenando o buffer em arquivo), evitando que a thread *writedbAgent edite o arquivo que está sendo recebido pelo Agente
 * 
 * Struct list_agents
 *  id  = ID do Agente gravado no Banco de Dados
 *  ip  = Endereço de IP do Agente gravado no Banco de Dados
 * 
 * Struct default_squid
 *  timestamp, elapsed, ipaddress, codestatus, bytes, method, url, hierarchy, username, mime
 *      Variáveis que vão receber o conteúdo de cada linha do agente, para que possa ser gravada no Banco de Dados.
 * É possível criar uma Struct personalizada de acordo com o logformat do seu Squid.
 * Basta indicar o nome da variável e o tamanho, separados por vírgula
 * 
 * Struct default_logSquid
 *  timestamp, ipaddress, macaddress, username, serverfqn, url, ipdest, mime, bytes, codestatus
 *      Variáveis que vão receber o conteúdo de cada linha enviado pelo agente, para ser gravado no Banco de Daodos.
 *  Padrão de logs logSquid
 * 
 *  ************** Fim Structs ************** */

/*
 * Função para criar um Socket de rede na porta (ServerPort) especificada no arquivo de configuração logsquid_server.conf. 
 *  Caso nenhuma porta tenha sido especificada, será utilizada a porta padrão: 8213
 */
void createSocket();

/*
 * Função que faz a ligação do Socket de rede com a struct sockaddr
 */
void startBind();

/*
 * Função que prepara o Socket de rede para escutar a solicitação do agente
 */
void startListen();

/*
 * Função que lista todas as conexões feitas (ativas / inativas)
 */
int listAgent(char *);

/*
 * Função para escrita no Banco de Dados
 * Parametros:
 *  lines = indica o início da leitura do arquivo, se 0, inicia a leitura do arquivo completo. Caso a gravação no Banco de Dados tenha sido interrompida, será continuada de onde parou
 *      Informação da linha se encontra no arquivo access_agent_ip_porta.log.stat, primeira coluna
 *  ip = endereço de ip do Agente, necessário para determinar:
 *      *Qual arquivo será lido
 *      *Criação do arquivo *.stat
 *  port = porta de comunicação do Agente, necessário para determinar:
 *      *Qual arquivo será lido
 *      *Criação do arquivo *.stat
 *          necessário para distinguir qual arquivo a função deve ler
 * Executa a função MYSQL_connect() para criar uma conexão com o Banco de Dados
 * Faz a leitura do arquivo de log especificado (nome do arquivo é formado pelo Endereço de IP e Porta do Agente) linha por linha (fgets()), e utiliza a função strtok_r() para armazenar cada coluna em sua respectiva variável
 * Executa a função MYSQL_query() para gravar no Banco de Dados
 *  Caso retorne um número maior que 0 (erro), escreve no arquivo o conteúdo do buffer lido do arquivo de log em um arquivo chamado access_agent_ip_porta.log.err
 * Grava no arquivo access_agent_ip_porta.log.stat o número da linha que o server já fez a leitura, Endereço de IP e Porta
 * Remove o arquivo access_agent_ip_port.log.tmp
 */
void write_db(int lines, char ip[16], int port);

/*
 * Função que verifica a existência de arquivos *.stat
 * Se existir:
 *  Lê o arquivo e obtém três variaveis:
 *      Número_linhas Endereço_IP Porta_Agente
 *  Executa a função write_db(lines, ip, port) para continuar a gravação no Banco de Dados de onde parou
 */
void check_lt_start();

/*
 * Função que verifica a existência de arquivos *.log e *.tmp, se estão vazios, remove-os
 * Se o Agente encerrou a conexão com o Server, a thread listen_thread[n] foi encerrada
 * Se a thread listen_thread[n] não recebeu nenhum byte de logs, o arquivo access_agent_ip_port.log ainda continua existindo, com isso, a thread writedb_thread[n] não se encerra.
 * Removendo o arquivo *.log vazio, a thread writedb_thread se encerra.
 */
void check_lt();

/*
 * Função que verifica a existencia de arquivos *.log que não estão vazios
 * Se o arquivo não estiver vazio, checa se o existe algum agente conectado com o IP e Porta especificado no nome do arquivo,
 * se não tiver, obtém o IP e a Porta no nome do arquivo, renomeia para *.log.tmp e cria um arquivo *.stat para ser gravado no Banco de Dados
 */
void check_lt_log();

/*
 * Função que é executada pela thread[0]
 * Aguarda a solicitação de conexão dos Agentes
 * Recebe do arquivo de configuração (logsquid_server.conf) a variavel ListenAgents
 *  Se o tamanho da variavel for diferente de 0
 *      Verifica se o Agente que está solicitando conexão está nesta lista
 *  Se for igual  0 Zero
 *      Aceita a conexão de qualquer agente
 * Realoca memória para a Struct host (Contém Informações sobre o Agente - Veja Struct hosts_connected)
 * Cria uma thread com a função *writedbAgent(id) com o número do host
 * Cria uma thread com a função *listenAgent(id) com o número do host
 * - Aguarda uma nova conexão
 */
void *waitRequest(void *);

/*
 * Função que é executada pela thread *waitRequest() para cada Agente
 * Enquanto a variavel hosts[n].conn for diferente de 0
 *  Recebe do Agente os logs
 *  Armazena o buffer em um arquivo com o seguinte nome access_agent_ip_port.log
 *      ip = host[n].ip
 *      port = host[n].port
 *  Enquanto está recebendo os logs do Agente e gravando o buffer no arquivo, a variavel host[n].action é setada para 1, para que a thread *writedbAgent() não interrompa a gravação do arquivo
 */
void *listenAgent(void *);

/*
 * Função que é executada pela thread *waitRequest() para cada Agente
 * Cria o arquivo access_agent_ip_port.log para a função *listenAgent(id) gravar o conteúdo do buffer
 *      ip = host[n].ip
 *      port = host[n].port
 * Se não conseguir criar o arquivo
 *  Envia um sinal de cancelamento para a thread listen_thread[n]
 *  Retorna (void*)NULL
 * 
 * Entra em um loop infinito
 * Verifica a existencia do arquivo de log
 *  Se não existir e a variavel host[n].conn for igual a 0
 *      define o valor 0 para a variavel host[n].write
 *      Sai do loop, encerrando a thread
 * Verifica se o tamanho do arquivo for difente que o tamanho da ultima leitura (size_f) e se host[n].action for igual a 0
 *  Renomeia o arquivo access_agent_ip_port.log para access_agent_ip_port.log.tmp
 *  Executa a função write_db() com os seguintes parametros:
 *      0 = indica que a leitura do arquivo deve ser feita do inicio
 *      host[n].ip = endereço de ip do agente, para formar o nome do arquivo na função
 *      host[n].port = porta que o agente utilizou para se conectar com o Server, para formar o nome do arquivo na função
 *  Após encerrar a função write_db(), armazena o tamanho do buffer lido para a variavel size_f
 * Retorna para o loop
 */
void *writedbAgent(void *);

/*
 * Função que consulta todos os agentes cadastrados na tabela agents
 * Armazena na struct list_agents o ID e o Endereço de IP
 */
void getAgents();

/*
 * Recebe o Endereço de IP do Agente
 * Retorna o ID do agent armazenado na struct list_agents
 * Retorna 0 caso o agente não esteja na lista
 */
int getIdAgent(char ip_agent[16]);

/*
 * Recebe o Endereço de IP do Agente
 * Checa se o Endereço de IP do Agente que se conectou no Server está registrado na Tabela agents
 * Se não estiver, Executa a função setAgent com o Endereço de IP como parametro
 */
void checkAgent(char ip_agent[16]);

/*
 * Recebe o Endereço de IP do Agente
 * Grava na Tabela agents o endereço de IP do Agente que se conectou no Server
 */
void setAgent(char ip_agent[16]);

/*
 * Função que é executada pela thread[1]
 * Ao iniciar, verifica a existencia de arquivos *.stat, para continuar a gravação no Banco de Dados de onde parou
 * Entra em um loop infinito
 *  Executa a função check_lt()
 */
void *garbageCollector(void *g);

/*
 * Recebe como parametro *char, char
 *  *char   = Ponteiro que sera pesquisado
 *  char    = caracteres que serão pesquisados no *char
 * Retorna 1 se encontrar o conteúdo de char
 * Retorn 0 se não encontrar o conteúdo de char
 */
ptrdiff_t index_of(const char *, char);

/*
 * Recebe como parametro um char*
 * Procura pelo caracter \t ou \n e remove-os da string
 */
void strip(char *);

/*
 * Recebe como parametro um char*
 * Procura pelo caracter \' e substitui por "-"
 */
void strip_quot(char *);

#endif /* SERVER_H */

