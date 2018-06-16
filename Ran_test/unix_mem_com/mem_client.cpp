#include <stdio.h>
#include <stdlib.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include <errno.h>
#include <string.h>
#include <time.h>

#define MY_SHM_ID 815

struct shared_use_at{
	int written_by_you;
	char some_text[72];
};

int main()
{
	int shmid, ret;
	time_t t;
	t = time(NULL);

	shmid = shmget(MY_SHM_ID, sizeof(struct shared_use_at), 0666);
	if(shmid > 0)
		printf("Create a shared memory segment %d\n", shmid);
	else if(shmid == EEXIST){
		printf("shared memory is exist!\n");
		exit(0);
	}
	printf("shmid = %d, EEXIST = %d\n", shmid, EEXIST);
	struct shmid_ds shmds;
	ret = shmctl(shmid, IPC_STAT, &shmds);
	if(ret == 0){
		printf("Size of memory segment is %d\n", (int)shmds.shm_segsz);
		printf("Number of attches %d\n", (int)shmds.shm_nattch);
	}else{
		printf("shmctl() call failed\n");
	}

	int running = 1;
	char buffer[100] = {0};
	void *shared_memory = (void *)0;
	struct shared_use_at *shared_stuff;
	shared_memory = shmat(shmid, (void *)0, 0);
	if(shared_memory == (void*)-1){
		printf("shmat failed\n");
		exit(0);
	}
	shared_stuff = (struct shared_use_at *)shared_memory;

	/*------------------------通信100w次---------------------------*/
	while(running++<1000000){
		while(shared_stuff->written_by_you == 1){
		}
		memset(shared_stuff->some_text, 0x00, 72);
		shared_stuff->some_text[0] = 'o';
		shared_stuff->written_by_you = 1;
	}
	/*------------------------通信100w次--结束-----------------------*/

	printf("time = %d\n", (int)(time(NULL) - t));
	shared_stuff->some_text[0] = 'k';
	shared_stuff->written_by_you = 1;
	ret = shmdt(shared_memory);
	if(ret == 0)
		printf("shmdt memory \n");
	else 
		printf("shmdt memory failed \n");

	ret = shmctl(shmid, IPC_RMID, 0);
	if(ret == 0)
		printf("shared memory removed \n");
	else
		printf("shared memory removed failed\n");
	return 0;

}
