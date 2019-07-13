#include <stdio.h>
#include "includes/ft_printf.h"
#include <limits.h>

int main()
{
    int ret;


  
    ret = ft_printf("%p ==>", &printf);
    printf("ret %d\n", ret);
    ret = printf("%p ==>", &printf);
    printf("ret %d\n", ret);
    return 0;
}

//(  2 147 483 649  )
//(  5 000 000 000  )
