#include "ft_printf.h"

char			*ft_llitoa_base(unsigned long long int n, t_properties v)
{
	char                *s;
	long long int 		len;
    int                 i;

	len = ft_nbrlen(n);
	if (!(s = (char *)malloc(sizeof(char) * (len + 1))))
		return (NULL);
    i = 0;
	while (1)
	{
        if (((n % v.base) >= 10) && (v.base == 16) && (v.type == 'x' || v.type == 'p')) 
            s[i] = (n % v.base) + 'a' - 10;
        else if (((n % v.base) >= 10) && (v.base == 16 && v.type == 'X'))
            s[i] = (n % v.base) + 'A' - 10;
        else
            s[i] = (n % v.base) + '0';
		n /= v.base;
        i++;
        if (n <= 0)
          break;
	}
    s[i] = '\0';
    ft_strrev(s);
	return (s);
}