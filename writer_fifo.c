#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>

int main(void)
{
	int fd;
	char buff[]= "mensaje..";
	mkfifo("/tmp/mi_fifo",0666);
	fd =open("/tmp/mi_fifo",O_WRONLY);
	write(fd,buff,sizeof(buff));
	close(fd);
	
	return 0;
}
