/* 
 * File:   mysql.c
 * Author: Mauro Marssola
 *
 * Created on 31 de Agosto de 2016, 16:23
 */

#include "lmysql.h"

struct SessionServer{
    int id;
    char ip[16];
} session;

int id_user_session;

void MYSQL_connect(MYSQL *connection){
    debug("Creating connection to the database", "mysql::MYSQL_connect");
    
    extern char *ServerDB, *UsernameDB, *PasswordDB, *NameDB;
    if(mysql_real_connect(connection, ServerDB, UsernameDB, PasswordDB, NameDB, 0, NULL, 0))
        debug("Connected to Database", "mysql::MYSQL_connect");
    else{
        char err_mysql[50];
        strcpy(err_mysql, mysql_error(connection));
        logerror(-1, err_mysql, "mysql::MYSQL_connect");
    }
}

int MYSQL_query(char *query, MYSQL *connection){
    int st_query = mysql_query(connection, query);
    return st_query;
}


void StartSession(){
    debug("Start session in database", "mysql::StartSession");
    MYSQL *connection = mysql_init(NULL);
    MYSQL_connect(connection);
    
    char *getip = getIPaddr();
    char query[2048], timestamp[256];
    int startsession = (int)time(NULL);
    sprintf(timestamp, "%d", startsession);
    
    char ipaddr[16];
    strcpy(ipaddr, getip);
    
    sprintf(query, "SELECT id, ipaddr FROM servers WHERE `ipaddr`='%s'", ipaddr);
    int st_query = mysql_query(connection, query);
    
    if(st_query == 0){
        MYSQL_RES *result = mysql_store_result(connection);
        unsigned long long num_rows = mysql_num_rows(result);
        if(num_rows == 0){
            memset(query, 0, strlen(query));
            sprintf(query, "INSERT INTO `servers`(`ipaddr`, `start_session`, `last_activity`) VALUES('%s', from_unixtime('%d'), from_unixtime('%d'))", ipaddr, startsession, startsession);
            int st_query = MYSQL_query(query, connection);
            if(st_query > 0){
                logerror(errno, (char *)mysql_error(connection), "mysql::StartSession");
                exit(0);
            }
            unsigned long long row = mysql_insert_id(connection);
            session.id = (int) row;
            strcpy(session.ip, ipaddr);
            mysql_free_result(result);
        }else{
            MYSQL_ROW row;
            row = mysql_fetch_row(result);

            memset(query, 0, strlen(query));
            sprintf(query, "UPDATE `servers` SET `ipaddr`='%s', `start_session`=from_unixtime('%d'), `last_activity`=from_unixtime('%d') WHERE `id`='%s'", ipaddr, startsession, startsession, row[0]);
            int st_query = MYSQL_query(query, connection);
            if(st_query > 0){
                logerror(-1, "Authentication failed", "mysql::StartSession");
                exit(0);
            }
            session.id = atoi(row[0]);
            strcpy(session.ip, ipaddr);
            mysql_free_result(result);
        }
    }else{
        logerror(errno, (char *)mysql_error(connection), "mysql::StartSession");
        exit(0);
    }
    id_user_session = session.id;
    
    memset(query, 0, strlen(query));
    mysql_close(connection);
}

void RenewSession(){
    debug("Renew session in database", "mysql::RenewSession");
    MYSQL *connection = mysql_init(NULL);
    MYSQL_connect(connection);
    
    char query[2048];
    sprintf(query, "SELECT id FROM servers WHERE `id`='%d' AND `ipaddr`='%s'", session.id, session.ip);

    int st_query = mysql_query(connection, query);
    if(st_query == 0){
        MYSQL_RES *result = mysql_store_result(connection);
        unsigned long long num_rows = mysql_num_rows(result);
        if(num_rows == 0){
            logerror(-1, "IP address is invalid", "mysql::RenewSession");
            exit(0);
        }
    }
    
    int renewsession = (int)time(NULL);
        
    char *getip = getIPaddr();
    char ipaddr[16];
    strcpy(ipaddr, getip);
    
    memset(query, 0, strlen(query));
    sprintf(query, "UPDATE `servers` SET `last_activity`=from_unixtime('%d') WHERE `id`='%d'", renewsession, session.id);
    
    int s_query = MYSQL_query(query, connection);
    if(s_query > 0){
        logerror(-1, "Renew session failed", "mysql::RenewSession");
        exit(0);
    }
    strcpy(session.ip, ipaddr);
    mysql_close(connection);
}

