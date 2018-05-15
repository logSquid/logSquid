/* 
 * File:   server.c
 * Author: marssola
 *
 * Created on 24 de Agosto de 2016, 16:55
 */

#include "server.h"

extern char *ServerPort, *PathLog, *ListenAgents, *TypeLog;
extern int id_user_session;

struct hosts_connected
{
    char ip[16];
    int port, conn, listen, write, action;
} *host;

struct list_agents
{
    int id;
    char ip[16];
} *agent;

struct default_squid
{
    char    timestamp[16], elapsed[16], ipaddress[16], codestatus[50], bytes[16], method[50],
    url[2049], hierarchy[50], username[50], mime[50];
};

struct default_logSquid
{
    char    timestamp[16], ipaddress[16], macaddress[18], username[50], serverfqn[101], url[2049],
    ipdest[50], mime[50], bytes[16], codestatus[50];
};

struct squid_logs_format
{
    char gt_a[16];                      //Client source IP address
    char gt_A[16];                      //Client FQDN
    char gt_p[10];                      //Client source port
    char gt_eui[18];                    //Client source EUI (MAC address, EUI-48 or EUI-64 identifier)
    char gt_la[16];                     //Local IP address the client connected to
    char gt_lp[10];                     //Local port number the client connected to
    char gt_qos[20];                    //Client connection TOS/DSCP value set by Squid
    char gt_nfmark[20];                 //Client connection netfilter mark set by Squid

    char la[16];                        //Local listening IP address the client connection was connected to.
    char lp[10];                        //Local listening port number the client connection was connected to.

    char lt_a[16];                      //Server IP address of the last server or peer connection
    char lt_A[16];                      //Server FQDN or peer name
    char lt_p[10];                      //Server port number of the last server or peer connection
    char lt_la[16];                     //Local IP address of the last server or peer connection
    char lt_lp[10];                     //Local port number of the last server or peer connection
    char lt_qos[20];                    //Server connection TOS/DSCP value set by Squid
    char lt_nfmark[20];                 //Server connection netfilter mark set by Squid

    char ts[10];                        //Seconds since epoch
    char tu[3];                         //Subsecond time (milliseconds)
    char tl[26];                        //Local time. Optional strftime format argument
    char tg[20];                        //GMT time. Optional strftime format argument
    char tr[10];                         //Response time (milliseconds)
    char dt[10];                         //Total time spent making DNS lookups (milliseconds)
    char tS[14];                        //Approximate master transaction start time (ts.tu)

    char et[50];                        //Tag returned by external acl
    char ea[50];                        //Log string returned by external acl
    char un[50];                        //User name (any available)
    char ul[50];                        //User name from authentication
    char ue[50];                        //User name from external acl helper
    char ui[50];                        //User name from ident

    char rm[10];                        //Request method (GET/POST etc)
    char gt_rm[10];                     //Request method from client
    char lt_rm[10];                     //Request method sent to server or peer
    char ru[2048];                      //Request URL from client (historic, filtered for logging)
    char gt_ru[2048];                   //Request URL from client
    char lt_ru[2048];                   //Request URL sent to server or peer
    char gt_rs[20];                     //Request URL scheme from client
    char lt_rs[20];                     //Request URL scheme sent to server or peer
    char gt_rd[256];                    //Request URL domain from client
    char lt_rd[256];                    //Request URL domain sent to server or peer
    char gt_rP[10];                     //Request URL port from client
    char lt_rP[10];                     //Request URL port sent to server or peer
    char rp[2048];                      //Request URL path excluding hostname
    char gt_rp[2048];                   //Request URL path excluding hostname from client
    char lt_rp[2048];                   //Request URL path excluding hostname sent to server or peer
    char rv[5];                         //Request protocol version
    char gt_rv[5];                      //Request protocol version from client
    char lt_rv[5];                      //Request protocol version sent to server or peer

    char gt_h[2048];                    //Original received request header.
    char gt_ha[2048];                   //Received request header after adaptation and redirection (pre-cache REQMOD vectoring point).

