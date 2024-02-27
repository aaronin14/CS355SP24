#include <fcntl.h> // File Control
#include <stdio.h>
#include <unistd.h>
#include <utmp.h>

int main() {
  printf("UTMP file is %s\n", UTMP_FILE);
  int intUTMPfile;
  struct utmp currentRecord;
  int intUTMPlength = sizeof(currentRecord);
  intUTMPfile = open(UTMP_FILE, O_RDONLY);

  while (read(intUTMPfile, &currentRecord, intUTMPlength) == intUTMPlength)
    printf("%s %s.\n", currentRecord.ut_user, currentRecord.ut_host);
  close(intUTMPfile);
  return 0;
}
