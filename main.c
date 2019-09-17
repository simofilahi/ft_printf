#include <stdio.h>
#include "includes/ft_printf.h"
#include <limits.h>
#include <math.h>


int main()
{
    int ret;
    // double f = 0;
    
    ret = ft_printf("%-#1x|%-01x|%#01x|%-#01x", 0U, 0U, 0U, 0U);
      printf("ret %d\n", ret);
    ret = printf("%-#1x|%-01x|%#01x|%-#01x", 0U, 0U, 0U, 0U);
    printf("ret %d\n", ret);
    return 0;  
}

//(  2 147 483 649  )
//(  
    
  
// 1100100001001100110011001100110011001100110011001101
// 110010000100110011001100110011001
      
      
    //   5 000 000 000  )
