/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   mysql.h
 * Author: marssola
 *
 * Created on 31 de Agosto de 2016, 16:23
 */

#ifndef MYSQL_H
#define MYSQL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#ifdef __APPLE__
    #include <mysql.h>
#else
    #include <mysql/mysql.h>
#endif
#include <time.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <netinet/in.h>
#include <net/if.h>
#include <arpa/inet.h>

#include <sys/stat.h>
#include <unistd.h>
#include <sys/types.h>
#include <unistd.h>

#include "../lib/log.h"
#include "../lib/debug.h"
#include "services.h"

void MYSQL_connect(MYSQL *);
int MYSQL_query(char *, MYSQL *);

void StartSession();
void RenewSession();
void *Session(void *);

void CreateDatabase(char *);
void DropDatabase(char *);

void CreateTable(char *);
void CreateTableSQL(char *);

void DropTable(char *);
void DropTableSQL(char *);

void CreateUser(char *);
void RemoveUser(char *);
void ResetPass(char *);

void CreateUserDatabase();
void RemoveUserDatabase();

void CreateUserServer();
void RemoveUserServer();
void ResetPassServer();

void CreateUserFront();
void RemoveUserFront();
void ResetPassFront();


#endif /* MYSQL_H */

