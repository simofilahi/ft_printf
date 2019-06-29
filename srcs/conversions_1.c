#include "ft_printf.h"

char    conversion(char *s)
{
    int len;

    len  = (int)ft_strlen(s);
    while (--len >= 0)
    {
        if (ft_isalpha(s[len]))
            return (s[len]);
    }
    return ('0');
}

t_var fill_structure(char *s)
{
    t_var v;

    v.pres = get_precision(s);
    v.width = get_width(s);
    v.flag = get_flag(s);
    v.length = get_length(s);
    return (v);
}

void    c_s_p_common(t_var v, int len, char *s)
{
    if (v.width > len)
    {
        if (v.flag == '-')
        {
            (len == 1) ? ft_putchar(*s) : ft_putstr(s);
            print(v.width - len, ' ');
        }
        else
        {
            print(v.width - len, ' ');
            (len == 1) ? ft_putchar(*s) : ft_putstr(s);
        } 
    }
    else
        (len == 1) ? ft_putchar(*s) : ft_putstr(s);
}

int     conv_c(char *s, va_list args)
{
    t_var v;
    char c;

    v = fill_structure(s);
    c = va_arg(args, int);
    c_s_p_common(v, 1, &c);
    return ((v.width > 1) ? v.width : 1);
}

int     conv_s(char *s, va_list args)
{
    t_var v;
    char *string;
    int  len;

    v = fill_structure(s);
    string = va_arg(args, char *);
    len = (int)ft_strlen(string);
    string = (len > v.pres) ? ft_strsub(string, 0, v.pres) : string;
    len = (len > v.pres) ? (int)ft_strlen(string) : len;
    if (v.pres && v.width == -1)
        ft_putstr(string);
    else if (v.pres == -1 && v.width)
        c_s_p_common(v, len, string);
    else if (v.pres && v.width)
        c_s_p_common(v, len, string);
    return ((v.width > len) ? v.width : len);
}

int     conv_p(char *s, va_list args)
{
     t_var v;
     long  int   ret;
     char *string;
     char *tmp;
     int   len;

    v = fill_structure(s);
    ret = va_arg(args, long int );
    string = hex(ret);
    tmp = string;
    string = ft_strjoin("0x7", string);
    ft_strdel(&tmp);
    len = (int)ft_strlen(string);
    if (v.width)
        c_s_p_common(v, len, string);
    else
        ft_putstr(string);
    ft_strdel(&string);
    return ((v.width > len) ? v.width : len);
}