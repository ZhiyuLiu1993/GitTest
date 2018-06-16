#include <stdio.h>  
#include <stdlib.h>  
#include <string.h>  
#include <malloc.h>  
#include <sys/types.h>  
#include <errno.h>  
#include <sys/stat.h>  
#include <fcntl.h>  
#include <sys/select.h>  
#include <unistd.h>  
#include <termios.h>  
#include <sys/stat.h>  
/**********定时器头文件***************/  
#include <sys/time.h>  
#include <signal.h>  
/***********进程间SOCKET通信头文件**********/  
#include <sys/socket.h>  
#include <sys/un.h>  

#define UNIX_DOMAIN "/tmp/.dis_msg"  
typedef struct _key_args  
{  
	unsigned int key;  
	union {   
		u_int32_t ipv4_addr;  
		u_int32_t ipv6_addr[4];  
	} sip;    
	union {   
		u_int32_t ipv4_addr;  
		u_int32_t ipv6_addr[4];   
	} dip;  
	unsigned short sport;  
	unsigned short dport;  
	unsigned char protocol;  
	unsigned short match_type;  
	unsigned short iptype;  
	unsigned short mask;  
	int core_id;  
}key_args_t;  
typedef struct _dis_msg_buff  
{  
	long mtype;  
	unsigned int key;  
	int core_num;  
	int msg_type;  
	key_args_t karg;  
}dis_msg_buff_t;  

int main()  
{  
	socklen_t clt_addr_len;  
	int listen_fd;  
	int com_fd;  
	int ret=0;  
	char reerrno = 0;  
	int i;  
	dis_msg_buff_t msg;  

	int len;  
	struct sockaddr_un clt_addr;  
	struct sockaddr_un srv_addr;  
	//创建用于通信的套接字，通信域为UNIX通信域  
	listen_fd=socket(AF_UNIX,SOCK_STREAM,0);  
	if(listen_fd<0)  
	{  
		printf("SERVER:cannot create listening socket\n");  
		return -1;  
	}  
	//设置服务器地址参数  
	srv_addr.sun_family=AF_UNIX;  
	strncpy(srv_addr.sun_path,UNIX_DOMAIN,sizeof(srv_addr.sun_path)-1);  
	unlink(UNIX_DOMAIN);  
	//绑定套接字与服务器地址信息  
	ret=bind(listen_fd,(struct sockaddr*)&srv_addr,sizeof(srv_addr));  
	if(ret==-1)  
	{  
		printf("cannot bind server socket\n");  
		close(listen_fd);  
		unlink(UNIX_DOMAIN);  
		return -1;   
	}  
	//对套接字进行监听，判断是否有连接请求  
	ret=listen(listen_fd,1);  
	if(ret==-1)  
	{  
		printf("cannot listen the client connect request\n");  
		close(listen_fd);  
		unlink(UNIX_DOMAIN);  
		return -1;   
	}  
	chmod(UNIX_DOMAIN,00777);//设置通信文件权限  
	//当有连接请求时，调用accept函数建立服务器与客户机之间的连接  
	len=sizeof(clt_addr);  
	com_fd=accept(listen_fd,(struct sockaddr*)&clt_addr, (socklen_t *)&len);  
	if(com_fd<0)  
	{  
		printf("cannot accept client connect request");  
		close(listen_fd);  
		unlink(UNIX_DOMAIN);  
		return -1;   
	} 
	/*------------------------通信100w次---------------------------*/    
	while(1){  
		//读取并输出客户端发送过来的连接信息  
		memset(&msg,0x00,sizeof(msg));  
		int recv_php_num=read(com_fd,&msg,sizeof(msg));  
		if (recv_php_num <= 0){  
			printf("read error\n");  
			return -1;  
		}  
		reerrno = 1;  
		write(com_fd,&reerrno,sizeof(reerrno));  
		reerrno = 0;  
	}  
} 
