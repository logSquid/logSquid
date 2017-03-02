#include "daemon.h"

extern char *Username;
extern int read_rotate, read_tmp;
struct passwd   *pwd;

void daemon_start(){
    int user = strlen(Username);
    if(strcmp(__progname, "logsquid_server") == 0 || strcmp(__progname, "logsquid_config") == 0){
        if(user == 0){
            pwd = getpwnam("logsquid");
            if(pwd == NULL){
                logerror(-1, "logSquid user was not created", "daemon::daemon_start");
            }
        }
        else
            pwd = getpwnam(Username);
    }
    else if(strcmp(__progname, "logsquid_agent") == 0){
        if(user == 0){
            pwd = getpwnam("squid");
            if(pwd == NULL){
                pwd = getpwnam("proxy");
                if(pwd == NULL){
                    logerror(-1, "Squid was not installed", "daemon::daemon_start");
                    exit(0);
                }
            }
        }
        else
            pwd = getpwnam(Username);
    }
    
    if(0 == pwd->pw_uid){
        char error[50];
        sprintf(error, "cannot run as %s", Username);
        logerror(-1, error, "daemon::daemon_start");
        exit(0);
    }
    
    if(read_tmp == 0 || read_rotate == 0 || strcmp(__progname, "logsquid_config") != 0){
        char filename_pid[20], pid[10];
        sprintf(filename_pid, "/tmp/%s.pid", __progname);
        sprintf(pid, "%d", getpid());

        int file_pid = open(filename_pid, O_RDWR | O_CREAT, 0775);
        if(file_pid < 0)
            logerror(errno, filename_pid, "daemon::daemon_start");
        write(file_pid, pid, strlen(pid));
        close(file_pid);
    }

    setuid(pwd->pw_uid);
    
    return;
}