    char lt_Hs[3];                      //HTTP status code received from the next hop
    char gt_Hs[3];                      //HTTP status code sent to the client
    char lt_h[2048];                    //Reply header. Optional header name argument as for >h
    char mt[50];                        //MIME content type

    char st[16];                        //Total size of request + reply traffic with client
    char gt_st[16];                     //Total size of request received from client. Excluding chunked encoding bytes.
    char lt_st[16];                     //Total size of reply sent to client (after adaptation)
    char gt_sh[16];                     //Size of request headers received from client
    char lt_sh[16];                     //Size of reply headers sent to client (after adaptation)

    char lt_sH[16];                     //Reply high offset sent
    char lt_sS[16];                     //Upstream object size

    char lt_bs[16];                     //Number of HTTP-equivalent message body bytes transfer encoding and control messages. Generated FTP/Gopher listings are treated as received bodies.

    char lt_pt[10];                     //Peer response time in milliseconds. The timer starts when the last request byte is sent to the next hop and stops when the last response byte is received.
    char lt_tt[10];                     //Total time in milliseconds. The timer starts with the first connect request (or write I/O) sent to the first selected peer. The timer stops with the last I/O with the last peer.
};

int sock[0], port, hosts = 1, agents = 1, true = 1, connected, size;

struct sockaddr_in server, client, *clients;
struct sockaddr_storage addr;

socklen_t sin_size, len;
pthread_t *listen_thread, *writedb_thread;
fd_set active_fd_set, read_fd_set;

void createSocket()
{
    debug("Creating network socket", "server::createSocket");
    if(strlen(ServerPort) == 0)
        port = 8213;
    else
        port = atoi(ServerPort);

    if((sock[0] = socket(AF_INET, SOCK_STREAM , IPPROTO_TCP)) < 0)
    {
        logerror(errno, "Socket", "server::createSocket");
        exit(1);
    }

    if(setsockopt(sock[0], SOL_SOCKET, SO_REUSEADDR, &true, sizeof(true)) == -1)
        logerror(errno, "Setsockopt", "server::createSocket");
    
    server.sin_family                       = AF_INET;
    server.sin_port                         = htons(port);
    server.sin_addr.s_addr                  = INADDR_ANY;
    bzero(&(server.sin_zero), 8);
}

void startBind()
{
    debug("Creating socket FD bind to the server", "server::startServer");
    if(bind(sock[0], (struct sockaddr *)&server, sizeof(struct sockaddr)) == -1)
    {
        logerror(errno, "Bind", "server::startBind");
        exit(1);
    }
}

void startListen()
{
    debug("Preparing to receive connections", "server::startListen");
    if(listen(sock[0], 10) == -1)
    {
        logerror(errno, "Listen", "server::startListen");
        exit(1);
    }
}

int listAgent(char *ip_agent)
{
    char *getAgents;
    
    getAgents = strtok(ListenAgents, " ");
    int h = 0;
    while(getAgents != NULL)
    {
        if(strcmp(ip_agent, getAgents) == 0)
            return 1;
        getAgents = strtok(NULL, " ");
        ++h;
    }
    return 0;
}

