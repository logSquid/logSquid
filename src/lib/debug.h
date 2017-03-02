/* 
 * File:   debug.h
 * Author: marssola
 *
 */

#ifndef DEBUG_H
#define DEBUG_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <time.h>

#include <errno.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

#include "../lib/log.h"

/*
 * Função que registra os passos no arquivo debug.log na pasta de logs.
 * Padrão: /var/log/logSquid/debug.log
 * Parametros:
 *  *string com descrição na função
 *  *modulo que está sendo executado no momento
 */
void debug(char *_str, char *_mod);

#endif /* DEBUG_H */

