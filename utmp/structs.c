#include <stdio.h>
#include <string.h>

struct dataRecord {
  int intId;
  int intAge;
  float fSalary;
  char strName[100];
};

void printDataRecord(const struct dataRecord *p) {
  printf("%s is %d years old, and their salary is %.2f.\n", p->strName,
         p->intAge, p->fSalary);
}
int main() {
  struct dataRecord John;
  John.intId = 12345;
  John.intAge = 25;
  John.fSalary = 100.25;
  strcpy(John.strName, "John");
  printDataRecord(&John);

  struct dataRecord *alias = 0;
  alias = &John;

  // These 2 methods will do the same thing
  alias->fSalary += 10;
  (*alias).fSalary += 15;
  printDataRecord(alias);
  printDataRecord(&John);
}