void *waitRequest(void *w)
{
    debug("Waiting for connections", "server::*waitRequest");
    FD_ZERO (&active_fd_set);
    FD_SET (sock[0], &active_fd_set);
    
    while(1)
    {
        sin_size = sizeof(struct sockaddr_in);
        read_fd_set = active_fd_set;
        
        int new = accept(sock[0], (struct sockaddr *)&client, &sin_size);
        if(new < 0)
        {
            logerror(errno, "Accept", "server::*waitRequest");
            continue;
        }
        
        if(0 != strlen(ListenAgents))
        {
            if(listAgent(inet_ntoa(client.sin_addr)) != 1)
            {
                char msg[70];
                sprintf(msg, "Host is not authorized to connect to the server: %s:%d", inet_ntoa(client.sin_addr), (int)ntohs(client.sin_port));
                logerror(-1, msg, "server::*waitRequest");
                shutdown(new, 2);
                continue;
            }
        }
        
        host = (struct hosts_connected *)realloc(host, ((sizeof(struct hosts_connected) * hosts) + sizeof(struct hosts_connected)));
        strcpy(host[hosts].ip, inet_ntoa(client.sin_addr));
        host[hosts].port = (int)ntohs(client.sin_port);
        host[hosts].conn = new;
        
        int id = hosts;
        writedb_thread = (pthread_t *)realloc(writedb_thread, ((sizeof(pthread_t *) * hosts) + (sizeof(pthread_t *))));
        listen_thread = (pthread_t *)realloc(listen_thread, ((sizeof(pthread_t *) * hosts) + (sizeof(pthread_t *))));
        
        pthread_create(&(writedb_thread[hosts]), NULL, writedbAgent, &id);
        pthread_create(&(listen_thread[hosts]), NULL, listenAgent, &id);

        hosts++;
    }
    pthread_exit((void*)w);
}

void *listenAgent(void *id)
{
    int n = *(int *)id;
    host[n].listen = 1;
    
    char msg_db_la[50], filename_agent[70];
    
    sprintf(msg_db_la, "Listening agent %s:%d", host[n].ip, host[n].port);
    debug(msg_db_la, "server::*listenAgent");
    
    sprintf(filename_agent, "%sserver/access_agent_%s_%d.log", PathLog, host[n].ip, host[n].port);
    
    int check_read;
    char buffer[1048576];
    while(1)
    {
        memset(buffer, 0, sizeof(buffer));
        check_read = read(host[n].conn, buffer, sizeof(buffer));
        
        host[n].action = 1;
        if(check_read <= 0)
        {
            shutdown(host[n].conn, 2);
            host[n].conn = 0;
            host[n].listen = 0;
            host[n].action = 0;
            return (void *)0;
        }
        else
        {
            int filelog = open(filename_agent, O_WRONLY | O_CREAT | O_APPEND, 0775);
            if(filelog < 0)
                logerror(errno, filename_agent, "server::*listenAgent");
            write(filelog, buffer, check_read);
            close(filelog);
            host[n].action = 0;
        }
    }
    host[n].listen = 0;
    pthread_exit((void*)NULL);
}

void *writedbAgent(void *id)
{
    int n = *(int *)id;
    host[n].write = 1;
    
    checkAgent(host[n].ip);
    
    char msg_db_wdb[70], filename_agent[70], tmpfilename_agent[70], statfilename_agent[75];
    sprintf(msg_db_wdb, "Writing in the database logs the agent %s:%d", host[n].ip, host[n].port);
    debug(msg_db_wdb, "server::*writedbAgent");
    
    if(strlen(PathLog) == 0)
        PathLog = "/var/log/logSquid/";

    sprintf(filename_agent, "%sserver/access_agent_%s_%d.log", PathLog, host[n].ip, host[n].port);
    sprintf(tmpfilename_agent, "%s.tmp", filename_agent);
    sprintf(statfilename_agent, "%s.stat", filename_agent);
    
    int filelog_agent = open(filename_agent, O_WRONLY | O_CREAT, 0775);
    if(filelog_agent < 0)
    {
        logerror(errno, filename_agent, "server::*writedbAgent");
        host[n].write = 0;
        pthread_cancel(listen_thread[n]);
        close(filelog_agent);
        return (void*)NULL;
    }
    close(filelog_agent);
    
    unsigned long size_f = 0;
    while(1)
    {
        sleep(1);
        if(host[n].action == 1)
            continue;

        struct stat f;
        int s_filename_agent = stat(filename_agent, &f);
        if(s_filename_agent < 0 && host[n].conn == 0)
        {
            host[n].write = 0;
            break;
        }
        if((unsigned long)f.st_size != (unsigned long)size_f && host[n].action == 0)
        {
            rename(filename_agent, tmpfilename_agent);
            write_db(0, host[n].ip, host[n].port);
        }
        size_f = f.st_size;
    }
    host[n].write = 0;
    
    pthread_exit((void*)NULL);
}

