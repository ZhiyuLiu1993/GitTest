//
// Created by root on 5/15/18.
//

#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <ctype.h>
#include <string.h>
#include <strings.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <stdlib.h>


#define ISspace(x) isspace((int)(x))

#define SERVER_STRING "Server: myhttpd/0.1.0\r\n"

void accept_request(int);
void bad_request(int);
void cat(int, FILE*);
void cannot_execute(int);
void error_die(const char*);
void execute_cgi(int, const char *, const char *, const char *);
int get_line(int, char *, int);
void headers(int, const char *);
void not_found(int);
void serve_file(int, const char *);
int startup(u_short *);
void unimplemented(int);

void not_found(int client){
    char buf[1024];

    sprintf(buf, "HTTP/1.0 200 OK\r\n");
    send(client, buf, sizeof(buf), 0);
    sprintf(buf, SERVER_STRING);
    send(client, buf, sizeof(buf), 0);
    sprintf(buf, "Content-type: text/html\r\n");
    send(client, buf, sizeof(buf), 0);
    sprintf(buf, "\r\n");
    send(client, buf, sizeof(buf), 0);
}

void cannot_execute(int client){
    char buf[1024];

    sprintf(buf, "HTTP/1.0 500 Internal Server Error\r\n");
    send(client, buf, sizeof(buf), 0);
    sprintf(buf, "Content-type: text/html\r\n");
    send(client, buf, sizeof(buf), 0);
    sprintf(buf, "\r\n");
    send(client, buf, sizeof(buf), 0);
    sprintf(buf, "<P>Error prohibited CGI execution.\r\n");
    send(client, buf, sizeof(buf), 0);
}

void headers(int client, const char *filename){
    char buf[1024];
    (void)filename;   //可以使用filename决定是什么文件类型

    sprintf(buf, "HTTP/1.0 200 OK\r\n");
    send(client, buf, sizeof(buf), 0);
    sprintf(buf, SERVER_STRING);
    send(client, buf, sizeof(buf), 0);
    sprintf(buf, "Content-type: text/html\r\n");
    send(client, buf, sizeof(buf), 0);
    sprintf(buf, "\r\n");
    send(client, buf, sizeof(buf), 0);
}

void cat(int client, FILE *resource){
    char buf[1024];

    fgets(buf, sizeof(buf), resource);
    while(!feof(resource)){
        send(client, buf, strlen(buf), 0);
        fgets(buf, sizeof(buf), resource);
    }
}

void serve_file(int client, const char *filename){
    FILE *resource = NULL;
    int numchars = 1;
    char buf[1024];

    buf[0] = 'A';
    buf[1] = '\0';

    while((numchars > 0) && strcmp("\n", buf)){
        numchars = get_line(client, buf, sizeof(buf));
    }

    resource = fopen(filename, "r");
    if(resource == NULL){
        not_found(client);
    }else{
        //打开成功后，将这个文件的基本信息封装成response的头部返回
        headers(client, filename);
        //把文件内容读出来作为body发回
        cat(client, resource);
    }

    fclose(resource);
}

void bad_request(int client){
    char buf[255];

    sprintf(buf, "HTTP/1.0 400 BAD REQUEST\r\n");
    send(client, buf, sizeof(buf), 0);
    sprintf(buf, "Content-type: text/html\r\n");
    send(client, buf, sizeof(buf), 0);
    sprintf(buf, "\r\n");
    send(client, buf, sizeof(buf), 0);
    sprintf(buf, "<P>Your browser sent a bad request, ");
    send(client, buf, sizeof(buf), 0);
    sprintf(buf, "such as a POST without a Content-Length.\r\n");
    send(client, buf, sizeof(buf), 0);
}

int get_line(int sock, char *buf, int size){
    int i = 0;
    char c = '\0';
    ssize_t n;

    while((i < size -1) && (c != '\n')){
        n = recv(sock, &c, 1, 0);

        if(n > 0){
            if(c == '\r'){
                n = recv(sock, &c, 1, MSG_PEEK);

                if((n > 0) && (c == '\n')){
                    recv(sock, &c, 1, 0);
                }
                else{
                    c = '\n';
                }
            }
            buf[i] = c;
            ++i;
        }else{
            c = '\n';
        }
    }
    buf[i] = '\0';
    return (i);
}


