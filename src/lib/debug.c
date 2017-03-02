/* 
 * File:   debug.h
 * Author: marssola
 *
 */

#include "debug.h"

char _filedebug[50];

void debug(char *_str, char *_mod){
    extern int debug_mode;
    extern char *PathLog;
    if(debug_mode == 0)
        return;
    
    check_pathlog();
    sprintf(_filedebug, "%sdebug.log", PathLog);

    int file = open(_filedebug, O_WRONLY | O_CREAT, 0775);
    if(file < 0){
        printf("Could not create the debug file: %s - %s\n", strerror(errno),_filedebug);
        logerror(errno, _filedebug, "debug");
        close(file);
        exit(1);
    }
    else
        close(file);
    
    FILE *logdebug;
    logdebug = fopen(_filedebug, "a+");
    if(logdebug == NULL){
        printf("Could not create the debug file: %s - %s\n", strerror(errno),_filedebug);
        logerror(errno, _filedebug, "debug");
        exit(1);
    }
    
    if(!fprintf(logdebug, "%d [%s] %s\n", (int)time(NULL), _mod, _str)){
        printf("Could not write the file debug: %s\n", strerror(errno));
        logerror(errno, _filedebug, "debug");
        exit(1);
    }
    fclose(logdebug);
}