void write_db(int lines, char ip[16], int port)
{
    char tmpfilename_agent[75], statfilename_agent[75], errfilename_agent[75];
    sprintf(tmpfilename_agent, "%sserver/access_agent_%s_%d.log.tmp", PathLog, ip, port);
    sprintf(statfilename_agent, "%sserver/access_agent_%s_%d.log.stat", PathLog, ip, port);
    sprintf(errfilename_agent, "%s/server/access_agent_%s_%d.log.err", PathLog, ip, port);
    
    FILE *filelog = fopen(tmpfilename_agent, "rw");
    if(filelog == NULL)
        logerror(errno, tmpfilename_agent, "server::write_db");
    
    int line_bytes = 2400;
    char get_line[line_bytes];

    while (!feof(filelog))
    {
        memset(&get_line, 0, strlen(get_line));
        fgets(get_line, line_bytes, filelog);
        printf("line: %s", get_line);
    }

    /*MYSQL *connection = mysql_init(NULL);
    MYSQL_connect(connection);
    
    int line = 0;
    char get_line[2400], buffer[2400], *explode;
    
    if(strcmp(TypeLog, "squid") == 0)
    {
        struct default_squid dsquid;
        while(!feof(filelog))
        {
            memset(&get_line, 0, strlen(get_line));
            memset(&buffer, 0, strlen(buffer));
            memset(&explode, 0, strlen(get_line));
            fgets(get_line, 2400, filelog);
            strcpy(buffer, get_line);

            if(strlen(get_line) == 0)
                continue;

            if(strlen(get_line) > 0 )
                strcpy(dsquid.timestamp, strtok_r(get_line, " ", &explode));
            if(strlen(explode) > 0)
                strcpy(dsquid.elapsed, strtok_r(NULL, " ", &explode));
            if(strlen(explode) > 0)
                strcpy(dsquid.ipaddress, strtok_r(NULL, " ", &explode));
            if(strlen(explode) > 0)
                strcpy(dsquid.codestatus, strtok_r(NULL, " ", &explode));
            if(strlen(explode) > 0)
                strcpy(dsquid.bytes, strtok_r(NULL, " ", &explode));
            if(strlen(explode) > 0)
                strcpy(dsquid.method, strtok_r(NULL, " ", &explode));
            if(strlen(explode) > 0)
                strcpy(dsquid.url, strtok_r(NULL, " ", &explode));
            if(strlen(explode) > 0)
                strcpy(dsquid.username, strtok_r(NULL, " ", &explode));
            if(strlen(explode) > 0)
                strcpy(dsquid.hierarchy, strtok_r(NULL, " ", &explode));
            if(strlen(explode) > 0)
                strcpy(dsquid.mime, strtok_r(NULL, " ", &explode));

            strip(dsquid.timestamp);
            strip(dsquid.elapsed);
            strip(dsquid.ipaddress);
            strip(dsquid.codestatus);
            strip(dsquid.bytes);
            strip(dsquid.method);
            strip_quot(dsquid.url);
            strip(dsquid.url);
            strip(dsquid.username);
            strip(dsquid.hierarchy);
            strip(dsquid.mime);
            
            if(index_of(dsquid.codestatus, '/') == 0 || index_of(dsquid.ipaddress, '.') == 0)
            {
                int write_lineerror = open(errfilename_agent, O_WRONLY | O_CREAT | O_APPEND, 0775);
                if(write_lineerror < 0)
                    logerror(errno, errfilename_agent, "server::write_db");
                write(write_lineerror, buffer, strlen(buffer));
                close(write_lineerror);
                continue;
            }

            if(strlen(dsquid.elapsed) == 0 || strlen(dsquid.ipaddress) == 0 || strlen(dsquid.codestatus) == 0 || strlen(dsquid.bytes) == 0 || strlen(dsquid.method) == 0 || strlen(dsquid.url) == 0 || strlen(dsquid.username) == 0 || strlen(dsquid.hierarchy) == 0 || strlen(dsquid.mime) == 0)
            {
                int write_lineerror = open(errfilename_agent, O_WRONLY | O_CREAT | O_APPEND, 0775);
                if(write_lineerror < 0)
                    logerror(errno, errfilename_agent, "server::write_db");
                write(write_lineerror, buffer, strlen(buffer));
                close(write_lineerror);
                continue;
            }

            if(lines > 0 && lines >= line)
            {
                ++line;
                continue;
            }
            char query[2400];
            sprintf(query, "INSERT INTO logSquid(datetime, ipuser, username, destination, url, ipdest, mime, size, status, agent, server)"
                           " VALUES(from_unixtime('%s'), '%s', '%s', '-', '%s', '%s', '%s', '%lu', '%s', '%d', '%d');",
                    dsquid.timestamp, dsquid.ipaddress, dsquid.username, dsquid.url, dsquid.hierarchy, dsquid.mime, (unsigned long)atoi(dsquid.bytes), dsquid.codestatus, getIdAgent(ip), id_user_session);
            int st_query = MYSQL_query(query, connection);

            if(st_query > 0)
            {
                char query_error[2400];
                sprintf(query_error, "%s %s %s %s %s %s %s %s %s\n, %s\n",
                        dsquid.timestamp, dsquid.ipaddress, dsquid.username, dsquid.url, dsquid.hierarchy, dsquid.bytes, dsquid.codestatus, dsquid.mime, ip,
                        mysql_error(connection));
                int _query_error = open(errfilename_agent, O_WRONLY | O_CREAT | O_APPEND, 0775);
                if(_query_error < 0)
                    logerror(errno, errfilename_agent, "server::write_db");
                write(_query_error, query_error, strlen(query_error));
                close(_query_error);
            }

            memset(query, 0, sizeof(query));
            line++;

            int statfilelog = open(statfilename_agent, O_WRONLY | O_CREAT, 0775);
            if(statfilelog < 0)
                logerror(errno, statfilename_agent, "server::write_db");
            char info_agent[50];
            sprintf(info_agent, "%d %s %d\n", line, ip, port);
            lseek(statfilelog, 0, SEEK_SET);
            write(statfilelog, info_agent, strlen(info_agent));
            close(statfilelog);

            memset(&dsquid, 0, sizeof(dsquid));
        }
    }
    
    if(strcmp(TypeLog, "logSquid") == 0)
    {
        struct default_logSquid dlsquid;
        while(!feof(filelog))
        {
            memset(&get_line, 0, strlen(get_line));
            memset(&buffer, 0, strlen(buffer));
            memset(&explode, 0, strlen(get_line));
            fgets(get_line, 2400, filelog);
            strcpy(buffer, get_line);

            if(strlen(get_line) == 0)
                continue;

            if(strlen(get_line) > 0 )
                strcpy(dlsquid.timestamp, strtok_r(get_line, " ", &explode));
            if(strlen(explode) > 0)
                strcpy(dlsquid.ipaddress, strtok_r(NULL, " ", &explode));
            if(strlen(explode) > 0)
                strcpy(dlsquid.macaddress, strtok_r(NULL, " ", &explode));
            if(strlen(explode) > 0)
                strcpy(dlsquid.username, strtok_r(NULL, " ", &explode));
            if(strlen(explode) > 0)
                strcpy(dlsquid.serverfqn, strtok_r(NULL, " ", &explode));
            if(strlen(explode) > 0)
                strcpy(dlsquid.url, strtok_r(NULL, " ", &explode));
            if(strlen(explode) > 0)
                strcpy(dlsquid.ipdest, strtok_r(NULL, " ", &explode));
            if(strlen(explode) > 0)
                strcpy(dlsquid.mime, strtok_r(NULL, " ", &explode));
            if(strlen(explode) > 0)
                strcpy(dlsquid.bytes, strtok_r(NULL, " ", &explode));
            if(strlen(explode) > 0)
                strcpy(dlsquid.codestatus, strtok_r(NULL, " ", &explode));
            
            strip(dlsquid.timestamp);
            strip(dlsquid.ipaddress);
            strip(dlsquid.macaddress);
            strip(dlsquid.username);
            strip(dlsquid.serverfqn);
            strip_quot(dlsquid.url);
            strip(dlsquid.url);
            strip(dlsquid.ipdest);
            strip(dlsquid.mime);
            strip(dlsquid.bytes);
            strip(dlsquid.codestatus);
            
            if(index_of(dlsquid.codestatus, '/') == 0 || index_of(dlsquid.macaddress, ':') == 0 || index_of(dlsquid.ipaddress, '.') == 0)
            {
                int write_lineerror = open(errfilename_agent, O_WRONLY | O_CREAT | O_APPEND, 0775);
                if(write_lineerror < 0)
                    logerror(errno, errfilename_agent, "server::write_db");
                write(write_lineerror, buffer, strlen(buffer));
                close(write_lineerror);
                continue;
            }

            if(strlen(dlsquid.ipaddress) == 0 || strlen(dlsquid.macaddress) == 0 || strlen(dlsquid.username) == 0 || strlen(dlsquid.serverfqn) == 0 || strlen(dlsquid.url) == 0 || strlen(dlsquid.ipdest) == 0 || strlen(dlsquid.mime) == 0 || strlen(dlsquid.bytes) == 0 || strlen(dlsquid.codestatus) == 0)
            {
                int write_lineerror = open(errfilename_agent, O_WRONLY | O_CREAT | O_APPEND, 0775);
                if(write_lineerror < 0)
                    logerror(errno, errfilename_agent, "server::write_db");
                write(write_lineerror, buffer, strlen(buffer));
                close(write_lineerror);
                continue;
            }

            if(lines > 0 && lines >= line)
            {
                ++line;
                continue;
            }
            
            char query[2400];
            sprintf(query, "INSERT INTO logSquid(datetime, ipuser, macaddress, username, destination, url, ipdest, mime, size, status, agent, server)"
                           " VALUES(from_unixtime('%s'), '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%lu', '%s', '%d', '%d');",
                    dlsquid.timestamp, dlsquid.ipaddress, dlsquid.macaddress, dlsquid.username, dlsquid.serverfqn, dlsquid.url, dlsquid.ipdest, dlsquid.mime, (unsigned long)atoi(dlsquid.bytes), dlsquid.codestatus, getIdAgent(ip), id_user_session);
            int st_query = MYSQL_query(query, connection);

            if(st_query > 0)
            {
                char query_error[2400];
                sprintf(query_error, "%s %s %s %s %s %s %s %s %s %s %s\n, %s\n",
                        dlsquid.timestamp, dlsquid.ipaddress, dlsquid.macaddress, dlsquid.username, dlsquid.serverfqn, dlsquid.url, dlsquid.ipdest, dlsquid.mime, dlsquid.bytes, dlsquid.codestatus, ip,
                        mysql_error(connection));
                int _query_error = open(errfilename_agent, O_WRONLY | O_CREAT | O_APPEND, 0775);
                if(_query_error < 0)
                    logerror(errno, errfilename_agent, "server::write_db");
                write(_query_error, query_error, strlen(query_error));
                close(_query_error);
            }
            
            memset(query, 0, sizeof(query));
            ++line;

            int statfilelog = open(statfilename_agent, O_WRONLY | O_CREAT, 0775);
            if(statfilelog < 0)
                logerror(errno, statfilename_agent, "server::write_db");
            char info_agent[50];
            sprintf(info_agent, "%d %s %d\n", line, ip, port);
            lseek(statfilelog, 0, SEEK_SET);
            write(statfilelog, info_agent, strlen(info_agent));
            close(statfilelog);

            memset(&dlsquid, 0, sizeof(dlsquid));
        }
    }

    int remove_tmp = remove(tmpfilename_agent);
    if(remove_tmp < 0)
        logerror(errno, tmpfilename_agent, "server::*writedbAgent");
    int remove_stat = remove(statfilename_agent);
    if(remove_stat < 0)
        logerror(errno, statfilename_agent, "server::*writedbAgent");
    
    mysql_close(connection);*/
    fclose(filelog);
}

