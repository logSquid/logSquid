/* 
 * File:   daemon.h
 * Author: marssola
 *
 * Created on 26 de Julho de 2016, 14:40
 */

#ifndef DAEMON_H
#define DAEMON_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pwd.h>
#include <errno.h>

#include "log.h"

extern char *__progname;

void daemon_start();

#endif /* DAEMON_H */