void *Session(void *v){
    while(1){
        sleep(60);
        RenewSession();
    }
    return v;
}

void CreateDatabase(char *name){
    char *database;
    if(strcmp(name, "default") == 0)
        database = "logSquid";
    else
        database = name;
    MYSQL *connection = mysql_init(NULL);
    
    extern char *ServerDB, *UsernameDB, *PasswordDB;
    if(mysql_real_connect(connection, ServerDB, UsernameDB, PasswordDB, NULL, 0, NULL, 0))
        debug("Connected to Database", "mysql::MYSQL_connect");
    else{
        char err_mysql[50];
        strcpy(err_mysql, mysql_error(connection));
        logerror(-1, err_mysql, "mysql::MYSQL_connect");
    }
    
    char query[100];
    sprintf(query, "CREATE DATABASE %s", database);
    
    int st_query = mysql_query(connection, query);
    if(st_query == 0)
        printf("[ Ok ] Create Database: %s\n", database);
    else
        printf("[ Er ] %s\n", mysql_error(connection));
    
    mysql_close(connection);
}

void DropDatabase(char *name){
    char *database;
    if(strcmp(name, "default") == 0)
        database = "logSquid";
    else
        database = name;
    MYSQL *connection = mysql_init(NULL);
    
    extern char *ServerDB, *UsernameDB, *PasswordDB;
    if(mysql_real_connect(connection, ServerDB, UsernameDB, PasswordDB, NULL, 0, NULL, 0))
        debug("Connected to Database", "mysql::DropDatabase");
    else{
        char err_mysql[50];
        strcpy(err_mysql, mysql_error(connection));
        logerror(-1, err_mysql, "mysql::MYSQL_connect");
    }
    
    char query[100];
    sprintf(query, "DROP DATABASE %s", database);
    
    int st_query = mysql_query(connection, query);
    if(st_query == 0)
        printf("[ Ok ] Remove Database: %s\n", database);
    else
        printf("[ Er ] %s\n", mysql_error(connection));
    
    mysql_close(connection);
}

void CreateTable(char *name){
    char *table;
    if(strcmp(name, "all") == 0){
        char tables[4][10] = {"servers", "logSquid", "users", "agents"};
        for(int i = 0; i < 4; i++)
            CreateTableSQL(tables[i]);
    }
    else{
        table = name;
        CreateTableSQL(table);
    }
}

void CreateTableSQL(char *table){
    char *path_sql = "/usr/share/logSquid/config/database/";
    char *filesql = (char *)malloc(((int)strlen(table)) + ((int)strlen(path_sql)+5));
    sprintf(filesql, "%s%s.sql", path_sql, table);
    
    struct stat file;
    int status = stat(filesql, &file);
    
    if(status == -1){
        printf("[ Er ] %s. File: %s\n", strerror(errno), filesql);
        exit(1);
    }
    
    if((int)file.st_size > 0){
        int read_sql = open(filesql, O_RDONLY);
        if(read_sql <= 0){
            printf("%s. File: %s\n", strerror(errno), filesql);
            exit(1);
        }
        char buffer[(file.st_size * sizeof(char) + 2)];
        memset(buffer, 0, ((int)(file.st_size * sizeof(char) + 2)));
        if(buffer == NULL){
            printf("%s\n", strerror(errno));
            exit(1);
        }
        
        if(lseek(read_sql, 0, SEEK_SET) < 0){
            printf("%s\n", strerror(errno));
            exit(1);
        }

        int ready = read(read_sql, buffer, file.st_size);
        if(ready > 0){
            MYSQL *connection = mysql_init(NULL);
            MYSQL_connect(connection);
            
            int st_query = mysql_query(connection, buffer);
            if(st_query == 0){
                printf("[ Ok ] Table: %s\n", table);
                if(strcmp(table, "users") == 0){
                    char insert_user[170] = {"INSERT INTO `users` (`id`, `username`, `password`, `nickname`, `theme`, `hashCode`) VALUES(1, 'Admin', 'a1c57faec072a5d61ddf05eb7166db83d9920df1', NULL, 'light', NULL);"};
                    int query = mysql_query(connection, insert_user);
                    if(query == 0)
                        printf("[ Ok ] User: Admin\n");
                    else
                        printf("[ Er ] User: Admin - %s\n", mysql_error(connection));
                }
            }
            else
                printf("[ Er ] Table: %s - %s\n", table, mysql_error(connection));
            mysql_close(connection);
        }
    }
    free(filesql);
}