void getAgents()
{
    MYSQL *connection = mysql_init(NULL);
    MYSQL_connect(connection);
    
    char query[50];
    sprintf(query, "SELECT id, ipaddr FROM agents");
    
    int st_query = mysql_query(connection, query);
    if(st_query == 0)
    {
        MYSQL_RES *result = mysql_store_result(connection);
        unsigned long long num_rows = mysql_num_rows(result);
        if(num_rows > 0)
        {
            MYSQL_ROW row;
            while((row = mysql_fetch_row(result)))
            {
                if(row == NULL)
                    break;
                agent = (struct list_agents *)realloc(agent, ((sizeof(struct list_agents) * agents) + sizeof(struct list_agents)));
                agent[agents].id = atoi(row[0]);
                strcpy(agent[agents].ip, row[1]);
                ++agents;
            }
        }
        mysql_free_result(result);
    }
    mysql_close(connection);
}

int getIdAgent(char ip_agent[16])
{
    for(int i = 1; i < agents; ++i){
        if(strcmp(ip_agent, agent[i].ip) == 0)
            return agent[i].id;
    }
    return 0;
}

void checkAgent(char ip_agent[16])
{
    debug("Check agent", "server::checkAgent");
    if(agents == 1)
    {
        setAgent(ip_agent);
        return;
    }
    for(int i = 1; i < agents; ++i)
    {
        if(strcmp(ip_agent, agent[i].ip) == 0)
            return;
    }
    setAgent(ip_agent);
}

