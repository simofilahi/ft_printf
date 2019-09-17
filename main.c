#include <stdio.h>
#include "includes/ft_printf.h"
#include <limits.h>
#include <math.h>


int main()
{
    int ret;
    // double f = 0;
    
    ret = ft_printf("%.f|%-.f|%+.f|% .f|%#.f|%0.f", 42., 42., 42., 42., 42., 42.);
      printf("ret %d\n", ret);
    ret = printf("%.f|%-.f|%+.f|% .f|%#.f|%0.f", 42., 42., 42., 42., 42., 42.);
    printf("ret %d\n", ret);
    return 0;  
}

//(  2 147 483 649  )
//(  
    
  
// 1100100001001100110011001100110011001100110011001101
// 110010000100110011001100110011001
      
      
    //   5 000 000 000  )
