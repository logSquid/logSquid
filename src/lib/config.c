#include "config.h"

struct option long_options[] ={
    {"conf", 1, NULL, 'c'},
    {"debug", 0, NULL, 'd'},
    {"help", 0, NULL, 'h'},
    {"version", 0, NULL, 'v'},
    {"read-rotate", 0, NULL, 'r'},
    {"read-tmp", 0, NULL, 't'},
    {0, 0, 0, 0}
};


char    *ServerPort = NULL, 
        *ListenAgents = NULL, 
        *ListenPort = NULL, 
        *ServerDB = NULL, 
        *ServerPortDB = NULL, 
        *UsernameDB = NULL, 
        *PasswordDB = NULL,
        *NameDB = NULL,
        *Server = NULL, 
        *PathLog = NULL,
        *ConfFile = NULL,
        *TypeLog = NULL,
        *LogFileSquid = NULL,
        *MaxMemoryRead = NULL,
        *SleepInterval = NULL,
        *Username = NULL;

int     debug_mode = 0;
int     read_rotate = 0, read_tmp;

cfg_t *cfg;

void lgsqd_agent_load(){
    cfg_opt_t agent[] = {
        CFG_SIMPLE_STR("Server", &Server),
        CFG_SIMPLE_STR("ServerPort", &ServerPort),
        CFG_SIMPLE_STR("PathLog", &PathLog),
        CFG_SIMPLE_STR("LogFileSquid", &LogFileSquid),
        CFG_SIMPLE_STR("MaxMemoryRead", &MaxMemoryRead),
        CFG_SIMPLE_STR("SleepInterval", &SleepInterval),
        CFG_SIMPLE_STR("Username", &Username),
        CFG_END()
    };
    cfg = cfg_init(agent, CFGF_NONE);
    if(cfg_parse(cfg, ConfFile) == -1){
        fprintf(stderr, "Configuration file was not found: %s\n", ConfFile);
        exit(-1);
    }
    return;
}
void lgsqd_server_load(){
    cfg_opt_t server[] = {
        CFG_SIMPLE_STR("ServerPort", &ServerPort),
        CFG_SIMPLE_STR("ListenAgents", &ListenAgents),
        CFG_SIMPLE_STR("Username", &Username),
        CFG_SIMPLE_STR("ServerDB", &ServerDB),
        CFG_SIMPLE_STR("ServerPortDB", &ServerPortDB),
        CFG_SIMPLE_STR("UsernameDB", &UsernameDB),
        CFG_SIMPLE_STR("PasswordDB", &PasswordDB),
        CFG_SIMPLE_STR("NameDB", &NameDB),
        CFG_SIMPLE_STR("PathLog", &PathLog),
        CFG_SIMPLE_STR("TypeLog", &TypeLog),
        CFG_END()
    };
    
    cfg = cfg_init(server, CFGF_NONE);
    if(cfg_parse(cfg, ConfFile) == -1){
        fprintf(stderr, "Configuration file was not found: %s\n", ConfFile);
        exit(-1);
    }
    return;
}

void check_ConfFile(char *file){
   struct stat s;
   int status = stat(file, &s);
   if(status == -1){
       fprintf(stderr, "Configuration file was not found: %s\n", file);
       exit(-1);
   }
   ConfFile = file;
}

void lgsqd_help_agent(){
    fprintf(stdout, "Usage: %s [PARAMETERS] [OPTIONS]\n", __progname);
    fprintf(stdout, "Squid's logs Collector.\n");
    fprintf(stdout, "Options:\n\
    short   long\n\
    -c      --conf          Indicate different configuration file\n\
                             %s [PARAMETER] [OPTION]\n\
                             e.g: %s --conf /path/logsquid_agent.conf\n\
                             default: /usr/local/etc/logSquid/logsquid_agent.conf\n\
    -d      --debug         Run in debug mode\n\
                             %s [PARAMETER]\n\
                             e.g: %s --debug\n\
                             view logs debug mode: /var/log/logSquid/debug.log\n\
    -r      --read-rotate   Reading rotated logs\n\
                             %s [PARAMETER]\n\
                             e.g: %s --read-rotate\n\
    -t      --read-tmp      Reading temporary logs\n\
                             %s [PARAMETER]\n\
                             e.g: %s --read-tmp\n\
    -v      --version       Display version number\n\
\n\
Default settings:\n\
    Installation path:          /usr/local/bin/\n\
    Log path:                   /var/log/logSquid/\n\
    Settings path:              /usr/local/etc/logSquid/\n\
\n\
 Run logsquid_config to configure the logSquid server\n\
 For more information, see: logsquid_config --help\n\
\n\
", __progname, __progname, __progname, __progname, __progname, __progname, __progname, __progname);
    exit(0);
}

void lgsqd_help_server(){
    fprintf(stdout, "Usage: %s [PARAMETERS] [OPTIONS]\n", __progname);
    fprintf(stdout, "Squid's logs in a database server.\n");
    fprintf(stdout, "Options:\n\
    short   long\n\
    -c      --conf          Indicate different configuration file\n\
                             %s [PARAMETER] [OPTION]\n\
                             e.g: %s --conf /path/logsquid_server.conf\n\
                             default: /usr/local/etc/logSquid/logsquid_server.conf\n\
    -d      --debug         Run in debug mode\n\
                             %s [PARAMETER]\n\
                             e.g: %s --debug\n\
                             view logs debug mode: /var/log/logSquid/debug.log\n\
    -v      --version       Display version number\n\
\n\
Default settings:\n\
    Installation path:          /usr/local/bin/\n\
    Log path:                   /var/log/logSquid/\n\
    Settings path:              /usr/local/etc/logSquid/\n\
\n\
 Run logsquid_config to configure the logSquid server\n\
 For more information, see: logsquid_config --help\n\
\n\
", __progname, __progname, __progname, __progname);
    exit(0);
}

void lgsqd_load_config(void){
    if(strcmp(__progname, "logsquid_server") == 0 || strcmp(__progname, "logsquid_config") == 0){
        if(ConfFile == 0)
            ConfFile = "/usr/local/etc/logSquid/logsquid_server.conf";
        lgsqd_server_load();
    }
    else if(strcmp(__progname, "logsquid_agent") == 0){
        if(ConfFile == 0)
            ConfFile = "/usr/local/etc/logSquid/logsquid_agent.conf";
        lgsqd_agent_load();
    }
    return;
}

void getParameters(int argc, char **argv){
    int optc;
    while((optc = getopt_long(argc, argv, "hvdrtc:D:T:U:R:", long_options, NULL)) != -1){
        switch(optc){
            case 'c':
                check_ConfFile(optarg);
                break;
            case 'd':
                debug_mode = 1;
                break;
            case 'r':
                read_rotate = 1;
                break;
            case 't':
                read_tmp = 1;
                break;
            case 'h':
                if(strcmp(__progname, "logsquid_server") == 0)
                    lgsqd_help_server();
                else if(strcmp(__progname, "logsquid_agent") == 0)
                    lgsqd_help_agent();
                break;
            case 'v':
                if(strcmp(__progname, "logsquid_server") == 0)
                    fprintf(stdout, "%s 2.0 (beta)\n", __progname);
                else if(strcmp(__progname, "logsquid_agent") == 0)
                    fprintf(stdout, "%s 2.0 (beta)\n", __progname);
                fprintf(stdout, "Copyright (c) 2016-2017 Vantage Brazil. All rights reserved. \n");
                exit(0);
                break;
            default:
                exit(1);
        }
    }
    
    return;
}
