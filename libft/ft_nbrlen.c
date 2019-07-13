#include "libft.h"

long long int ft_nbrlen(unsigned long long int n)
{
    long long int 	len;


	len = (n > 0) ? 0 : 1;
	while (n != 0)
	{
		n = n / 10;
		len++;
	}
	return (len);
}