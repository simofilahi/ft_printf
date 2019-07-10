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


int     conv_c(char *s, va_list args)
{
    t_var v;
    char c;
    char *string;
    int  len;

    v = fill_structure(s, 'c');
    c = va_arg(args, int);
    string = apply_width(v, &c, 1);
    len = (int)ft_strlen(string);
    if (v.f_flag == '-' && c == 0)
    {
        ft_putchar(c);
        ft_putstr(string);
    }
    else if (c == 0)
    {
        ft_putstr(string);
        ft_putchar(c);
    }
    else
        ft_putstr(string);
    return ((c == 0) ? len + 1 : len);
}

int     conv_s(char *s, va_list args)
{
    t_var v;
    char *string;
    int  len;

    v = fill_structure(s, 's');
    string = va_arg(args, char *);
    if (string == NULL)
        string = ft_strdup("(null)");
    len = (int)ft_strlen(string);
    if (v.pres && v.width == -1)
        string = apply_pres(v, string, 0);
    else if (v.pres == -1 && v.width)
        string = apply_width(v, string, 0);
    else if (v.pres && v.width)
        string = apply_width_pres(v, string, string, 0, 0);
    ft_putstr(string);
    len = (int)ft_strlen(string);
    return (len);
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
    if (v.width != -1)
       string = apply_width(v, string, 0);
    ft_putstr(string);
    len = (int)ft_strlen(string);
    ft_strdel(&string);
    return (len);
}