void DropTable(char *name){
    char *table;
    if(strcmp(name, "all") == 0){
        char tables[4][10] = {"servers", "logSquid", "users", "agents"};
        for(int i = 0; i < 4; i++)
            DropTableSQL(tables[i]);
    }
    else{
        table = name;
        DropTableSQL(table);
    }
}

void DropTableSQL(char *name){
    char query[30];
    sprintf(query, "DROP TABLE `%s`;", name);
    
    MYSQL *connection = mysql_init(NULL);
    MYSQL_connect(connection);
    int st_query = mysql_query(connection, query);
    if(st_query == 0)
        printf("[ Ok ] Drop Table: %s\n", name);
    else
        printf("[ Er ] Drop Table: %s - %s\n", name, mysql_error(connection));
    
    mysql_close(connection);
}

void CreateUser(char *option){
    if(strcmp(option, "database") == 0)
        CreateUserDatabase();
    /*if(strcmp(option, "server") == 0)
        CreateUserServer();*/
    if(strcmp(option, "frontend") == 0)
        CreateUserFront();
}

void RemoveUser(char *option){
    if(strcmp(option, "database") == 0)
        RemoveUserDatabase();
    /*if(strcmp(option, "server") == 0)
        RemoveUserServer();*/
    if(strcmp(option, "frontend") == 0)
        RemoveUserFront();
}

void ResetPass(char *option){
    /*if(strcmp(option, "server") == 0)
        ResetPassServer();*/
    if(strcmp(option, "frontend") == 0)
        ResetPassFront();
}

void CreateUserDatabase(){
    char    *username = getUser(" ([Enter] for default)"), 
            *password = getPass(" ([Enter] for default)"),
            *confirm = getPass(" (Confirm)"), 
            *database = getDatabase(" ([Enter] for default)");

    if((int)strlen(username) == 0)
        strcpy(username, "logSquid");
    if((int)strlen(password) == 0)
        strcpy(password, "logSquid");
    if((int)strlen(database) == 0)
        strcpy(database, "logSquid");
    if(strcmp(password, confirm) != 0){
        printf("[ Er ] Reset user: %s - Password does not matches\n", username);
        exit(0);
    }

    char sql_user[256];
    sprintf(sql_user, "CREATE USER \'%s\'@\'%%\' IDENTIFIED BY \'%s\';", username, password);
    MYSQL *connection = mysql_init(NULL);
    MYSQL_connect(connection);
    
    int st_query = mysql_query(connection, sql_user);
    if(st_query == 0)
        printf("[ Ok ] Created user: %s\n", username);
    else
        printf("[ Er ] Created user: %s - %s\n", username, mysql_error(connection));
    
    memset(sql_user, 0, 256);
    sprintf(sql_user, "GRANT SELECT, INSERT, UPDATE, DELETE ON %s.* TO %s@'%%' IDENTIFIED BY '%s';", database, username, password);
    
    st_query = mysql_query(connection, sql_user);
    if(st_query == 0)
        printf("[ Ok ] Privileges granted(SELECT, INSERT, UPDATE, DELETE): %s\n", username);
    else
        printf("[ Er ] Privileges granted(SELECT, INSERT, UPDATE, DELETE): %s - %s\nExecute no MySQL: %s\n", username, mysql_error(connection), sql_user);
    
}

