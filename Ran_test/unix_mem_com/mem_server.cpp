#include <stdio.h>
#include <stdlib.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include <errno.h>
#include <unistd.h>

#define MY_SHM_ID 815

struct shared_use_at{
	int written_by_you;
	char some_text[72];
};

int main()
{
	printf("page size = %d\n", getpagesize());
	int shmid, ret;
	shmid = shmget(MY_SHM_ID, sizeof(struct shared_use_at), 0666|IPC_CREAT);
	if(shmid > 0)
		printf("Create a shared memory segment %d\n", shmid);
	struct shmid_ds shmds;
	ret = shmctl(shmid, IPC_STAT, &shmds);
	if(ret == 0){
		printf("Size of memory segment is %d\n", (int)shmds.shm_segsz);
		printf("Number of attches %d\n", (int)shmds.shm_nattch);
	}else{
		printf("shmctl() call failed\n");
	}

	int running = 1;
	int arunning = 1;
	void *shared_memory = (void *)0;
	struct shared_use_at *shared_stuff;
	shared_memory = shmat(shmid, (void *)0, 0);
	if(shared_memory == (void*)-1){
		printf("shmat failed\n");
		exit(0);
	}
	shared_stuff = (struct shared_use_at *)shared_memory;
	shared_stuff->written_by_you = 0;

	/*------------------------通信100w次---------------------------*/
	while(running++){
		if(shared_stuff->written_by_you){
			if(shared_stuff->some_text[0] == 'o')
				arunning++;
			if(shared_stuff->some_text[0] == 'k')
				break;
			shared_stuff->written_by_you = 0;
		}
	}
	/*------------------------通信100w次--结束-------------------------*/
	printf("arunning = %d, running = %d \n", arunning, running);
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

