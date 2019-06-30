#include "ft_printf.h"

char    *hex(int long n)
{
    int i;
    int res;

    char *hexa;

    i = 0;
    res = 0;
    if (!(hexa = (char *)malloc(sizeof(char) * 100)))
        return (NULL);
    while (n / 16 > 0)
    {
        res = n % 16; 
        if (res < 10)
            hexa[i++] = res + '0';
        else
            hexa[i++] = res + 'a' - 10;
        n /= 16;
    }
    hexa[i] = '\0';
    ft_strrev(hexa);
    return (hexa);
}

char    *octal(long long int n)
{
    char *octal;
    int i;

    if (!(octal = (char *)malloc(sizeof(char) * 100)))
        return (0);
    i = 0;
    while (1)
    {
        octal[i] = n % 8 + '0';
        n = n / 8;
        i++;
        if (n <= 0)
         break;
    }
    octal[i] = '\0';
    ft_strrev(octal);
    return (octal);
}

char			*ft_llitoa(long long int n)
{
	char                *s;
	int                 sign;
	long long int 		len;

	sign = 0;
	len = ft_nbrlen(n);
	if (n < 0)
	{
		n = -n;
		sign = 1;
	}
	if (!(s = (char *)malloc(sizeof(char) * len + 1)))
		return (NULL);
	s[len] = '\0';
	while (len--)
	{
		s[len] = (n % 10) + 48;
		n /= 10;
	}
	if (sign)
		s[0] = '-';
	return (s);
}