#include <stdio.h>
#include "includes/ft_printf.h"
#include <limits.h>

int main()
{
    int ret;


  
    ret = ft_printf("%-#.5hho|%-0.5hho|%#0.5hho|%-#0.5hho", ULLONG_MAX, ULLONG_MAX, ULLONG_MAX, ULLONG_MAX);
    printf("ret %d\n", ret);
   ret = printf("%-#.5hho|%-0.5hho|%#0.5hho|%-#0.5hho", ULLONG_MAX, ULLONG_MAX, ULLONG_MAX, ULLONG_MAX);
    printf("ret %d\n", ret);
    return 0;
}

//(  2 147 483 649  )
//(  5 000 000 000  )
