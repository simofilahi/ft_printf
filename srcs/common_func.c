#include "ft_printf.h"

int is_dot(char *s)
{
    while (*s)
        if (*s++ == '.')
            return (1);
    return (0);
}

void debug(t_var v)
{
    ft_putstr("v.pres ==> ");
    ft_putnbr(v.pres);
    ft_putchar('\n');
    ft_putstr("v.width ==> ");
    ft_putnbr(v.width);
    ft_putchar('\n');
    ft_putstr("v.f_flag ==> ");
    ft_putnbr(v.f_flag);
    ft_putchar('\n');
    ft_putstr("v.s_flag ==> ");
    ft_putnbr(v.s_flag);
    ft_putchar('\n');
    ft_putstr("v.v_length ==> ");
    ft_putchar('\n');
    ft_putendl(v.length);
}

void print(int count, char c)
{
    if (count <= 0)
        return ;
    while (count--)
        ft_putchar(c);
}

int    apply_width(t_var v, int len, char *s, int flag)
{
    if (v.f_flag == '-')
    {
        ft_putchar('H');
        (flag == 1 && len > 1) ? ft_putstr(s) : 0;
        (len == 1) ? ft_putchar(*s) : 0;
        print(v.width - len, ' ');
    }
    else
    {
        //ft_putchar('H');
        print(v.width - len, ' ');
        (flag == 1 && len > 1) ? ft_putstr(s) : 0;
        (len == 1) ? ft_putchar(*s) : 0;
    }
    return((v.width > len) ? v.width : len);
}


int    apply_pres(t_var v, int len, char **str, int sign)
{
    char *src;

    (void)sign;
    src = NULL;
    if (v.pres < len && v.type == 's')
        *str = ft_strsub(*str, 0, v.pres);
    else if (v.pres > len && v.type != 's')
    {
       src = ft_strnew(v.pres - len);
       src = (char *)ft_memset(src, '0', v.pres - len);
       *str = ft_strjoin(src, *str);
    }
    len = (int)ft_strlen(*str);
    return (len);
}

int     apply_width_pres(t_var v, int len, char *s, int sign)
{
    int ret;

    len = apply_pres(v, len, &s, sign);
    ret = apply_width(v, len, s, 1);
    return(ret);
}