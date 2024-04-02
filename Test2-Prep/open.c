#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
	int file_descriptor;
	file_descriptor=open("example.txt", O_RDONLY);
	if(file_descriptor<0) {
		perror("example.txt");
		return 1;
	} else {
		printf("Open file successfully\n");
		close(file_descriptor);
		return 0;
	}
}
