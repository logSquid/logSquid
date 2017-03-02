/* 
 * File:   logsquid_agent.c
 * Author: Mauro Marssola
 *
 * Created on 6 de Julho de 2016, 14:52
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pwd.h>
#include <pthread.h>

#include "../lib/config.h"
#include "../lib/log.h"
#include "../lib/debug.h"
#include "../lib/daemon.h"

#include "agent.h"
#include "readlog.h"

pthread_t main_threads[4];
int main(int argc, char **argv) {
            
    getParameters(argc, argv);
    lgsqd_load_config();
    daemon_start();
    
    extern int read_rotate, read_tmp;
    if(read_rotate > 0 || read_tmp > 0){
        createConnection();
        checkSocket();
        if(read_rotate > 0)
            check_rotate();
        if(read_tmp > 0)
            check_tmp();
        closeConnection();
    }
    else{
        pthread_create(&(main_threads[0]), NULL, connectServer, NULL);
        pthread_create(&(main_threads[1]), NULL, read_logsquid, NULL);
        pthread_create(&(main_threads[2]), NULL, read_logsquid_tmprotate, NULL);

        pthread_join(main_threads[0], NULL);
        pthread_join(main_threads[1], NULL);
        pthread_join(main_threads[2], NULL);
    }
    
    return 0;
}

