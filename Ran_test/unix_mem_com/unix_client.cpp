#include <stdio.h>  
#include <stdlib.h>  
#include <sys/ipc.h>  
#include <sys/types.h>  
#include <sys/socket.h>  
//#include <sys/time.h>  
#include <unistd.h>
#include <sys/un.h>  
#include <errno.h>  
//#include <string.h>  
#include <time.h>

#define DIS_MSG_FILE "/tmp/.dis_msg"  

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
	int i = 0;  
	int fd = 0;  
	int len = 0;  
	int ret = 0;  
	char reerrno = 0;  
	struct sockaddr_un addr;  
	dis_msg_buff_t msg;  
	time_t t;  
	t = time(NULL);  

	fd = socket(AF_UNIX, SOCK_STREAM, 0);  
	if (fd < 0){  
		printf("CLIENT: socket error\n");  
		return -1;  
	}  

	memset(&addr, 0x00, sizeof(struct sockaddr_un));  
	addr.sun_family = AF_UNIX;  
	strncpy(addr.sun_path, DIS_MSG_FILE,strlen(DIS_MSG_FILE));  

	len = sizeof(addr.sun_family);  
#ifdef HAVE_SUN_LEN  
	len = addr.sun_len = SUN_LEN(&addr);  
#else  
	len = sizeof (addr.sun_family) + strlen (addr.sun_path);  
#endif /* HAVE_SUN_LEN */  
	ret = connect(fd, (struct sockaddr *)&addr, len);  
	if (ret<0){  
		printf("CLIENT: connect error\n");  
		return -1;  
	}  

	/*------------------------通信100w次---------------------------*/  
	while(i++ < 1000000){  
		memset(&msg, 0x00, sizeof(msg));  
		if(write(fd, &msg, sizeof(msg)) < 0)  
		{  
			printf("CLIENT: write error\n");  
			goto err;  
		}  
		while(1){  
			int nbytes;  
			reerrno = 0;  
			nbytes = read(fd, &reerrno, sizeof(reerrno));  
			if (nbytes <= 0 && errno != EINTR)  
				goto err;  
			if (nbytes > 0){  
				if (reerrno == 1)  
					break;  
				else  
					goto err;  
			}  
		}  
	}  
	/*------------------------通信100w次-结束--------------------------*/  
	close(fd);  
	printf("CLIENT: success  %d\n", (time(NULL)-t));  
	return 0;  
err:  
	close(fd);  
	printf("CLIENT: failed\n");  
	return -1;  
}  
