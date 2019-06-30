#include <stdio.h>

int main()
{
    int ret;

 /*   ret = printf("%+5d\n", 12);
    printf("ret ==> %d\n", ret);
    ret = printf("%-4d\n", -12);
    printf("ret ==> %d\n", ret);*/
 /*   ret = printf("%04d\n", 12);
    printf("ret ==> %d\n", ret);*/
/*    ret = printf("%.3d\n", 1337);
    printf("ret ==> %d\n", ret);
     ret = printf("%4c\n", 'a');
    printf("ret ==> %d\n", ret);
     ret = printf("%.2s\n", "hello");
     printf("ret ==> %d\n", ret);*/
 /*    ret = printf(" %-#10d \n", 12);
      printf("ret ==> %d\n", ret);*/
    ret = printf("%-1c\n", 'm');
    printf("ret ==> %d\n", ret);
    printf("%lu", sizeof(long long int));
    return 0;
}