#include <stdio.h>
#include "includes/ft_printf.h"
#include <limits.h>

int main()
{
    int ret;


  
    ret = ft_printf("%X|%-X|%#X|%0X", UINT_MAX, UINT_MAX, UINT_MAX, UINT_MAX);
    printf("ret %d\n", ret);
   ret = printf("%X|%-X|%#X|%0X", UINT_MAX, UINT_MAX, UINT_MAX, UINT_MAX);
    printf("ret %d\n", ret);
    return 0;
}

//(  2 147 483 649  )
//(  5 000 000 000  )