void execute_cgi(int client, const char *path,
                 const char *method, const char *query_string){
    char buf[1024];
    int cgi_output[2];
    int cgi_input[2];
    pid_t pid;
    int status;
    int i;
    char c;
    int numchars = 1;
    int content_length = -1;

    //向buf中填东西以保证能进入下面while
    buf[0] = 'A';
    buf[1] = '\0';

    //如果是GET请求，读取并忽略剩下内容
    if(strcasecmp(method, "GET") == 0){
        while((numchars > 0) && strcmp("\n", buf)){
            numchars = get_line(client, buf, sizeof(buf));
        }
    } else{
        //POST方法，继续读取剩下的内容
        numchars = get_line(client, buf, sizeof(buf));
        //此处只读header内容，忽略body内容
        while((numchars > 0) && strcmp("\n", buf)){
            buf[15] = '\0';
            if(strcasecmp(buf, "Content-Length:") == 0){
                content_length = atoi(&(buf[16]));
            }
            numchars = get_line(client, buf, sizeof(buf));
        }
        if(content_length){
            bad_request(client);
            return;
        }
    }

    sprintf(buf, "HTTP/1.0 200 OK\r\n");
    send(client, buf, sizeof(buf), 0);

    if(pipe(cgi_output) < 0){
        cannot_execute(client);
        return;
    }
    if(pipe(cgi_input) < 0){
        cannot_execute(client);
        return;
    }

    if((pid = fork()) < 0){
        cannot_execute(client);
        return;
    }

    if(pid == 0){
        char meth_env[255];
        char query_env[255];
        char length_env[255];

        //将子进程的输出由标准输出重定向到cgi_output的管道写端上
        dup2(cgi_output[1], 1);
        //将子进程的输入由标准输入重定向到cgi_input的管道读端上
        dup2(cgi_input[0], 0);

        close(cgi_output[0]);
        close(cgi_input[1]);

        sprintf(meth_env, "REQUEST_METHOD=%s", method);

        //将这环境变量加进子进程的运行环境中
        putenv(meth_env);

        //根据http请求的不同方法，构造并存储不同的环境变量
        if(strcasecmp(method, "GET") == 0){
            sprintf(query_env, "QUERY_STRING=%s", query_string);
            putenv(query_env);
        }else{
            sprintf(length_env, "CONTENT_LENGTH=%d", content_length);
            putenv(length_env);
        }

        execl(path, path, NULL);
        exit(0);
    }else{
        close(cgi_output[1]);
        close(cgi_input[0]);

        //如果是POST方法的话就继续读body的内容，并写到cgi_input管道里让子进程去读
        if(strcasecmp(method, "POST") == 0){
            for (int i = 0; i < content_length; ++i) {
                recv(client, &c, 1, 0);
                write(cgi_input[1], &c, 1);
            }
        }

        //从管道中独处子进程的输出，并发送到客户端去
        while(read(cgi_output[0], &c, 1) > 0){
            send(client, &c, 1, 0);
        }

        close(cgi_output[0]);
        close(cgi_input[1]);

        waitpid(pid, &status, 0);
    }
}

