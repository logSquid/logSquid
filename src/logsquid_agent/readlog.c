#include "readlog.h"

extern char *LogFileSquid, *PathLog, *MaxMemoryRead, *SleepInterval;
extern int read_rotate, read_tmp;
char *ReadLogFileSquid;

struct File_spec{
    char *name;
    unsigned long size;
};

int check_logfilesquid(){
    debug("Checking the existence of the Squid log file", "readlog::check_logfilesquid");
    
    int count = strlen(LogFileSquid);
    if(count == 0)
        LogFileSquid = "/var/log/squid/access.log";
    
    struct stat f;
    int errcode = stat(LogFileSquid, &f);
    if(errcode == -1){
        logerror(errno, LogFileSquid, "readlog::check_logfilesquid");
        return 0;
    }
    return 1;
}

void *read_logsquid(void *r){
    debug("Read the Squid log file", "readlog::*read_logsquid");
    int status = check_logfilesquid();
    if(status == 0)
        pthread_exit((void *)r);
    check_bytes(0);
    
    pthread_exit((void *)r);
}

void *read_logsquid_tmprotate(void *tr){
    debug("Temporary or rotated file reading", "readlog::*read_logsquid");
    int status = check_logfilesquid();
    if(status == 0)
        pthread_exit((void *)tr);
    
    while(1){
        sleep(60);
        int ctmp = check_tmp();
        if(ctmp > 0)
            system("/usr/local/bin/logsquid_agent -dt");
        check_gz();
        int crotate = check_rotate();
        if(crotate > 0)
            system("/usr/local/bin/logsquid_agent -dr");
    }
    
    pthread_exit((void *)tr);
}

void check_bytes(int rotate){
    debug("Read the Squid log file", "readlog::check_bytes");
    unsigned long maxbytes;
    int count = strlen(MaxMemoryRead);
    if(count == 0)
        maxbytes = 104857600;
    else
        maxbytes = atoi(MaxMemoryRead);
    
    unsigned long readbytes;
    struct File_spec file;
    
    if(rotate > 0)
        file.name = ReadLogFileSquid;
    else
        file.name = LogFileSquid;
    file.size = 1;
    
    while(1){
        struct stat f;
        int status = stat(file.name, &f);
        long totalread  = 0;
        
        if(status == -1)
            logerror(errno, file.name, "readlog::read_logsquid");
        
        if((unsigned long)f.st_size < (unsigned long)file.size)
            file.size = f.st_size;
        
        if((unsigned long)f.st_size > (unsigned long)file.size){
            if((int)file.size == 0 || (int)file.size == 1)
                readbytes = f.st_size;
            else
                readbytes = f.st_size - file.size;
            
            if((unsigned long)readbytes >= (unsigned long)maxbytes)
                totalread = read_parts(&file.name, readbytes, maxbytes);
            else
                totalread = read_full(&file.name, f.st_size);
        }
        if(totalread == -1){
            sleep(atof(SleepInterval));
            continue;
        }
        if((unsigned long)totalread == readbytes)
            file.size = f.st_size;
        
        if(rotate > 0){
            int remove_file = remove(file.name);
            if(remove_file < 0)
                logerror(errno, file.name, "readlog::check_bytes");
            break;
        }
        sleep(atof(SleepInterval));
    }
    return;
}

unsigned long read_full(char **name, unsigned long filesize){
    char msg[50];
    sprintf(msg, "Read Squid log file: %s", *name);
    debug(msg, "readlog::read_full");
    unsigned long ready = 0;
    
    int file = open(*name, O_RDWR);
    if(file <= 0)
        logerror(errno, *name, "readlog::read_full");
    else{
        char *buffer = (char*)malloc((sizeof(char) * filesize));
        if(buffer == NULL){
            logerror(errno, *name, "readlog::read_full");
            close(file);
            return 0;
        }
        if(lseek(file, 0, SEEK_SET) < 0)
            logerror(errno, *name, "readlog::read_full");
        ready = read(file, buffer, filesize);
        if(read_tmp == 0 || read_rotate == 0){
            int trunc;
            if((trunc = ftruncate(file, 0)) != 0){
                logerror(errno, *name, "readlog::read_full");
                close(file);
            }
        }
        
        int _send = sendData(&buffer, ready);
        if(_send < 0){
            debug("Writing buffer in temporary file", "readlog::read_full");
            if(read_tmp == 0 || read_rotate == 0){
                if(strlen(PathLog) == 0)
                    PathLog = "/var/log/logSquid/";
                char filename_tmp[70];
                sprintf(filename_tmp, "%sagent/access.log.tmp", PathLog);

                int filelog_tmp = open(filename_tmp, O_WRONLY | O_CREAT | O_APPEND, 0775);
                if(filelog_tmp < 0)
                    logerror(errno, filename_tmp, "readlog::read_full");
                
                write(filelog_tmp, buffer, ready);
                fflush(stdout);
                close(filelog_tmp);
            }
            else
                write(file, buffer, ready);
        }
        
        free(buffer);
    }
    close(file);
    return ready;
}

