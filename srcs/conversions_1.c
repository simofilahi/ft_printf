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

t_var fill_structure(char *s, char c)
{
    t_var v;

    v.pres = get_precision(s);
    v.width = get_width(s);
    v.f_flag = get_fflag(s);
    v.s_flag = get_sflag(s);
    v.length = get_length(s);
    v.type = c;
    return (v);
}


int     conv_c(char *s, va_list args)
{
    t_var v;
    char c;

    v = fill_structure(s, 'c');
    c = va_arg(args, int);
    apply_width(v, 1, &c, 0);
    return ((v.width > 1) ? v.width : 1);
}

int     conv_s(char *s, va_list args)
{
    t_var v;
    char *string;
    int  ret;
    int  len;

    v = fill_structure(s, 's');
    string = va_arg(args, char *);
    if (string == NULL)
        string = ft_strdup("(null)");
    len = (int)ft_strlen(string);
    ret = len;
    if (v.pres && v.width == -1)
    {
       ret = apply_pres(v, len, &string, 0);
       ft_putstr(string);
    }
    else if (v.pres == -1 && v.width)
        ret = apply_width(v, len, string, 1);
    else if (v.pres && v.width)
        ret = apply_width_pres(v, len, string, 0);
    else
        ft_putstr(string);
    return (ret);
}

int     conv_p(char *s, va_list args)
{
     t_var v;
     long  int   ret;
     char *string;
     char *tmp;
     int   len;

    v = fill_structure(s, 'i');
    ret = va_arg(args, long int );
    string = hex(ret, 0);
    tmp = string;
    string = ft_strjoin("0x", string);
    ft_strdel(&tmp);
    len = (int)ft_strlen(string);
    if (v.width)
        apply_width(v, len, string, 1);
    else
        ft_putstr(string);
    ft_strdel(&string);
    return ((v.width > len) ? v.width : len);
}