#include "ft_printf.h"

int    conv_type(char *s, t_properties *v, void (*f)(char *, t_properties **, char ), char *conv_arr)
{
    int len;
    int len_2;

    len  = (int)ft_strlen(s) - 1;
    len_2 = (int)ft_strlen(conv_arr);
    // ft_putstr_fd("here str ==>",2);
    // ft_putstr_fd(s, 2);
 //   printf("s ==> %s\n", s);
    //ft_putendl_fd("HERE", 2);
    if (len_2 == 1)
    {
    //         printf("s[len] == %c\n", s[len]);
    // printf("conv_arr[0] ==> %c\n", conv_arr[0]);
        if (conv_arr[0] == s[len])
        {
              
            f(s, &v, s[len]);
            return (1);
        }
        return (0);
    }
    while (*conv_arr)
    {
        if (s[len] == *conv_arr)
        {
            f(s, &v, s[len]);
            return (1);
        }
        conv_arr++;
    }
    return (0);
}


int     conv_c(t_properties v, va_list args)
{
    char c;
    int len;

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

int     conv_s(t_properties v, va_list args)
{
    char *string;
    int  len;

    string = va_arg(args, char *);
    if (string == NULL)
        string = ft_strdup("(null)");
    len = (int)ft_strlen(string);
    if (v.pres != -1 && v.width == -1)
        string = apply_pres(v, string, 0, 1);
    else if (v.pres == -1 && v.width != -1)
        string = apply_width(v, string, 0, 1);
    else if (v.pres != -1 && v.width != -1)
        string = apply_width_pres(v, string, 0, 0);
    ft_putstr(string);
    len = (int)ft_strlen(string);
    return (len);
}

int     conv_p(t_properties v, va_list args)
{
    long long int   ret;
    char            *str;
    char            *tmp;
    int             len;

    ret = va_arg(args, long long int);
    str = ft_llitoa_base(ret, v);
    tmp = str;
    str = ft_strjoin("0x", str);
    ft_strdel(&tmp);
    if (v.width != -1)
       str = apply_width(v, str, 0, 0);
    ft_putstr(str);
    len = (int)ft_strlen(str);
    ft_strdel(&str);
    return (len);
}


int conv_b(t_properties v, va_list args)
{
     long long int   n;
     char            *str;
     int             len;

    n = va_arg(args, long int);
    str = ft_llitoa_base(n, v);
    ft_putstr(str);
    ft_strdel(&str);
    len = (int)ft_strlen(str);
    return (len);
}