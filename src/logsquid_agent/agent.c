/* 
 * File:   agent.c
 * Author: marssola
 *
 * Created on 31 de Agosto de 2016, 11:33
 */

#include "agent.h"

extern char *ServerPort, *Server, *PathLog, read_tmp, read_rotate;

struct hostent *host;
struct sockaddr_in server;
int sock, port, bytes_send, conn;

pthread_t threads[2];
fd_set active_fd_set;


void *connectServer(void *c){
    debug("Creating connection to the server", "agent::*connectServer");
    connection:
        createConnection();
        if(sock > 2)
            conn = sock;

        pthread_create(&(threads[0]), NULL, waitResponse, NULL);
        pthread_join(threads[0], NULL);

        if(conn <= 0){
            debug("Wait 60 seconds to try a new connection", "agent::*connectServer");
            sleep(60);
            goto connection;
        }
    pthread_exit((void*)c);
}

void createConnection(){
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if(sock == -1)
        logerror(errno, "Socket", "agent::connectServer");

    host = gethostbyname(Server);
    
    if(strlen(ServerPort) == 0)
        port = 8213;
    else
        port = atoi(ServerPort);
    
    server.sin_family               = AF_INET;
    server.sin_port                 = htons(port);
    server.sin_addr                 = *((struct in_addr *)host->h_addr);
    bzero((&server.sin_zero), 8);
    
    if(connect(sock, (struct sockaddr *)&server, sizeof(struct sockaddr)) == -1){
        logerror(errno, "Connect", "agent::connectServer");
        sock = -1;
    }
    FD_ZERO(&active_fd_set);
    FD_SET(sock, &active_fd_set);
}

void checkSocket(){
    if((sock < 0) && (read_rotate > 0 || read_tmp > 0))
        exit(-1);
}

int sendData(char **buffer, int bytes){
    debug("Receiving data to send to the server", "agent::sendData");
    if(sock <= 0)
        return -1;
    int _send = write(sock, *buffer, bytes);
    return _send;
}

void *waitResponse(void *w){
    int bytes_rec;
    char rec_data[10];
    while(1){
        bytes_rec = read(sock, rec_data, sizeof(rec_data));
        if(bytes_rec <= 0){
            logerror(-1, "Connection closed or refused", "agent::*waitResponse");
            pthread_cancel(threads[0]);
            shutdown(sock, 2);
            FD_CLR(sock, &active_fd_set);
            conn = 0;
            sock = -1;
            break;
        }
    }
    pthread_exit((void*)w);
}

void closeConnection(){
    shutdown(sock, 2);
    FD_CLR(sock, &active_fd_set);
    sock = -1;
}