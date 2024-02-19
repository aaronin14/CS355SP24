#include <stdio.h>
#include <string.h>

struct dataRecord {
    int iId;
    int iAge;
    float fSalary;
    char strName[100];
};

void printDataRecord(const struct dataRecord *p) {
    printf("%s is %d years old, and their salary is %.2f.\n", 
        p->strName, p->iAge, p->fSalary);
}


int main() {
    struct dataRecord John;
    John.iId = 10;
    John.iAge = 25;
    John.fSalary = 100000.00;
    strcpy(John.strName,"John");
    printDataRecord(&John);

    struct dataRecord *alias = 0;
    alias = &John;
    alias->fSalary +=10000;
    printDataRecord(alias);

    return 0;
}