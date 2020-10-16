#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>

int main(void)
{
	int fd,n;
	char buf[1024];
	
	
	fd = open("/tmp/mi_fifo",O_RDONLY);
	n=read(fd,buf,sizeof(buf));
	printf("RX mensaje:%s\n",buf);
	printf("Numero de bytes:%d\n",n);
	close(fd);
	
	return 0;
}
