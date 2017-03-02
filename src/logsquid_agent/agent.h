/* 
 * File:   agent.h
 * Author: marssola
 *
 * Created on 31 de Agosto de 2016, 11:39
 */

#ifndef AGENT_H
#define AGENT_H

#include <sys/types.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <pthread.h>

#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <resolv.h>
#include <netdb.h>
#include <arpa/inet.h>

#include "../lib/log.h"
#include "../lib/debug.h"

/*
 * Função que cria conexão com o Server
 * Obtém o IP (Server) e a Porta (ServerPort) do Server no arquivo de configuração logsquid_agent.conf
 * Se nenhuma porta for definida no arquivo de configuração, será utilizada a porta 8213
 */
void createConnection();

/*
 * Função que encerra a conexão com o Server
 */
void closeConnection();

/*
 * Função para enviar o buffer da leitura dos arquivos de log
 * Recebe dois parametros:
 *  **buffer = conteúdo do arquivo lido
 *  bytes = total de bytes lido
 */
int sendData(char **, int);

/*
 * Função que verifica se a conexão com o Server ainda está ativa
 * Caso contrário retorna -1
 */
void checkSocket();

/*
 * Função que é executada pela thread[0]
 * Executa a função createConnection() e cria uma nova thread que executa a função *waitResponse(), que aguarda uma resposta do Server de encerramento.
 * Se cair a conexão com o Servidor, aguarda 60 segundos para tentar uma nova conexão
 */
void *connectServer(void *);

/*
 * Função que é executada pela função *connectServer()
 * Fica aguardando uma resposta do Server, sinal de encerramento da conexão.
 */
void *waitResponse(void *);

#endif /* AGENT_H */

