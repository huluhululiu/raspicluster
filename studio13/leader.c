#include <fcntl.h>
#include <stdio.h>
#include <sys/mman.h>
#include <unistd.h>
#include <sys/types.h>
#include <time.h>
#include <string.h>
#include "shared_memstudio.h"

int main(int argc, char *argv[]) {
	int fd;
	struct shared_data sharedData;
	int n = sizeof(sharedData.data)/sizeof(sharedData.data[0]);
	int a[n];
	int i = 0;
	for(i = 0; i < n; i++) {
		srand((unsigned)time(NULL));
		a[i] = rand();
	}
	memcpy(sharedData.data, a, n);
	fd = shm_open("Studio13_memory", O_RDWR | O_CREAT, S_IRWXU);
	ftruncate(fd,sizeof(sharedData));
	void *p;
	p = mmap(NULL,sizeof(sharedData),PROT_READ|PROT_WRITE,MAP_SHARED,fd,0);
	for(i = 0; i < n; i++) {
		printf("%i\n", sharedData.data[i]);
	}
	return 0;
}