#include <stdio.h>
#include <fcntl.h>
#include <utmp.h>
#include <unistd.h>

int main() {
    int intUTMPfile;
    struct utmp currentRecord;
    int intUTMPlength = sizeof(currentRecord);
    intUTMPfile = open(UTMP_FILE, O_RDONLY);

    while (read(intUTMPfile, &currentRecord, intUTMPlength) == intUTMPlength)
        printf("%-8s %-8s %d (%s)\n", currentRecord.ut_user,
                currentRecord.ut_line, currentRecord.ut_tv.tv_sec, currentRecord.ut_host);

    close(intUTMPfile);
    return 0;


}
