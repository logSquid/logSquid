#include "services.h"

char *sha1( char *val ){
   int msg_length = strlen( val );
   int hash_length = gcry_md_get_algo_dlen( GCRY_MD_SHA1 );
   unsigned char hash[ hash_length ];
   char *out = (char *) malloc( sizeof(char) * ((hash_length*2)+1) );
   char *p = out;
   gcry_md_hash_buffer( GCRY_MD_SHA1, hash, val, msg_length );
   int i;
   for ( i = 0; i < hash_length; i++, p += 2 ) {
      snprintf ( p, 3, "%02x", hash[i] );
   }
   return out;
}

char *getIPaddr(){
    extern char *ServerDB, *ServerPortDB;
    struct sockaddr_in serv;
    
    int sock = socket(AF_INET, SOCK_DGRAM, 0);
    if(sock < 0){
        logerror(-1, "", "services::*getIPaddr");
        return "0";
    }

    memset(&serv, 0, sizeof(serv));
    serv.sin_family = AF_INET;
    serv.sin_addr.s_addr = inet_addr(ServerDB);
    serv.sin_port = htons(atoi(ServerPortDB));
    
    connect(sock, (const struct sockaddr*)&serv, sizeof(serv));
    struct sockaddr_in name;
    socklen_t namelen = sizeof(name);
    getsockname(sock, (struct sockaddr*)&name, &namelen);
    
    char buffer[100];
    const char* p = inet_ntop(AF_INET, &name.sin_addr, buffer, 100);
    //char *result = (char *)p;
    char *result = strdup(p);
    close(sock);
   
	printf("Char: %lu, Const Char: %lu\n", sizeof(char *), sizeof(const char *));
 
    if(p != NULL)
        return result;
    else
        logerror(-1, "", "services::*getIPaddr");
    
    return "0";
}

int getch(void){
    struct termios oldattr, newattr;
    int ch;

    tcgetattr( STDIN_FILENO, &oldattr );
    newattr = oldattr;
    newattr.c_lflag &= ~( ICANON | ECHO );
    tcsetattr( STDIN_FILENO, TCSANOW, &newattr );
    ch = getchar();
    tcsetattr( STDIN_FILENO, TCSANOW, &oldattr );

    return ch;
}

void flush_in(){ 
    int ch;
    while( (ch = fgetc(stdin)) != EOF && ch != '\n' ){} 
}

char *getIP(){
    char *ip = malloc(16);
    int i = 0;
    
    printf("IP address: ");
    while(1){
        char ch = getch();
        if(ch == 10){
            printf("\n");
            break;
        } else if(ch == 127){
            if(i == 0)
                continue;
            i--;
            ip[i] = '\0';
            putchar('\b');
            printf(" ");
            putchar('\b');
            continue;
        }
        if(i > 14)
            continue;
        if(ch == 48 || ch == 49 || ch == 50 || ch == 51 || ch == 52 || ch == 53 || ch == 54 || ch == 55 || ch == 56 || ch == 57 || ch == 46){
            putchar(ch);
            ip[i] = ch;
            i++;
        }
    }
    ip[i] = '\0';
    return ip;
}

char *getUser(char *msg){
    char *username = malloc(30);
    int i = 0;
        
    printf("Username%s: ", msg);
    while(1){
        char ch = getch();
        if(ch == 10){
            printf("\n");
            break;
        }
        else if(ch == 127){
            if(i == 0)
                continue;
            i--;
            username[i] = '\0';
            putchar('\b');
            printf(" ");
            putchar('\b');
            continue;
        }
        putchar(ch);
        username[i] = ch;
        i++;
    }
    username[i] = '\0';
    return username;
}

char *getPass(char *msg){
    char *password = malloc(50);
    int i = 0;
    
    printf("Password%s: ", msg);
    while(1){
        char ch = getch();
        if(ch == 10)
            break;
        else if(ch == 127){
            if(i == 0)
                continue;
            i--;
            password[i] = '\0';
            putchar('\b');
            printf(" ");
            putchar('\b');
            continue;
        }
        putchar('*');
        password[i] = ch;
        i++;
    }
    password[i] = '\0';
    printf("\n");
    return password;
}

char *getDatabase(char *msg){
    char *database = malloc(30);
    int i = 0;
        
    printf("Database%s: ", msg);
    while(1){
        char ch = getch();
        if(ch == 10){
            printf("\n");
            break;
        }
        else if(ch == 127){
            if(i == 0)
                continue;
            i--;
            database[i] = '\0';
            putchar('\b');
            printf(" ");
            putchar('\b');
            continue;
        }
        putchar(ch);
        database[i] = ch;
        i++;
    }
    database[i] = '\0';
    return database;
}
