/* 
 * File:   readlog.h
 * Author: marssola
 *
 */

#ifndef READLOG_H
#define READLOG_H

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/types.h>
#include <unistd.h>
#include <math.h>
#include <fcntl.h>
#include <glob.h>

#include "../lib/log.h"
#include "../lib/debug.h"
#include "agent.h"

/*
 * Função para verificar a existencia do arquivo de log especificado no logsquid_agent.conf
 * Se nenhum arquivo for especificado, define como padrão:
 *  /var/log/squid/access.log
 * Se o arquivo não existir, retorna 0 (erro) para a função read_logsquid()
 */
int check_logfilesquid();

/*
 * Função que executa a check_logfilesquid(), e se o retorno for igual a 0, encerra a função
 * Executa a função check_bytes() para fazer a leitura do arquivo de log e monitorar a entrada de novos dados
 */
void *read_logsquid(void *);

/*
 * Função que é executada pela thread[2] que monitora a existência de arquivos temporários e rotacionados a cada 60 segundos,
 * se existir, executa uma nova instancia do logsquid_agent com o argumento -dt
 */
void *read_logsquid_tmprotate(void *);

/*
 * Função que faz a leitura completa dos arquivos de logs
 * Recebe como parametro o nome do arquivo, quantidade de bytes a serem lidos e o tamanho do arquivo
 * Após ler o arquivo de log, trunca o tamanho do arquivo para 0
 * Utiliza a função malloc() para alocar memória suficiente para a leitura dos bytes especificados no parametro readbytes
 * Recebe o tamanho do arquivo (filesize) como parametro para subtrair com o tamanho de bytes (readbytes) a ser lido, para determinar a posição da leitura com a função lseek()
 * Chama a função sendData(&buffer, ready) com a passagem de parametros: buffer = conteúdo lido do arquivo, ready = total lido em bytes do buffer
 * Se a função sendData retornar um número menor que 0, grava o conteúdo do buffer em um arquivo temporário, que será verficado pela função *read_logsquid_tmprotate()
 * Retorna o tamanho de bytes lidos para conferir
 */
unsigned long read_full(char **name, unsigned long filesize);

/*
 * Função que faz a leitura em partes dos arquivos de logs para evitar sobrecarregar a memória do computador
 * O limite de leitura pode ser definido no arquivo de configuração logsquid_agent.conf
 *  Padrão (100MB): 
 *      MaxMemoryRead = 104857600
 *      O tamanho especificado tem de ser em bytes
 * Após ler o arquivo de log, trunca o tamanho do arquivo para 0
 * Utiliza a função malloc() para alocar memória suficiente para a leitura dos bytes especificados no parametro readbytes
 * Recebe o tamanho máximo (maxbytes) em bytes que pode ser lido para ser dividido pelo tamanho de bytes do arquivo (readbytes), para determinar em quantas vezes será feita a leitura para não sobrecarregar a memória do computador.
 * Chama a função sendData(&buffer, ready) com a passagem de parametros: buffer = conteúdo lido do arquivo, ready = total lido em bytes do buffer
 * Se a função sendData retornar um número menor que 0, grava o conteúdo do buffer em um arquivo temporário, que será verficado pela função *read_logsquid_tmprotate()
 * Retorna o tamanho de byets lidos para conferir
 */
unsigned long read_parts(char **name, unsigned long readbytes, unsigned long maxbytes);

/*
 * Função que verifica se o arquivo de log sofreu alguma alteração - se foi escrito mais bytes
 * Recebe como parametro um número maior que 0 para determinar a leitura dos arquivos de logs rotacionados / temporários. Se 0 for especificado, fará a leitura do arquivo de log principal
 * Mantem um loop infinito com tempo especificado no arquivo de configuração logsquid_agent.conf:
 *  Padrão (segundos):
 *      SleepInterval = 1
 * No loop é feito a verificação do tamanho do arquivo com a função stat, e se for maior do que a leitura anterior, chama a função read_parts, quando ultrapassa o tamanho de bytes especificado no arquivo de configuração logsquid_agent.conf, ou a leitura completa com a função read_full()
 * Recebe o total de bytes lidos com a função read_parts() e read_full, para comparar com o tanto de bytes determinados para a leitura, se forem iguais, atualiza o struct file.size para o tamanho de bytes lidos.
 * Se rotate for diferente de 0, após a leitura do arquivo de log, sai do loop e encerra a função
 */
void check_bytes(int rotate);

/*
 * Função que verifica a existencia de arquivos temporários
 * Se existir, executa a função check_bytes() com o parametro 1, indicando a leitura de arquivos temporários.
 * Arquivos temporários são gerados assim que o Agente perde a comunicação com o Server.
 */
int check_tmp();

/*
 * Função que verifica a existencia de arquivos rotacionados
 * Se existir, executa a função check_bytes() com o numero de arquivos como parametro
 */
int check_rotate();

/*
 * Função que verifica a existencia de arquivos rotacionados compactados (com a extensão .gz)
 * Se existir arquivos rotacionados compactados, descompacta com gzip -df nome_do_arquivo.gz
 */
int check_gz();

#endif /* READLOG_H */

