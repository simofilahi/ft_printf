#include "ft_printf.h"

char    *hex(int long n)
{
    int i;
    int res;

    char *hexa;

    i = 0;
    res = 0;
    hexa = (char *)malloc(sizeof(char) * 100);
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