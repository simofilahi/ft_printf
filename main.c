#include <stdio.h>
#include "includes/ft_printf.h"
#include <limits.h>
#include <math.h>


int main()
{
    int ret;
    double f = 112.42;
    
    ret = ft_printf("%.f\n", 1.5);
    printf("ret %d\n", ret);
    ret = printf("%.f\n", 2.50);
    printf("ret %d\n", ret);
    // ft_printf("|%.f|%.10f|%.1f|%.6f|\n", f,f,f,f);
    // printf("|%.f|%.100f|%.1f|%.6f|\n", f,f,f,f);
    return 0;
}

//(  2 147 483 649  )
//(  
    
  
// 1100100001001100110011001100110011001100110011001101
// 110010000100110011001100110011001
      
      
    //   5 000 000 000  )