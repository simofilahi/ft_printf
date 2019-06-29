#include "ft_printf.h"

void debug(t_var v)
{
    printf("v.pres ==> %d\n", v.pres);
    printf("v.width ==> %d\n", v.width);
    printf("v.flag ==> %c\n", v.flag);
}

void print(int count, char c)
{
    if (count <= 0)
        return ;
    while (count--)
        ft_putchar(c);
}

int   calcu_for_signs(t_var v, int len, int sign)
{
    len = (v.flag == '+' &&  sign == 0) ? len + 1 : len;
    len = (sign == 1) ? len + 1 : len;
    return (len);
}

void   apply_signs(t_var v, int sign)
{
    (sign == 1) ? ft_putchar('-') : 0;
    (v.flag == '+' && sign == 0) ? ft_putchar('+') : 0;
}

int    apply_width(t_var v, int len, int n, int sign, int flag)
{
    len = calcu_for_signs(v, len, sign);
    if (v.flag == -1 || v.flag == '0' || v.flag == '+')
    {
        print(v.width - len, ' ');
        (flag == 1) ? apply_signs(v, sign) : 0;
        (flag == 1) ? ft_putnbr(n) : 0;
    }
    else
    {
        (flag == 1) ? apply_signs(v, sign) : 0;
        (flag == 1) ? ft_putnbr(n) : 0;
        print(v.width - len, ' ');
    }
    return((v.width > len) ? v.width : len);
}


int    apply_pres(t_var v, int len, int n, int sign)
{
    apply_signs(v, sign);
    print(v.pres - len, '0');
    ft_putnbr(n);
    len = calcu_for_signs(v, len, sign);
    if (sign == 1 || v.flag == '+')
        len = v.pres + 1;
    return (len);
}

int     apply_width_pres(t_var v, int len, int n, int sign)
{
    int ret = 0;
    int i;

    if (v.pres > len)
        i = v.pres;
    else
        i = len;
    if (v.flag == '+' || v.flag == '0' || v.flag == -1)
    {
        ret = apply_width(v, i, n, sign, 0);
        apply_pres(v, len, n, sign);
    }
    else if (v.flag == '-')
    {
        apply_pres(v, len, n, sign);
        len = v.pres;
        ret = apply_width(v, len, n, sign, 0);
    }
    return(ret);
}

int     conv_d(char *s, va_list args)
{
    t_var v;
    int  n;
    int len;
    int sign;

    v = fill_structure(s);
    n = va_arg(args, int);
    sign = (n < 0) ? 1 : 0;
    n *= (sign == 1) ? -1 : 1;
    len = ft_nbrlen(n);
    if (v.width != -1 && v.pres == -1)
        return (apply_width(v, len, n, sign, 1));
    else if (v.width == -1 && v.pres != -1)
        return (apply_pres(v, len, n, sign));
    else if (v.width != -1 && v.pres != -1)
        return (apply_width_pres(v, len, n, sign));
    return (0);
}
