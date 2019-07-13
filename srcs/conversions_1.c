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

    v = fill_structure(s, 'p');
    ret = va_arg(args, long int );
    string = ft_llitoa_base(ret, 16, 0);
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

char    *float_to_str(t_var v, double n)
{
    int long long f;
int long long h;
    f = (unsigned long long int)n;
    printf("f ==> %lld\n", f);
    //*str = ft_llitoa_base(())
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
            n *= 10;
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

int     conv_f(char *s, va_list args)
{
     t_var                  v;
    double         n;
    int                    len;
    char                   *str;

    v = fill_structure(s, 'f');
    //casting(v, &n, args);
    n = va_arg(args, double);
    str = float_to_str(v, n);
    //str = hex(n, 1);
    n = (n < 0) ? n * -1 : n;
    if (v.width == -1 && v.pres != -1)
    {
        str = apply_pres(v, str, n,0);
        str = apply_flags(v, str, s, n);
    }
    else if (v.width != -1 && v.pres == -1)
    {
        str = apply_flags(v, str, s, n);
        str = apply_width(v, str, n, 0);
    }
    else if (v.width != -1 && v.pres != -1)
        str = apply_width_pres(v, str, s, n, 0);
    else
        str = apply_flags(v, str, s, n);
    ft_putstr(str);
    len = (int)ft_strlen(str);
    return (len);
}

int conv_b(char *s, va_list args)
{
     t_var           v;
     long long int   ret;
     char            *string;
     char            *tmp;
     int             len;

    v = fill_structure(s, 'b');
    ret = va_arg(args, long int);
    string = ft_llitoa_base(ret, 2, 0);
    ft_putstr(string);
    len = (int)ft_strlen(string);
    return (len);
}