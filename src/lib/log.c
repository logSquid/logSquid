#include "log.h"

char _fileerror[50];

void check_pathlog(){
    extern char *PathLog;
    int count = strlen(PathLog);
    if(count == 0)
        PathLog = "/var/log/logSquid/";

    DIR *pathlog = opendir(PathLog);
    if(pathlog == NULL){
        printf("%s - %s\n", strerror(errno), PathLog);
        exit(1);
    }
    closedir(pathlog);
}

void logerror(int _errno, char *_str, char *_mod){
    check_pathlog();
    extern char *PathLog;
    sprintf(_fileerror, "%serror.log", PathLog);
    
    int file = open(_fileerror, O_WRONLY | O_CREAT, 0775);
    if(file < 0){
        printf("Could not create the log file: %s - %s\n", strerror(errno), _fileerror);
        close(file);
        exit(1);
    }
    else
        close(file);
    
    FILE *logfile;
    logfile = fopen(_fileerror, "a+");
    if(logfile == NULL){
        printf("Could not create the log file: %s - %s\n", strerror(errno), _fileerror);
        fclose(logfile);
        exit(1);
    }
    if(_errno == -1){
        if(!fprintf(logfile, "%d [%s] %s\n", (int)time(NULL), _mod, _str)){
            printf("Could not write the log: %s\n", strerror(errno));
            fclose(logfile);
            exit(1);
        }
    }
    else if(!fprintf(logfile, "%d [%s] %s %s\n", (int)time(NULL), _mod, strerror(_errno), _str)){
        printf("Could not write the log: %s\n", strerror(errno));
        fclose(logfile);
        exit(1);
    }
    fclose(logfile);
    
}