void RemoveUserDatabase(){
    char *username = getUser("");
    if((int)strlen(username) == 0 ){
        printf("[ Er ] Remove user - Invalid user\n");
        exit(0);
    }

    MYSQL *connection = mysql_init(NULL);
    MYSQL_connect(connection);
    
    char sql_user[100];
    sprintf(sql_user, "DROP USER \'%s\';", username);
    int st_query = mysql_query(connection, sql_user);
    if(st_query == 0)
        printf("[ Ok ] Remove user: %s\n", username);
    else
        printf("[ Er ] Remove user: %s - %s\n", username, mysql_error(connection));
    
    mysql_close(connection);
}

void CreateUserServer(){
    char    *username = getUser(""),
            *password = getPass(""),
            *confirm = getPass(" (Confirm)");
    
    if((int)strlen(username) == 0 ){
        printf("[ Er ] Created user - Invalid user\n");
        exit(0);
    }
    if((int)strlen(password) == 0){
        printf("[ Er ] Created user: %s - Invalid password\n", username);
        exit(0);
    }
    if(strcmp(password, confirm) != 0){
        printf("[ Er ] Reset user: %s - Password does not matches\n", username);
        exit(0);
    }
    
    MYSQL *connection = mysql_init(NULL);
    MYSQL_connect(connection);
    
    char query[256];
    sprintf(query, "SELECT username FROM servers WHERE username='%s'", username);
    int st_query = mysql_query(connection, query);
    if(st_query == 0){
        MYSQL_RES *result = mysql_store_result(connection);
        unsigned long long num_rows = mysql_num_rows(result);
        if(num_rows != 0)
            printf("[ Er ] Created user: %s - User already exists\n", username);
        else{
            memset(query, 0, 256);
            sprintf(query, "INSERT INTO servers(username, password) VALUES('%s', '%s')", 
                    username, sha1(password));
            st_query = mysql_query(connection, query);
            if(st_query == 0)
                printf("[ Ok ] Created user: %s\n", username);
        }
    }
    else
        printf("[ Er ] Created user: %s - %s\n", username, mysql_error(connection));
    
    mysql_close(connection);
}

void RemoveUserServer(){
    char *username = getUser("");
    if((int)strlen(username) == 0 ){
        printf("[ Er ] Remove user - Invalid user\n");
        exit(0);
    }
    
    MYSQL *connection = mysql_init(NULL);
    MYSQL_connect(connection);
    
    char query[256];
    sprintf(query, "DELETE FROM servers WHERE username='%s'", username);
    int st_query = mysql_query(connection, query);
    if(st_query == 0){
        int num_rows = mysql_affected_rows(connection);
        if(num_rows > 0)
            printf("[ Ok ] Remove user: %s\n", username);
        else
            printf("[ Er ] Remove user: %s - User not found\n", username);
    }
    else
        printf("[ Er ] Remove user: %s - %s\n", username, mysql_error(connection));
    
    mysql_close(connection);
}

void ResetPassServer(){
    char    *username = getUser(""),
            *password = getPass(""),
            *confirm = getPass(" (Confirm)");
    
    if((int)strlen(username) == 0){
        printf("[ Er ] Reset user - Invalid user\n");
        exit(0);
    }
    if((int)strlen(password) == 0){
        printf("[ Er ] Reset user: %s - Invalid password\n", username);
        exit(0);
    }
    if(strcmp(password, confirm) != 0){
        printf("[ Er ] Reset user: %s - Password does not matches\n", username);
        exit(0);
    }
    
    MYSQL *connection = mysql_init(NULL);
    MYSQL_connect(connection);
    
    char query[256];
    sprintf(query, "SELECT username FROM servers WHERE username='%s'", username);
    int st_query = mysql_query(connection, query);
    if(st_query == 0){
        MYSQL_RES *result = mysql_store_result(connection);
        unsigned long long num_rows = mysql_num_rows(result);
        if(num_rows == 0)
            printf("[ Er ] Reset user: %s - User not found\n", username);
        else{
            memset(query, 0, 256);
            sprintf(query, "UPDATE servers SET password='%s' WHERE username='%s'",
                    sha1(password), username);
            st_query = mysql_query(connection, query);
            if(st_query == 0){
                int affected = mysql_affected_rows(connection);
                if(affected > 0)
                    printf("[ Ok ] Reset user: %s\n", username);
                else
                    printf("[ Er ] Reset user: %s - %s\n", username, mysql_error(connection));
            }
        }
    }
    else
        printf("[ Er ] Reset user: %s - %s\n", username, mysql_error(connection));
    
    mysql_close(connection);
}