void setAgent(char ip_agent[16])
{
    debug("Check agent", "server::setAgent");

    MYSQL *connection = mysql_init(NULL);
    MYSQL_connect(connection);
    
    char query[50];
    sprintf(query, "INSERT INTO agents(ipaddr) VALUES('%s')", ip_agent);
    int st_query = mysql_query(connection, query);
    if(st_query > 0)
        logerror(-1, (char *)mysql_error(connection), "server::setAgent");
    else
        getAgents();
    mysql_close(connection);
}

void *garbageCollector(void *g)
{
    debug("Search garbage", "server::*garbageCollector");
    check_pathlog();
    check_lt_log();
    check_lt_start();
    while(1)
    {
        if(hosts == 1)
        {
            sleep(60);
            continue;
        }
        check_lt_log();
        check_lt_start();
        check_lt();
        sleep(60);
    }
    pthread_exit((void*)g);
}

void check_lt_start()
{
    debug("Searching for files interrupted", "server::check_lt_start");
    char *file_status = (char*)malloc(sizeof(char) * strlen(PathLog)+25);
    strcpy(file_status, PathLog);
    strcat(file_status, "server/access_agent_*.stat");
    
    glob_t glob_buffer;
    glob((char * restrict)file_status, 0, NULL, &glob_buffer);
    if(glob_buffer.gl_pathc > 0)
    {
        for(int i = (glob_buffer.gl_pathc -1); i >= 0; i--)
        {
            char ip[15], lines[15], port[15];
            FILE *filestat = fopen(glob_buffer.gl_pathv[i], "r");
            if(filestat == NULL)
                logerror(errno, glob_buffer.gl_pathv[i], "server::*writedbAgent");
            fscanf(filestat, "%s %s %s", lines, ip, port);
            write_db(atoi(lines), ip, atoi(port));
            fclose(filestat);
        }
    }
    globfree(&glob_buffer);
}