unsigned long read_parts(char **name, unsigned long readbytes, unsigned long maxbytes){
    char msg[50];
    sprintf(msg, "Read Squid log file: %s", *name);
    debug(msg, "readlog::read_parts");
    unsigned long totalread = 0;
    int file = open(*name, O_RDONLY);
    if(file == 0)
        logerror(errno, *name, "readlog::get_logsquid");
    else{
        int part = ceil((float)readbytes / (float)maxbytes);
	int i;
        for(i = 1; i <= part; i++){
            if(i == part)
                maxbytes = readbytes - totalread;
            char *buffer = (char*)malloc((sizeof(char) * maxbytes) +1);
            if(buffer == NULL){
                logerror(errno, *name, "readlog::read_parts");
                close(file);
                return 0;
            }
            if(lseek(file, totalread, SEEK_SET) < 0)
                logerror(errno, *name, "readlog::read_parts");
            unsigned long ready = read(file, buffer, maxbytes);
            int _send = sendData(&buffer, ready);
            if(_send < 0){
                close(file);
                return totalread;
            }
            totalread = totalread + ready;
            free(buffer);
        }
    }
    if(readbytes == totalread){
        int trunc;
        if((trunc = ftruncate(file, 0)) != 0)
            logerror(errno, *name, "readlog::read_full");
    }
    close(file);
    return totalread;
}

int check_tmp(){
    debug("Checking temporary files", "readlog::check_tmp");
    if(strlen(PathLog) == 0)
        PathLog = "/var/log/logSquid/";
    char *LogFileTmp = (char*)malloc((sizeof(char) * strlen(PathLog))+20);
    strcpy(LogFileTmp, PathLog);
    strcat(LogFileTmp, "agent/access.log.tmp");
    
    struct stat f;
    int status = stat(LogFileTmp, &f);
    if(status < 0){
        free(LogFileTmp);
        return 0;
    }

    if(f.st_size > 0){
        if(read_tmp > 0){
            debug("Reading temporary files", "readlog::check_tmp");
            ReadLogFileSquid = LogFileTmp;
            check_bytes(1);
            free(LogFileTmp);
            return 0;
        }
        else{
            free(LogFileTmp);
            return 1;
        }
    }
    
    free(LogFileTmp);
    return 0;
}

int check_rotate(){
    debug("Checking for rotated files", "readlog::check_rotate");
    check_gz();
    char *logfile = (char*)malloc((sizeof(char) * strlen(LogFileSquid))+2);
    strcpy(logfile, LogFileSquid);
    strcat(logfile, ".*");
    
    glob_t glob_buffer;
    int i, match_count;
    glob((char * restrict)logfile, 0, NULL, &glob_buffer);
    match_count = glob_buffer.gl_pathc;
    
    if(match_count > 0){
        if(read_rotate > 0){
            debug("Reading rotated files", "readlog::check_rotate");
            for(i=(match_count-1); i>=0; i--){
                ReadLogFileSquid = glob_buffer.gl_pathv[i];
                check_bytes(i+1);
            }
        }
        else{
            globfree(&glob_buffer);
            free(logfile);
            return 1;
        }
    }
        
    globfree(&glob_buffer);
    free(logfile);
    return 0;
}

int check_gz(){
    debug("Checking for GZ files", "readlog::check_gz");
    char *gzfile = (char*)malloc((sizeof(char) * strlen(LogFileSquid))+2);
    strcpy(gzfile, LogFileSquid);
    strcat(gzfile, ".*.gz");
    
    glob_t glob_buffer;
    int i, macth_count;
    glob((char * restrict)gzfile, 0, NULL, &glob_buffer);
    macth_count = glob_buffer.gl_pathc;
    if(macth_count > 0){
        if(read_rotate > 0){
            debug("Decompressing gz files", "readlog::check_gz");
            for(i=(macth_count-1); i>=0; i--){
                char *command = (char*)malloc((sizeof(char) * strlen(LogFileSquid))+11);
                strcpy(command, "gzip -df ");
                strcat(command, glob_buffer.gl_pathv[i]);
                int cmdstatus = system(command);
                if(cmdstatus != 0)
                    logerror(errno, command, "readlog::check_gz");
                free(command);
            }
        }
        else{
            globfree(&glob_buffer);
            return 1;
        }
    }
    globfree(&glob_buffer);
    return 0;
}
