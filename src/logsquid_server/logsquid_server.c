/* 
 * File:   logsquid_server.c
 * Author: Mauro Marssola
 *
 * Created on 6 de Julho de 2016, 14:52
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../lib/config.h"
#include "../lib/log.h"
#include "../lib/debug.h"
#include "../lib/daemon.h"

#include <sys/types.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <pthread.h>

#include "server.h"
#include "../lib/lmysql.h"

pthread_t main_threads[2];

int main(int argc, char** argv)
{
    
    getParameters(argc, argv);
    lgsqd_load_config();
    daemon_start();
    
    //StartSession();
    
    createSocket();
    startBind();
    startListen();
    
    //getAgents();
    
    pthread_create(&(main_threads[0]), NULL, waitRequest, NULL);
    pthread_create(&(main_threads[1]), NULL, garbageCollector, NULL);
    //pthread_create(&(main_threads[2]), NULL, Session, NULL);
    
    pthread_join(main_threads[0], NULL);
    pthread_join(main_threads[1], NULL);
    //pthread_join(main_threads[2], NULL);
    
    return (EXIT_SUCCESS);
}

