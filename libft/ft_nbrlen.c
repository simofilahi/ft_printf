#include "libft.h"
//
#include <stdio.h>

int ft_nbrlen(long long int n, int flag)
{
    int 	len;


	len = (n > 0) ? 0 : 1;
	while (1)
	{
		n /= (flag == 1) ? 2 : 10;
		if (n <= 0)
			break ;
		len++;
	}
	return (len);
}