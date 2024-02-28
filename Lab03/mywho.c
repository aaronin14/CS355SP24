#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <utmp.h>

void printInfo(int );

int main() {
    struct utmp currentRecord;
    int intUTMPlength = sizeof(currentRecord);
    int intUTMPfile;
    intUTMPfile = open(UTMP_FILE, O_RDONLY);
    while (read(intUTMPfile, &currentRecord, intUTMPlength) == intUTMPlength) {
        printf("%-4s\t %-8s\t %d (%s)\n", currentRecord.ut_user, currentRecord.ut_line,
                currentRecord.ut_tv.tv_sec, currentRecord.ut_host);
        printInfo(currentRecord.ut_tv.tv_sec);
    }
    close(intUTMPfile);
    return 0;
}

void printInfo(int t) {
    int d = t / 86400;
    printf("%d ", d);
    int y = d / 365;
    printf("%d ", y);
}
