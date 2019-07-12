#include "ft_printf.h"

// int casting_helper()
// {

// }

void casting(t_var v, long long int *n, va_list args)
{
    if (ft_strcmp(v.length, "d") == 0 || ft_strcmp(v.length, "i") == 0)
        *n = (int)va_arg(args, long long int);
    else if (ft_strcmp(v.length, "o") == 0 || ft_strcmp(v.length, "u") == 0 || ft_strcmp(v.length, "x") == 0 || ft_strcmp(v.length, "X") == 0)
        *n = (unsigned int)va_arg(args, unsigned long long int);
    if (ft_strcmp(v.length, "hd") == 0 || ft_strcmp(v.length, "hi") == 0)
        *n = (short)va_arg(args, long long int);
    else if (ft_strcmp(v.length, "ho") == 0 || ft_strcmp(v.length, "hu") == 0 || ft_strcmp(v.length, "hx") == 0 || ft_strcmp(v.length, "hX") == 0)
        *n = (unsigned short)va_arg(args, unsigned long long int);
    else if (ft_strcmp(v.length, "hhd") == 0 || ft_strcmp(v.length, "hhi") == 0)
        *n = (signed short)va_arg(args, long long int);
    else if (ft_strcmp(v.length, "hho") == 0 || ft_strcmp(v.length, "hhu") == 0 || ft_strcmp(v.length, "hhx") == 0 || ft_strcmp(v.length, "hhX") == 0)
        *n = (unsigned char)va_arg(args, unsigned long long int);
    else if (ft_strcmp(v.length, "ld") == 0 || ft_strcmp(v.length, "li") == 0)
        *n = (long)va_arg(args, long long int);
    else if (ft_strcmp(v.length, "lo") == 0 || ft_strcmp(v.length, "lu") == 0 || ft_strcmp(v.length, "lx") == 0 || ft_strcmp(v.length, "lX") == 0)
        *n = (unsigned long)va_arg(args, unsigned long long int);
    else if (ft_strcmp(v.length, "lld") == 0 || ft_strcmp(v.length, "lli") == 0)
        *n = va_arg(args, long long int);
    else if (ft_strcmp(v.length, "llo") == 0 || ft_strcmp(v.length, "llu") == 0 || ft_strcmp(v.length, "llx") == 0 || ft_strcmp(v.length, "llX") == 0)
        *n = va_arg(args, unsigned long long int);
}

int     conv_o(char *s, va_list args)
{
    t_var v;
    int  long long n;
    int len;
    char *str;

    v = fill_structure(s, 'o');
    casting(v, &n, args);
    n = (unsigned long long int)n;
    str = octal(n);
    n = (n < 0) ? n * -1 : n;
    len = 0;
    if (v.width == -1 && v.pres != -1)
    {
        str = apply_pres(v, str, n,0);
          //  printf("before str ==>%s\n", str);
        str = apply_flags(v, str, s, n);
        // printf("after str ==>%s\n", str);
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
    len = ft_strlen(str);
    ft_putstr(str);
    ft_strdel(&str); 
    return (len);
}

int     conv_d(char *s, va_list args)
{
    t_var                  v;
    int long long          n;
    int                    len;
    char                   *str;
    unsigned long long int nbr;

    v = fill_structure(s, 'i');
    casting(v, &n, args);
    nbr = (n < 0) ? n * -1 : n;
    str = ft_llitoa(nbr);
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

int     conv_i(char *s, va_list args)
{
    t_var                  v;
    int long long          n;
    int                    len;
    char                   *str;
    unsigned long long int nbr;

    v = fill_structure(s, 'i');
    casting(v, &n, args);
    nbr = (n < 0) ? n * -1 : n;
    str = ft_llitoa(nbr);
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


int     conv_u(char *s, va_list args)
{
    t_var                  v;
    int long long          n;
    int                    len;
    char                   *str;

    v = fill_structure(s, 'u');
    casting(v, &n, args);
    str = ft_llitoa(n);
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

int     conv_x(char *s, va_list args)
{

    t_var                  v;
    int long long          n;
    int                    len;
    char                   *str;

    v = fill_structure(s, 'x');
    casting(v, &n, args);
    str = hex(n, 0);
    n = (n < 0) ? n * -1 : n;
    if (v.width == -1 && v.pres != -1)
    {
        str = apply_pres(v, str, n, 0);
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

int     conv_X(char *s, va_list args)
{
     t_var                  v;
    int long long          n;
    int                    len;
    char                   *str;

    v = fill_structure(s, 'X');
    casting(v, &n, args);
    str = hex(n, 1);
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