#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
	int fd;
	char buffer[1024];
	int numbytes;

	fd=open("example.txt", O_RDONLY);
	while((numbytes=read(fd,buffer,1024))>0) {
		printf("%s", buffer);
	}
	if(numbytes<0) {
		perror("example.txt");
		return 1;
	}
	close(fd);
	return 0;
}
