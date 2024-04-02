#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <utmp.h>

int main() {
	struct utmp currentRecord;
	int recordLength = sizeof(currentRecord);
	int fd;
	fd=open("/var/run/utmp", O_RDONLY);
	if (fd==-1) {
		perror("/var/run/utmp");
		return 1;
	}
	while((read(fd, &currentRecord, recordLength))>0) {
		printf("User: %s\n", currentRecord.ut_user);
		printf("Terminal: %s\n", currentRecord.ut_line);
		printf("\n");
	}
	close(fd);
	return 0;
}
