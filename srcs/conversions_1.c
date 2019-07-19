#include "ft_printf.h"

int    conversion(char *s, t_properties *v, void (*f)(char *, t_properties **, char ), char c)
{
    int len;

    len  = (int)ft_strlen(s);
    while (--len >= 0)
    {
        if (s[len] == c)
        {
            f(s, &v, c);
            return (1);
        }
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
    str = ft_llitoa_base(ret, 16, 0);
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

char    *float_to_str(t_properties v, double n)
{
    int long long f;
    int long long h;
    f = (unsigned long long int)n;
    printf("f ==> %lld\n", f);
  //  str = ft_llitoa_base(())
    printf("n ===> before %f\n", n);
    int i;

     i = 0;
    while (i < v.pres)
    {
        // if (i == 5)
        //     n *= 11;
        // else
        // {
              if (i == 0)
                f = ft_nbrlen(n);
            n *= -10;
            // if (i == 5)
            //     n += 1;
        // }
        i++;
    }
    printf("f ===>  %lld\n", f);
     printf("n ===> after %f\n", n);


    char *str;
    int j;

    n /= 10;
    printf("n ===> after modulo %f\n", n);
    h = n;
    int flag = 0;
   printf("h ===> after %lld\n", h);
    str = (char *)malloc(sizeof(char) * (ft_nbrlen(n) + 2));
    j = 0;
    while (1)
    {
        if (ft_nbrlen(h) == f && !flag)
        {
            str[j] = '.';
            flag = 1;
        }
        else
        {
            str[j] = h % 10 + '0';
            h /= 10;
        }
        j++;
        if (h <= 0)
            break;
    }
    str[j] = '\0';
    ft_strrev(str);
    return (str);
}

int     conv_f(t_properties v, va_list args)
{
    double                   n;
    int                    len;
    char                   *str;

    n = va_arg(args, double);
    str = float_to_str(v, n);
    n = (n < 0) ? n * -1 : n;
    if (v.width == -1 && v.pres != -1)
    {
        str = apply_pres(v, str, n,0);
        str = apply_flags(v, str, n);
    }
    else if (v.width != -1 && v.pres == -1)
    {
        str = apply_flags(v, str, n);
        str = apply_width(v, str, n, 0);
    }
    else if (v.width != -1 && v.pres != -1)
        str = apply_width_pres(v, str, n, 0);
    else
        str = apply_flags(v, str, n);
    ft_putstr(str);
    len = (int)ft_strlen(str);
    return (len);
}

int conv_b(t_properties v, va_list args)
{
     long long int   n;
     char            *str;
     int             len;

    (void)v;
    n = va_arg(args, long int);
    str = ft_llitoa_base(n, 2, 0);
    ft_putstr(str);
    ft_strdel(&str);
    len = (int)ft_strlen(str);
    return (len);
}