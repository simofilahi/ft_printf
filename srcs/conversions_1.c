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
    int len;

    v = fill_structure(s, 'c');
    c = va_arg(args, int);
    len = 1;
    if (v.f_flag == '-')
    {
        ft_putchar(c);
        if (v.width > len)
             print(v.width - len, ' ');
    }
    else if (v.width > len)
    {
        if (v.width > len)
            print(v.width - len, ' ');
        ft_putchar(c);
    }
    else
        ft_putchar(c);
    return ((v.width > len) ? v.width : len);
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
    if (v.pres != -1 && v.width == -1)
        string = apply_pres(v, string, 0, 1);
    else if (v.pres == -1 && v.width != -1)
        string = apply_width(v, string, 0, 1);
    else if (v.pres != -1 && v.width != -1)
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
       string = apply_width(v, string, 0, 0);
    ft_putstr(string);
    len = (int)ft_strlen(string);
    ft_strdel(&string);
    return (len);
}