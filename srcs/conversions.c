#include "ft_printf.h"

char    conversion(char *s)
{
    while (*s)
    {
        if (ft_isalpha(*s))
            return (*s);
        s++;
    }
    return ('0');
}

int get_precision(char *s)
{
    size_t len;
    int ret;

    len = ft_strlen(s);
    ret = -1;
    while (s[--len])
    {
        if (s[len] == '.')
        {
            ret = ft_atoi(s+(++len));
            break;
        }
    }
    return (ret);
}

int get_width(char *s)
{
   int i;
   int ret;

   i = 0;
   ret = -1;
   while (s[i])
   {
        if (s[i] >= '0' && s[i] <= '9')
        {
            ret = ft_atoi(s+i);
            break;
        }
        else if (s[i] == '.')
            break;
        i++;
    }
    return (ret); 
}

int get_flag(char *s)
{
    while (*s)
    {
        if ((*s == '%') && \
            (*(s + 1) == '-' ||\
             *(s + 1) == '0' ||\
             *(s + 1) == '+' ||\
             *(s + 1) == '#'))
                 return (*(s + 1));
        s++;
    }
    return (-1);
}

t_var fill_structure(char *s)
{
    t_var v;

    v.pres = get_precision(s);
    v.width = get_width(s);
    v.flag = get_flag(s);
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

void    conv_s_2(t_var v, int *len, char **string)
{
    char *tmp;

    if (*len > v.pres)
    {
        tmp = *string;
        *string = ft_strsub(*string, 0, v.pres);
        *len = (int)ft_strlen(*string);
    }
}

int     conv_s(char *s, va_list args)
{
    t_var v;
    char *string;
    int  len;

    v = fill_structure(s);
    string = va_arg(args, char *);
    len = (int)ft_strlen(string);
    if (v.pres != -1 && v.width == -1)
    {
        conv_s_2(v, &len, &string);
        ft_putstr(string);
    }
    else if (v.pres == -1 && v.width != -1)
        c_s_p_common(v, len, string);
    else if (v.pres != -1 && v.width != -1)
    {
        conv_s_2(v, &len, &string);
        c_s_p_common(v, len, string);
    }
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
    if (v.width != -1)
        c_s_p_common(v, len, string);
    else
        ft_putstr(string);
    ft_strdel(&string);
    return ((v.width > len) ? v.width : len);
}

int     conv_d_2(t_var v, int len, int n)
{
    int ret = 0;

    if (v.width > v.pres && v.pres > len)
    {
        ret = v.width;
        if (v.flag == -1 || v.flag == '+')
        {
            v.width = (v.flag == '+') ? v.width - v.pres - 1 : v.width - v.pres;
            print(v.width, ' ');
            (v.flag == '+') ? ft_putchar('+') : 0;
            print(v.pres - len, '0');
            ft_putnbr(n);
        }
        else if (v.flag == '-')
        {
            print(v.pres - len, '0');
            ft_putnbr(n);
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
    }
    return((ret > 0) ? ret : len);
}

void    conv_d_1(t_var v, int len, int n)
{
    if (v.width > len)
    {
        if (v.flag == -1 || v.flag == '+')
        {
            len = (v.flag == '+' && n>= 0) ? len + 1 : len;
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
}
int     conv_d(char *s, va_list args)
{
    t_var v;
    int  n;
    int len;

    v = fill_structure(s);
    n = va_arg(args, int);
    len = ft_nbrlen(n);
    if (v.width && v.pres == -1)
        conv_d_1(v, len, n);
    else if (v.width == -1 && v.pres)
    {
        if (v.pres > len)
        {
            (v.flag == '+') ? ft_putchar('+') : 0;
            print(v.pres - len, '0');
        }
        ft_putnbr(n);
        return (v.pres);
    }
    else if (v.width && v.pres)
        return (conv_d_2(v, len, n));
    return ((v.width > len) ? v.width : len);
}