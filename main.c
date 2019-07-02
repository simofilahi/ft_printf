#include <stdio.h>
#include "includes/ft_printf.h"

int main()
{
    int ret;

   // int long long var = 400000000000000000;
    ret = ft_printf("%0.5d", 0);
    printf("ret ==> %d\n", ret);
    printf("**************************\n");
    printf("**************************\n");
    ret = printf("%0.5d", 0);
    printf("ret ==> %d\n", ret);
    return 0;
}
