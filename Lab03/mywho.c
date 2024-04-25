#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <utmp.h>

int main() {
    struct utmp currentRecord;
    int intUTMPlength = sizeof(currentRecord);
    int intUTMPfile;
    intUTMPfile = open(UTMP_FILE, O_RDONLY);
    while (read(intUTMPfile, &currentRecord, intUTMPlength) == intUTMPlength) {
        printf("%-8s\t %-8s\t %d (%s)\n", currentRecord.ut_user, currentRecord.ut_line,
                currentRecord.ut_tv.tv_sec, currentRecord.ut_host);
    }
    close(intUTMPfile);
    return 0;
}
