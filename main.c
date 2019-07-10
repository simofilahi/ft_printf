#include <stdio.h>
#include "includes/ft_printf.h"

//#define INT_MIN -214748364

int main()
{
    int ret;

   // int long long var = 400000000000000000;
   // ret = ft_printf("%.5 000 000 000d\n", 100);
  //  printf("ret ==> %d\n", ret);
  //  printf("**************************\n");
  //  printf("**************************\n");

    //ret = ft_printf("%d|%-d|%+d|% d|%0d", INT_MIN, INT_MIN, INT_MIN, INT_MIN, INT_MIN);
//    printf("ret ==> %d\n", ret);
  //  ret = printf("%d|%-d|%+d|% d|%0d", INT_MIN, INT_MIN, INT_MIN, INT_MIN, INT_MIN);
    //printf("ret ==> %d\n", ret);

   // int var = 0;
  
    ret = ft_printf("%05d\n", -10);
    printf("ret %d\n", ret);
     ret = printf("%05d\n", -10);
    printf("ret %d\n", ret);
    return 0;
}

//(  2 147 483 649  )
//(  5 000 000 000  )
