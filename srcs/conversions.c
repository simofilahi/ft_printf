#include "ft_printf.h"

int     conv_d(char *s, va_list args)
{
    t_var v;
    int  n;
    int len;
    int sign;
    char *str;

    v = fill_structure(s);
    n = va_arg(args, int);
    sign = (n < 0) ? 1 : 0;
    n *= (sign == 1) ? -1 : 1;
    str = ft_llitoa((long long int)n);
    len = ft_strlen(str);
    if (v.width != -1 && v.pres == -1)
        return (apply_width(v, len, str, sign, 1));
    else if (v.width == -1 && v.pres != -1)
        return (apply_pres(v, len, str, sign));
    else if (v.width != -1 && v.pres != -1)
        return (apply_width_pres(v, len, str, sign));
    else
        ft_putstr(str);
    return (len);
}

int     conv_o(char *s, va_list args)
{
    t_var v;
    unsigned int  n;
    int len;
    char *str;

    v = fill_structure(s);
    n = va_arg(args, unsigned int);
    str = octal(n);
    len = ft_strlen(str);
    if (v.width != -1 && v.pres == -1)
        return (apply_width(v, len, str, 0, 1));
    else if (v.width == -1 && v.pres != -1)
        return (apply_pres(v, len, str, 0));
    else if (v.width != -1 && v.pres != -1)
        return (apply_width_pres(v, len, str, 0));
    else if (v.f_flag == '#')
    {
        ft_putchar('0');
        len += 1;
    }
    ft_putstr(str);
    ft_strdel(&str);
    return (len);
}

int     conv_u(char *s, va_list args)
{
    t_var v;
    unsigned int  n;
    int len;
    char *str;

    v = fill_structure(s);
    n = va_arg(args, unsigned int);
    str = ft_llitoa((long long int)n);
    len = ft_strlen(str);
    if (v.width != -1 && v.pres == -1)
        return (apply_width(v, len, str, 0, 1));
    else if (v.width == -1 && v.pres != -1)
        return (apply_pres(v, len, str, 0));
    else if (v.width != -1 && v.pres != -1)
        return (apply_width_pres(v, len, str, 0));
    else
        ft_putstr(str);
    return (len);
}

int     conv_x(char *s, va_list args)
{
    t_var v;
    unsigned int  n;
    int len;
    char *str;

    v = fill_structure(s);
    n = va_arg(args, unsigned int);
    str = hex(n, 0);
    if (v.f_flag == '#' || v.s_flag == '#')
    {
        str = ft_strjoin("0X", str);
        if (v.f_flag == '#')
            v.f_flag = -1;
        else
            v.s_flag = -1;
    }
    len = ft_strlen(str);
    if (v.width != -1 && v.pres == -1)
        len = apply_width(v, len, str, 0, 1));
    else if (v.width == -1 && v.pres != -1)
        len = apply_pres(v, len, str, 0));
    else if (v.width != -1 && v.pres != -1)
        len = apply_width_pres(v, len, str, 0));
    ft_strdel(&str);
    return (len);
}

int     conv_X(char *s, va_list args)
{
    t_var v;
    unsigned int  n;
    int len;
    char *str;

    v = fill_structure(s);
    n = va_arg(args, unsigned int);
    str = hex(n, 1);
     if (v.f_flag == '#' || v.s_flag == '#')
    {
        str = ft_strjoin("0X", str);
        if (v.f_flag == '#')
            v.f_flag = -1;
        else
            v.s_flag = -1;
    }
    len = ft_strlen(str);
    if (v.width != -1 && v.pres == -1)
        return (apply_width(v, len, str, 0, 1));
    else if (v.width == -1 && v.pres != -1)
        return (apply_pres(v, len, str, 0));
    else if (v.width != -1 && v.pres != -1)
        return (apply_width_pres(v, len, str, 0));
    ft_strdel(&str);
    return (len);
}