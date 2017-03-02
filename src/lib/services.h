/* 
 * File:   services.h
 * Author: Mauro Marssola
 *
 * Created on 13 de Dezembro de 2016, 16:06
 */

#ifndef SERVICES_H
#define SERVICES_H

#include <gcrypt.h>
#include <string.h>
#include <errno.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <termios.h>

#include "../lib/log.h"
#include "../lib/debug.h"

char *sha1(char *);

char *getIPaddr();

int getch(void);

void flush_in();

char *getIP();

char *getUser(char *);

char *getPass(char *);

char *getDatabase(char *);

#endif /* SERVICES_H */

