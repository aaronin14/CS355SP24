#include <stdio.h>

int main() {
    int x = 5;
    int *p = 0; // points to null
    
    printf("x = %2d, p = %p\n", x, p);
    //printf("x = %2d, p = %p, *p = %d\n", x, p, *p);
    
    p = &x;
    printf("x = %2d, *p = %d, p = %p\n", x, *p, p);

    x = 15; // &p is the address of p
    printf("x = %2d, *p = %d, p = %p, &p = %p\n", x, *p, p, &p);

    *p = 17; // this point at the variable x, the same as x = 17
    printf("x = %2d, *p = %d, p = %p\n", x, *p, p);
   
    int y = 50;
    printf("x = %2d, y = %2d, *p = %d, p = %p\n", x, y, *p, p);
    
    p = &y;
    printf("x = %2d, y = %2d, *p = %d, p = %p\n", x, y, *p, p);
    return 0;
}
