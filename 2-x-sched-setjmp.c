#include <stdio.h>
#include <setjmp.h>

jmp_buf a_ment;

void a()
{
    int retval = setjmp(a_ment);
    switch (retval) {
        case 0: //mikor mentjük a kontextust
            printf("Hello!\n");
            longjmp(a_ment, 1);
            break;
        case 1: //mikor longjmp(a_ment, 1) ugrik ide
            printf("jmp 2\n");
            longjmp(a_ment, 2);
            break;
        case 2:
            printf("jmp 3\n");
            longjmp(a_ment, 3);
            break;
        case 3:
            printf("bye\n");
            return;
    }
}

int main()
{
    a();
    return 0;
}