void CreateUserFront(){
    char    *username = getUser(""),
            *password = getPass(""),
            *confirm = getPass(" (Confirm)");
    
    if((int)strlen(username) == 0){
        printf("[ Er ] Create User - Invalid user\n");
        exit(0);
    }
    if((int)strlen(password) == 0){
        printf("[ Er ] Create User: %s - Invalid password\n", username);
        exit(0);
    }
    
    if(strcmp(password, confirm) != 0){
        printf("[ Er ] Reset user: %s - Password does not matches\n", username);
        exit(0);
    }
    
    MYSQL *connection = mysql_init(NULL);
    MYSQL_connect(connection);
    
    char query[256];
    sprintf(query, "SELECT username FROM users WHERE username='%s'", username);
    int st_query = mysql_query(connection, query);
    if(st_query == 0){
        MYSQL_RES *result = mysql_store_result(connection);
        unsigned long long num_rows = mysql_num_rows(result);
        if(num_rows != 0)
            printf("[ Er ] Created user: %s - User already exists\n", username);
        else{
            memset(query, 0, 256);
            sprintf(query, "INSERT INTO users(username, password, theme) VALUES('%s', '%s', 'Light')",
                    username, sha1(password));
            st_query = mysql_query(connection, query);
            if(st_query == 0)
                printf("[ Ok ] Create user: %s\n", username);
        }
    }
    else
        printf("[ Er ] Created user: %s - %s\n", username, mysql_error(connection));
    
    mysql_close(connection);
}

void RemoveUserFront(){
    char *username = getUser("");
    if((int)strlen(username) == 0 ){
        printf("[ Er ] Remove user - Invalid user\n");
        exit(0);
    }
    
    MYSQL *connection = mysql_init(NULL);
    MYSQL_connect(connection);
    
    char query[256];
    sprintf(query, "DELETE FROM users WHERE username='%s'", username);
    int st_query = mysql_query(connection, query);
    if(st_query == 0){
        int num_rows = mysql_affected_rows(connection);
        if(num_rows > 0)
            printf("[ Ok ] Remove user: %s\n", username);
        else
            printf("[ Er ] Remove user: %s - User not found\n", username);
    }
    else
        printf("[ Er ] Remove user: %s - %s\n", username, mysql_error(connection));
    
    mysql_close(connection);
}

void ResetPassFront(){
    char    *username = getUser(""),
            *password = getPass(""),
            *confirm = getPass(" (Confirm)");
    
    if((int)strlen(username) == 0){
        printf("[ Er ] Reset user - Invalid user\n");
        exit(0);
    }
    if((int)strlen(password) == 0){
        printf("[ Er ] Reset user: %s - Invalid password\n", username);
        exit(0);
    }
    
    if(strcmp(password, confirm) != 0){
        printf("[ Er ] Reset user: %s - Password does not matches\n", username);
        exit(0);
    }
    
    MYSQL *connection = mysql_init(NULL);
    MYSQL_connect(connection);
    
    char query[256];
    sprintf(query, "SELECT username FROM users WHERE username='%s'", username);
    int st_query = mysql_query(connection, query);
    if(st_query == 0){
        MYSQL_RES *result = mysql_store_result(connection);
        unsigned long long num_rows = mysql_num_rows(result);
        if(num_rows == 0)
            printf("[ Er ] Reset user: %s - User not found\n", username);
        else{
            memset(query, 0, 256);
            sprintf(query, "UPDATE users SET password='%s' WHERE username='%s'",
                    sha1(password), username);
            st_query = mysql_query(connection, query);
            if(st_query == 0){
                int affected = mysql_affected_rows(connection);
                if(affected > 0)
                    printf("[ Ok ] Reset user: %s\n", username);
                else
                    printf("[ Er ] Reset user: %s - %s\n", username, mysql_error(connection));
            }
        }
    }
    else
        printf("[ Er ] Reset user: %s - %s\n", username, mysql_error(connection));
    
    mysql_close(connection);
}
