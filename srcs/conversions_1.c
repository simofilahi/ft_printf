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
    v.f_flag = get_fflag(s);
    v.s_flag = get_sflag(s);
    v.length = get_length(s);
    return (v);
}


int     conv_c(char *s, va_list args)
{
    t_var v;
    char c;

    v = fill_structure(s);
    c = va_arg(args, int);
    apply_width(v, 1, &c, 0, 0);
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
        apply_width(v, len, string, 0, 1);
    else if (v.pres && v.width)
        apply_width_pres(v, len, string, 0);
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
        apply_width(v, len, string, 0, 1);
    else
        ft_putstr(string);
    ft_strdel(&string);
    return ((v.width > len) ? v.width : len);
}