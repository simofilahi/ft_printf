#include "ft_printf.h"

char    *apply_flag_space(t_var v, char *str)
{
    char *src;
    int   len;

    src = NULL;
    len = (int)ft_strlen(str);
    if (v.width > len && (v.f_flag != '-' && v.s_flag != '-' && v.f_flag != '0' && v.s_flag != '0'))
    {
        src = ft_strnew(v.width - len);
        ft_memset(src, ' ', v.width - len);
        str = ft_strjoin(src, str);
    }
    else
        str = ft_strjoin(" ", str);
    return (str);
}

char    *apply_flag_zero(t_var v, char *str, int len, int long long n)
{
    char *src;

    src = NULL;
    if (v.width > len && v.pres == -1)
    {
        src = ft_strnew(v.width - len);
        ft_memset(src, '0', v.width - len);
        str = ft_strjoin(src, str);
    }
    if (v.f_flag == '+' && v.type == 'i' && n >= 0)
        str = ft_strjoin("+", str);
    return (str);
}

char    *apply_flags(t_var v, char *str, char *conv, int long long n)
{
    int len;
    int flag = 0;

     if ((n < 0 && (v.f_flag == '0' || v.s_flag == '0') && (v.width != -1) && (v.pres != -1)) ||\
        (n < 0 && (v.f_flag != '0' && v.s_flag != '0') && (v.width != -1) && (v.pres == -1)) ||\
        (n < 0 && ((v.f_flag != '0' && v.s_flag != '0') && (v.width != -1) && (v.pres != -1)))
    )
    {
        flag = 1;
        str = ft_strjoin("-", str);
    }
     if (n < 0)
    {
        v.f_flag = (v.f_flag == ' ') ? -1 : v.f_flag;
        v.s_flag = (v.s_flag == ' ') ? -1 : v.s_flag;
    }
    if (n < 0 && v.f_flag == '+' && v.s_flag == '0' && v.width != -1)
        len = (int)ft_strlen(str);
    else if ((n < 0 && (v.f_flag == '0') && (v.width != -1) && (v.pres != -1)) ||\
        (n < 0 && (v.f_flag == '0') && (v.width != -1) && (v.pres == -1)) ||\
        (n < 0 && (v.f_flag != '0') && (v.width != -1) && (v.pres == -1)) ||\
        (n < 0 && (v.f_flag != '0') && (v.width != -1) && (v.pres != -1)) ||\
        (n < 0 && (v.f_flag == ' '))
        )
        {
            len = (int)ft_strlen(str) + 1;
        }
    else
        len = (int)ft_strlen(str);
    (void)conv;
    // if (n < 0)
    // {
    //     v.f_flag = (v.f_flag == ' ') ? -1 : v.f_flag;
    //     v.s_flag = (v.s_flag == ' ') ? -1 : v.s_flag;
    // }
    if (v.f_flag == '+' || v.s_flag == '+')
        len += 1;
    if ((v.f_flag == '+' || v.s_flag == '+') && v.type == 'i' && n >= 0 && v.s_flag != '0')
    {
         
        str = ft_strjoin("+", str);
    }
    else if (((v.f_flag == ' ' && v.s_flag == '0') || (v.f_flag == '0' && v.s_flag == ' ')) && (v.type != 's'))
    {
        str = apply_flag_zero(v, str, len + 1, n);
        str = apply_flag_space(v, str);
    }
    else if ((v.f_flag == ' ' || v.s_flag == ' ') && v.type != 's')
        str = apply_flag_space(v, str);
    else if ((v.f_flag == '0' || v.s_flag == '0') && v.type != 's')
        str = apply_flag_zero(v, str, len, n);
    if (!flag && n < 0)
        str = ft_strjoin("-", str);
    return (str);
}

void casting(t_var v, long long int *n, va_list args)
{
    if (ft_strcmp(v.length, "hhd") == 0)
        *n = (signed short)va_arg(args, long long int);
    else if (ft_strcmp(v.length, "hd") == 0)
        *n = (short)va_arg(args, long long int);
    else if (ft_strcmp(v.length, "ld") == 0)
        *n = (long)va_arg(args, long long int);
    else if (ft_strcmp(v.length, "lld") == 0)
        *n = va_arg(args, long long int);
    else
        *n = (int)va_arg(args, long long int);
}

int     conv_d(char *s, va_list args)
{
    t_var                  v;
    int long long          n;
    int                    len;
    char                   *str;
    unsigned long long int nbr;

    v = fill_structure(s, 'i');
    //debug(v);
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
    {
        str = apply_flags(v, str, s, n);
    }
    ft_putstr(str);
    len = (int)ft_strlen(str);
    return (len);
}

/*int     conv_o(char *s, va_list args)
{
    t_var v;m
    unsigned int  n;
    int len;
    char *str;

    v = fill_structure(s, 'u');
    n = va_arg(args, unsigned int);
    str = octal(n);
    len = ft_strlen(str);
    if (v.width != -1 && v.pres == -1)
        apply_width(v, str, 1);
    else if (v.width == -1 && v.pres != -1)
        apply_pres(v, str, 0);
    else if (v.width != -1 && v.pres != -1)
        str = apply_width_pres(v, str, s, n, 0);
    else if (v.f_flag == '#')
    {
        ft_putchar('0');
        len += 1;
    }
    ft_putstr(str);
    ft_strdel(&str);
    return (len);
}

int     conv_u(char *s, va_list args)
{
    t_var v;
    unsigned int  n;
    int len;
    char *str;

    v = fill_structure(s, 'u');
    n = va_arg(args, unsigned int);
    str = ft_llitoa((long long int)n);
    len = ft_strlen(str);
    if (v.width != -1 && v.pres == -1)
        apply_width(v, str, 1);
    else if (v.width == -1 && v.pres != -1)
        apply_pres(v, str, 0);
    else if (v.width != -1 && v.pres != -1)
         str = apply_width_pres(v, str, s, n, 0);
    else
        ft_putstr(str);
    return (len);
}

int     conv_x(char *s, va_list args)
{
    t_var v;
    unsigned int  n;
    int len;
    char *str;

    v = fill_structure(s, 'u');
    n = va_arg(args, unsigned int);
    str = hex(n, 0);
    if (v.f_flag == '#' || v.s_flag == '#')
    {
        str = ft_strjoin("0X", str);
        if (v.f_flag == '#')
            v.f_flag = -1;
        else
            v.s_flag = -1;
    }
    len = ft_strlen(str);
    if (v.width != -1 && v.pres == -1)
        apply_width(v, str, 1);
    else if (v.width == -1 && v.pres != -1)
        apply_pres(v, str, 0);
    else if (v.width != -1 && v.pres != -1)
         str = apply_width_pres(v, str, s, n, 0);
    ft_strdel(&str);
    return (len);
}

int     conv_X(char *s, va_list args)
{
    t_var v;
    unsigned int  n;
    int len;
    char *str;

    v = fill_structure(s, 'u');
    n = va_arg(args, unsigned int);
    str = hex(n, 1);
     if (v.f_flag == '#' || v.s_flag == '#')
    {
        str = ft_strjoin("0X", str);
        if (v.f_flag == '#')
            v.f_flag = -1;
        else
            v.s_flag = -1;
    }
    len = ft_strlen(str);
    if (v.width != -1 && v.pres == -1)
        apply_width(v, str, 1);
    else if (v.width == -1 && v.pres != -1)
        apply_pres(v, str, 0);
    else if (v.width != -1 && v.pres != -1)
       str = apply_width_pres(v, str, s, n, 0);
    ft_strdel(&str);
    return (len);
}*/