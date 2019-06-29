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

void print(int count, char c)
{
    while (count--)
        ft_putchar(c);
}

void debug(t_var v, char *s)
{
    (void)s;
   // ft_putstr(s);
  //  ft_putchar('\n');
    printf("v.pres ==> %d\n", v.pres);
    printf("v.width ==> %d\n", v.width);
    printf("v.flag ==> %c\n", v.flag);
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

int    apply_width(t_var v, int len, int n, int sign)
{
    if (v.width > len)
    {
        if (v.flag == -1 || v.flag == '+')
        {
            len = (v.flag == '+' && n >= 0) ? len + 1 : len;
            print(v.width - len, ' ');
            (v.flag == '+' && n >= 0) ? ft_putchar('+') : 0;
            ft_putnbr(n);
        }
        else
        {
            ft_putnbr(n);
            print(v.width - len, ' ');
        }
    }
    else
        ft_putnbr(n);
    return((v.width > len) ? v.width : len);
}

int     check_length(char *s)
{
    (void)s;
    return (0);
}

int    apply_pres(t_var v, int len, int n, int sign)
{
    (v.flag == '+' && sign == 0) ? ft_putchar('+') : 0;
    (sign == 1) ? ft_putchar('-') : 0;
    (v.pres > len) ? print(v.pres - len, '0') : 0;
    ft_putnbr(n);
    v.pres = (v.flag == '+' || sign == 1) ? v.pres + 1 : v.pres;
    len = (v.flag == '+' || sign == 1) ? len + 1 : len;
    return ((v.pres > len) ? v.pres : len);
}

int     apply_width_pres(t_var v, int len, int n, int sign)
{
    int ret = 0;

   /* if (v.width > v.pres && v.pres > len)
    {
        ret = v.width;
       if (v.flag == -1 || v.flag == '+')
        {
            v.width = (v.flag == '+') ? v.width - v.pres - 1 : v.width - v.pres;
            v.width = (sign == 1) ? v.width - 1 : v.width;
            print(v.width, ' ');
            (sign == 1) ? ft_putchar('-') : 0;
            (v.flag == '+' && sign == 0) ? ft_putchar('+') : 0;
            print(v.pres - len, '0');
            ft_putnbr(n);
        }
        else if (v.flag == '-')
        {
            (sign == 1) ? ft_putchar('-') : 0;
            print(v.pres - len, '0');
            ft_putnbr(n);
            v.width = (sign == 1) ? v.width - 1 : v.width;
            v.width = v.width - v.pres;
            print(v.width, ' ');
        }

    }
    else if (v.width < v.pres && v.pres > len)
    {
        ret = v.pres;

        (v.flag == '+') ? ft_putchar('+') : 0;
        print(v.pres - len, '0');
        ft_putnbr(n);
    }
    else if ((v.width > v.pres || v.width < len ) && v.pres < len)
    {
        ret = len;
        ft_putnbr(n);
    }*/
    apply_pres(v, len, n, sign);
    ft_putchar('\n');
    v.pres += (v.pres > len) ? v.pres - len : v.pres;
    len = v.width - v.pres;
    ft_putnbr(len);
    ft_putchar('\n');
    apply_width(v, len, n, sign);
    return((ret > 0) ? ret : len);
}



int     conv_d(char *s, va_list args)
{
    t_var v;
    int  n;
    int len;
    int sign;

    v = fill_structure(s);
    n = va_arg(args, int);
    sign = 0;
    if (n < 0)
    {
            n *= -1;
            sign = 1;
    }
    len = ft_nbrlen(n);
    if (v.width && v.pres == -1)
        return (apply_width(v, len, n));
    else if (v.width == -1 && v.pres)
        return (apply_pres(v, len, n, sign));
    else if (v.width && v.pres)
        return (apply_width_pres(v, len, n, sign));
    return (0);
}