void accept_request(int client){
    char buf[1024];
    int numchars;
    char method[255];
    char url[255];
    char path[512];
    size_t i;
    size_t j;   //j表示请求buf
    struct stat st;
    int cgi = 0;    //1 表示是一个cgi程序

    char *query_string = NULL;

    //读请求行
    numchars = get_line(client, buf, sizeof(buf));
    i = 0;
    j = 0;
    while(!ISspace(buf[j]) && (i < sizeof(method) - 1)){
        method[i] = buf[j];
        ++i;
        ++j;
    }
    method[i] = '\0';

    //目前只实现了GET和POST，其余消息发送response告诉客户端未实现
    if(strcasecmp(method, "GET") && strcasecmp(method, "POST")){
        unimplemented(client);
        return;
    }

    //POST则将cgi置1
    if(strcasecmp(method, "POST") == 0){
        cgi = 1;
    }

    i = 0;

    while(ISspace(buf[j]) && (j < sizeof(buf))){
        ++j;
    }

    while(!ISspace(buf[j]) && (i < sizeof(url) - 1) && (j < sizeof(buf))){
        url[i] = buf[j];
        ++i;
        ++j;
    }
    url[i] = '\0';

    //GET请求
    if(strcasecmp(method, "GET") == 0){
        query_string = url;

        while((*query_string != '?') && (*query_string != '\0')){
            ++query_string;
        }

        if(*query_string == '?'){
            cgi = 1;
            *query_string = '\0';
            ++query_string;
        }
    }

    sprintf(path, "../mydocs%s", url);

    if(path[strlen(path) - 1] == '/'){
        strcat(path, "index.html");
    }

    //查询当前文件是否存在
    if(stat(path, &st) == -1){
        while((numchars > 0) && strcmp("\n", buf)){
            numchars = get_line(client, buf, sizeof(buf));
        }
        not_found(client);
    }else{
        //文件存在，与S_IFMT,相与之后值可以用来判断是什么类型文件
        if((st.st_mode & S_IFMT) == S_IFDIR){
            strcat(path, "/index.html");
        }

        //只要下列一个置位，表示其为可执行文件
        if((st.st_mode & S_IXUSR) ||
           (st.st_mode & S_IXGRP) ||
           (st.st_mode & S_IXOTH)){
            cgi = 1;
        }

        if(!cgi){
            serve_file(client, path);
        }else{
            execute_cgi(client, path ,method, query_string);
        }
    }

    close(client);
}



int startup(u_short *port){
    int httpd = 0;

    struct sockaddr_in name;

    httpd = socket(AF_INET, SOCK_STREAM, 0);
    if(httpd == -1){
        error_die("socket");
    }

    memset(&name, 0, sizeof(name));
    name.sin_family = AF_INET;
    name.sin_port = htons(*port);

    name.sin_addr.s_addr = htonl(INADDR_ANY);

    if(bind(httpd, (struct sockaddr *)&name, sizeof(name)) < 0){
        error_die("bind");
    }

    //传进来时port为0，则由系统分配端口号，这是需要获取系统分配的
    if(*port == 0){
        int namelen = sizeof(name);

        if(getsockname(httpd, (struct sockaddr *)&name, &namelen) == -1){
            error_die("getsockname");
        }
        *port = ntohs(name.sin_port);
    }

    if(listen(httpd, 5) < 0){
        error_die("listen");
    }

    return (httpd);
}

void error_die(const char *sc){
    //在当前的标准错误上产生一条错误消息
    perror(sc);
    exit(1);
}

void unimplemented(int client){
    char buf[1024];

    sprintf(buf, "HTTP/1.0 501 Method Not Implemented\r\n");
    send(client, buf, strlen(buf), 0);
    sprintf(buf, SERVER_STRING);
    send(client, buf, strlen(buf), 0);
    sprintf(buf, "Content-Type: txet/html\r\n");
    send(client, buf, strlen(buf), 0);
    sprintf(buf, "\r\n");
    send(client, buf, strlen(buf), 0);
    sprintf(buf, "<HTML><HEAD><TITLE>Method Not Implemented\r\n");
    send(client, buf, strlen(buf), 0);
    sprintf(buf, "</TITLE></HEAD>\r\n");
    send(client, buf, strlen(buf), 0);
    sprintf(buf, "<BODY><P>HTTp request method not supported.\r\n");
    send(client, buf, strlen(buf), 0);
    sprintf(buf, "</BODY></HTML>\r\n");
    send(client, buf, strlen(buf), 0);
}

int main(){
    int server_sock = -1;
    u_short port = 80; //0表示由系统决定
    int client_sock = -1;

    struct sockaddr_in client_name;
    int client_name_len = sizeof(client_name);

    server_sock = startup(&port);
    printf("httpd running on port %d\n", port);

    while(1){
        client_sock = accept(server_sock, (struct sockaddr *)&client_name,
                        &client_name_len);
        if(client_sock == -1){
            error_die("accept");
        }
        accept_request(client_sock);

    }
    close(server_sock);

    return (0);
}