void check_lt_log()
{
    debug("Looking for interrupted log files", "server::check_lt_log");
    char *file_log = (char*)malloc(sizeof(char) * strlen(PathLog)+25);
    strcpy(file_log, PathLog);
    strcat(file_log, "server/access_agent_*.log");
    
    glob_t glob_log;
    glob((char * restrict)file_log, 0, NULL, &glob_log);
    if(glob_log.gl_pathc > 0)
    {
        for(int i = (glob_log.gl_pathc -1); i >= 0; i--)
        {
            struct stat log;
            int _file_log = stat(glob_log.gl_pathv[i], &log);
            if(_file_log != -1 && log.st_size > 0)
            {
                for(int x = 1; x < hosts; ++x)
                {
                    char file_test[75];
                    sprintf(file_test, "%sserver/access_agent_%s_%d.log", PathLog, host[x].ip, host[x].port);
                    if(strcmp(file_test, glob_log.gl_pathv[i]) == 0)
                        continue;
                }
                
                char file_tmp[75], file_stat[75], filename_split[75];
                sprintf(file_tmp, "%s.tmp", glob_log.gl_pathv[i]);
                sprintf(file_stat, "%s.stat", glob_log.gl_pathv[i]);
                strcpy(filename_split, glob_log.gl_pathv[i]);
                filename_split[(strlen(filename_split) -4)] = '\0';
                
                char *get_info = malloc(16), get_ip[16], get_port[8];
                strtok_r(filename_split, "_", &get_info);
                strtok_r(NULL, "_", &get_info);
                strcpy(get_ip, strtok_r(NULL, "_", &get_info));
                strcpy(get_port, strtok_r(NULL, "_", &get_info));
                
                if(rename(glob_log.gl_pathv[i], file_tmp) < 0)
                    continue;

                int create_file_stat = open(file_stat, O_WRONLY | O_CREAT, 0775);
                if(create_file_stat < 0)
                    continue;

                char stat_info[50];
                sprintf(stat_info, "0 %s %s\n", get_ip, get_port);
                write(create_file_stat, stat_info, strlen(stat_info));
                close(create_file_stat);
            }
            else if(_file_log != -1 && log.st_size == 0)
            {
                if(remove(glob_log.gl_pathv[i]))
                    logerror(errno, glob_log.gl_pathv[i], "server::check_lt_log");
            }
        }
    }
    
}

