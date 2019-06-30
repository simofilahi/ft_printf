#include "ft_printf.h"

void debug(t_var v)
{
    printf("v.pres ==> %d\n", v.pres);
    printf("v.width ==> %d\n", v.width);
    printf("v.f_flag ==> %c\n", v.f_flag);
    printf("v.s_flag ==> %c\n", v.s_flag);
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
    if ((v.f_flag == '+' || v.f_flag == '#' || v.s_flag == '#') && (sign == 0))
         len += 1;
    len = (sign == 1) ? len + 1 : len;
    return (len);
}

void   apply_signs(t_var v, int sign)
{
    (sign == 1) ? ft_putchar('-') : 0;
    (v.f_flag == '+' && sign == 0) ? ft_putchar('+') : 0;
    (v.f_flag == '#' || v.s_flag == '#') ? ft_putchar('0') : 0;
}

int    apply_width(t_var v, int len, char *s, int sign, int flag)
{
    len = calcu_for_signs(v, len, sign);
   if ((v.f_flag == '-' || v.s_flag == '-' ||\
       v.f_flag == '#' || v.s_flag == '#') &&\
      !(v.f_flag == '#' && v.s_flag == -1))
    {
        (flag == 1) ? apply_signs(v, sign) : 0;
        (flag == 1) ? ft_putstr(s) : 0;
        (len == 1) ? ft_putchar(*s) : 0;
        print(v.width - len, ' ');
    }
    if (v.f_flag == -1 ||\
        v.f_flag == '0' ||\
        v.f_flag == '+' ||\
       (v.f_flag == '#' && v.s_flag == -1))
    {
        print(v.width - len, ' ');
        (flag == 1) ? apply_signs(v, sign) : 0;
        (flag == 1) ? ft_putstr(s) : 0;
        (len == 1) ? ft_putchar(*s) : 0;
    }
    return((v.width > len) ? v.width : len);
}


int    apply_pres(t_var v, int len, char *s, int sign)
{
    apply_signs(v, sign);
    len = calcu_for_signs(v, len, sign);
    print(v.pres - len, '0');
    ft_putstr(s);
    len = calcu_for_signs(v, len, sign);
    if (sign == 1 || v.f_flag == '+')
        len = v.pres + 1;
    return ((len > v.pres) ? len : v.pres);
}

int     apply_width_pres(t_var v, int len, char *s, int sign)
{
    int ret;
    int i;

    ret = 0;
    if (v.pres > len)
        i = v.pres;
    else
        i = len;
    if (v.f_flag == '-')
    {
        apply_pres(v, len, s, sign);
        len = (v.pres > len) ? v.pres : len;
        ret = apply_width(v, len, s, sign, 0);
    }
    else
    {
        if (v.f_flag == '#' && v.pres > len)
            v.f_flag = -1;
        ret = apply_width(v, i, s, sign, 0);
        apply_pres(v, len, s, sign);
    }
    return(ret);
}