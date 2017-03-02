/*
 * File:   logsquid_config.c
 * Author: Mauro Marssola
 *
 * Created on 15 de Dezembro de 2016, 10:40
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../lib/config.h"
#include "../lib/log.h"
#include "../lib/debug.h"
#include "../lib/daemon.h"
#include "../lib/lmysql.h"

#include <confuse.h>
#include <getopt.h>

struct option config_options[] = {
    {"help", 0, NULL, 'h'},
    {"create-database", 1, NULL, 'C'},
    {"drop-database", 1, NULL, 'c'},
    {"create-table", 1, NULL, 'T'},
    {"drop-table", 1, NULL, 't'},
    {"create-user", 1, NULL, 'U'},
    {"drop-user", 1, NULL, 'u'},
    {0, 0, 0, 0}
};

void Help(){
    fprintf(stdout, "Usage: %s [PARAMETERS] [OPTIONS]\n", __progname);
    fprintf(stdout, "Configuration of Database and users for logSquid.\n");
    fprintf(stdout, "The required arguments:\n");
    fprintf(stdout, "\
    --create-database           Create database with the desired name (default: logSquid)\n\
                                    e.g: %s --create-database [NAME]\n\
    --drop-database             Remove database (default: logSquid)\n\
                                    e.g: %s --drop-database [NAME]\n\
    --create-table              Create tables for logSquid\n\
                                options:\n\
                                    [all]:      create all the necessary tables\n\
                                    [agents]:   create table for agents registration\n\
                                    [logSquid]: create squid log table\n\
                                    [servers]:  create table for servers registration\n\
                                    [users]:    create table of frontend users\n\
                                    e.g: %s --create-table [OPTION]\n\
                                *The tables is on the directory '/usr/share/logSquid/config/database/', and can be edited if necessary\n\
    --drop-table                Removes one or all tables\n\
                                options:\n\
                                    [all]:      remove all tables\n\
                                    [agents]:   remove table agents\n\
                                    [logSquid]: remove table logSquid\n\
                                    [servers]:  remove table servers\n\
                                    [users]:    remove table users\n\
                                    e.g: %s --drop-table [OPTION]\n\
    --create-user               Create user\n\
                                options:\n\
                                    [database]: create user for login on the database\n\
                                    [frontend:] Create user for frontend login\n\
                                    e.g: %s --create-user [OPTION]\n\
    --drop-user                 Remove users\n\
                                options:\n\
                                    [database]: remove user for login on the database\n\
                                    [frontend:] remove user for frontend login\n\
                                    e.g: %s --drop-user [OPTION]\n\
    --reset-password            Reset Password\n\
                                options:\n\
                                    [frontend:] reset frontend users password\n\
                                    e.g: %s --reset-password [OPTION]\n\
\n\
", __progname, __progname, __progname, __progname, __progname, __progname, __progname);
    
    
}

void getOptionsConfig(int argc, char **argv){
    int optc;
    while((optc = getopt_long(argc, argv, "h", config_options, NULL)) != -1){
        switch(optc){
            case 'C':
                CreateDatabase(optarg);
                break;
            case 'c':
                DropDatabase(optarg);
                break;
            case 'T':
                CreateTable(optarg);
                break;
            case 't':
                DropTable(optarg);
                break;
            case 'U':
                CreateUser(optarg);
                break;
            case 'u':
                RemoveUser(optarg);
                break;
            case 'R':
                ResetPass(optarg);
                break;
            case 'h':
                Help();
                break;
            default:
                exit(1);
        }
    }
}

int main(int argc, char** argv) {
    
    lgsqd_load_config();
    getOptionsConfig(argc, argv);
    daemon_start();
    
    
    
    return (EXIT_SUCCESS);
}