void check_lt()
{
    debug("Searching garbage", "server::check_lt");
    for(int i = 1; i < hosts; ++i)
    {
        if(host[i].conn == 0 && host[i].listen == 0)
        {
            char filename[70], filename_tmp[75];
            sprintf(filename, "%sserver/access_agent_%s_%d.log", PathLog, host[i].ip, host[i].port);
            sprintf(filename_tmp, "%s.tmp", filename);
            
            struct stat log, tmp;
            int _log = stat(filename, &log);
            if(_log != -1 && log.st_size == 0)
            {
                int _rlog = remove(filename);
                if(_rlog < 0)
                    logerror(errno, filename, "server::*garbageCollector");
            }
            int _tmp = stat(filename_tmp, &tmp);
            if(_tmp != -1 && tmp.st_size == 0)
            {
                int _rtmp = remove(filename_tmp);
                if(_rtmp < 0)
                    logerror(errno, filename_tmp, "server::*garbageCollector");
            }

        }
    }
}

ptrdiff_t index_of(const char *string, char search)
{
    const char *moved_string = strchr(string, search);
    /* If not null, return the difference. */
    if (moved_string)
        return 1;
    return 0;
}

void strip(char *s)
{
    char *p2 = s;
    while(*s != '\0')
    {
        if(*s != '\t' && *s != '\n')
            *p2++ = *s++;
        else
            ++s;
    }
    *p2 = '\0';
}

void strip_quot(char *str)
{
    int size = strlen(str);
    char *str2 = str;
    for(int i = 0; i < size; ++i)
    {
        if(str2[i] == '\'')
            strcpy(&str2[i], "-");
    }
    str = str2;
}
