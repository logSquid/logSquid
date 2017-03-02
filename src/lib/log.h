/* 
 * File:   log.h
 * Author: Mauro Marssola
 *
 */

#ifndef LOG_H
#define LOG_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <dirent.h>
#include <time.h>

#include <errno.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

#include "daemon.h"

extern char *__progname;

/*
 * Função que verifica se a pasta de log foi definido no conf e se existe no sistema de arquivos.
 * Caso não foi definido, é aplicado o endereço padrão para a variavel PathLog
 * Caminho Padrão: /var/etc/logSquid
 */
void check_pathlog();

/*
 * Função para gravar os erros em um arquivo de log
 * Padrão: /var/log/logSquid/error.log
 * Parametros:
 *  valor inteiro da função errno, 
 *  *string como complemento da função errno,
 *  *modulo em qual foi gerado o erro
 *      ao receber o inteiro da função errno, é convertido para a string corresponde do padrão GNU com a função strerror(errno)
 */
void logerror(int , char *, char *);

#endif /* LOG_H */

