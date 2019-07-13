#include "ft_printf.h"

// char    *binary(unsigned long long int n)
// {
//     int i;
//     int len;
//     char *bin;

//     len = ft_nbrlen(n);
//     if (!(bin = (char *)malloc(sizeof(char) * (len + 1))))
//         return (NULL);
//     i = 0;
//     while (1)
//     {
//         bin[i] = n % 2;
//         n /= 2;
//         if (n == 0)
//          break ;
//         i++;
//     }
//     bin[i] = '\0';
//     ft_strrev(bin);
//     return (bin);
// }

// char    *hex(unsigned long long int n, int flag)
// {
//     int len;
//     int i;
//     int res;
//     char *hexa;

//     i = 0;
//     res = 0;
//     len = ft_nbrlen(n);
//     if (!(hexa = (char *)malloc(sizeof(char) * (len + 1))))
//         return (NULL);
//     while (1)
//     {
//         res = n % 16; 
//         if (res < 10)
//             hexa[i++] = res + '0';
//        else if (flag == 0)
//             hexa[i++] = res + 'a' - 10;
//         else
//             hexa[i++] = res + 'A' - 10;
//         n /= 16;
//         if (n == 0)
//          break ;
//     }
//     hexa[i] = '\0';
//     ft_strrev(hexa);
//     return (hexa);
// }

// char    *octal(unsigned long long int n)
// {
//     char *octal;
//     int len;
//     int i;

//     len = ft_nbrlen(n);
//     if (!(octal = (char *)malloc(sizeof(char) * (len + 1))))
//         return (0);
//     i = 0;
//     while (1)
//     {
//         octal[i] = n % 8 + '0';
//         n = n / 8;
//         i++;
//         if (n <= 0)
//          break;
//     }
//     octal[i] = '\0';
//     ft_strrev(octal);
//     return (octal);
// }

char			*ft_llitoa_base(unsigned long long int n, int base, int flag)
{
	char                *s;
    long long int       res;
	long long int 		len;
    int                 i;


	len = ft_nbrlen(n);
	if (!(s = (char *)malloc(sizeof(char) * (len + 1))))
		return (NULL);
    res = 0;
    i = 0;
	while (1)
	{
        res = n % base;
        if (res >= 10 && base == 16 && flag == 0) 
            s[i] = res + 'a' - 10;
        else if (res >= 10 && base == 16 && flag == 1)
            s[i] = res + 'A' - 10;
        else
            s[i] = res + '0';
		n /= base;
        i++;
        if (n <= 0)
          break;
	}
    s[i] = '\0';
    ft_strrev(s);
	return (s);
}