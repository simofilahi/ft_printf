#include "ft_printf.h"


char    *strappend(t_var v, char *str, int n)
{
    int len;
    char *src;
    char *tmp;

    len = (int)ft_strlen(str);
    src = NULL;
    tmp = str;
    if (v.f_flag == '+' && v.type == 'i' && n >= 0)
        str = ft_strjoin("+", str);
    else if (v.f_flag == ' ' && v.type != 's')
    {   
          
        if (v.width > len)
        {
            src = ft_strnew(v.width - len);
            ft_memset(src, ' ', v.width - len);
             str = ft_strjoin(src, str);
        }
        else
            str = ft_strjoin(" ", str);
    }
    else if (v.f_flag == '0' && v.type != 's')
    {
        if (v.width > len)
        {
            src = ft_strnew(v.width - len);
            ft_memset(src, '0', v.width - len);
            str = ft_strjoin(src, str);
        }
    }
    return (str);
}

int     zero_cases(t_var v, char *s, int n)
{
    if (n == 0 && (v.pres == -1 || v.pres == 0) && is_dot(s))
    {
        if (v.f_flag == '+')
            ft_putchar('+');
        else if (v.f_flag == ' ')
            ft_putchar(' ');
        return ((v.f_flag == '+' || v.f_flag == ' ') ? 1 : 0);
    }
    return (-1);
}
/*void    get_type(t_var v, va_list args, int *n)
{
    (void)args;
    (void)n;

    if (ft_strcmp(v.length, "h") == 0)
    {

    }
    else if (ft_strcmp(v.length, "hh") == 0)
    {

    }
    else if (ft_strcmp(v.length, "h") == 0)
    {

    }
  //  debug(v);
}*/

int     conv_d(char *s, va_list args)
{
    t_var v;
    long long int n;
    int len;
    int ret;
    char *str;

    v = fill_structure(s, 'i');
    n = va_arg(args, long long int);
    str = ft_llitoa((long long int)n);
    if ((len = zero_cases(v, s, n)) != -1)
        return (len);
    len = ft_strlen(str);
    if (v.width == -1 && v.pres != -1)
        apply_pres(v, len, &str, 0);
    else if (v.width != -1 && v.pres == -1)
        apply_width(v, len, str, 1);
    else if (v.width != -1 && v.pres != -1)
        apply_width_pres(v, len, str, 0);
    str = strappend(v, str, n);
   // ft_putstr(str);
    ret = (int)ft_strlen(str);
    return (ret);
}

int     conv_o(char *s, va_list args)
{
    t_var v;
    unsigned int  n;
    int len;
    char *str;

    v = fill_structure(s, 'u');
    n = va_arg(args, unsigned int);
    str = octal(n);
    len = ft_strlen(str);
    if (v.width != -1 && v.pres == -1)
        return (apply_width(v, len, str, 1));
    else if (v.width == -1 && v.pres != -1)
        return (apply_pres(v, len, &str, 0));
    else if (v.width != -1 && v.pres != -1)
        return (apply_width_pres(v, len, str, 0));
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
        return (apply_width(v, len, str, 1));
    else if (v.width == -1 && v.pres != -1)
        return (apply_pres(v, len, &str, 0));
    else if (v.width != -1 && v.pres != -1)
        return (apply_width_pres(v, len, str, 0));
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
        len = apply_width(v, len, str, 1);
    else if (v.width == -1 && v.pres != -1)
        len = apply_pres(v, len, &str, 0);
    else if (v.width != -1 && v.pres != -1)
        len = apply_width_pres(v, len, str, 0);
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
        return (apply_width(v, len, str, 1));
    else if (v.width == -1 && v.pres != -1)
        return (apply_pres(v, len, &str, 0));
    else if (v.width != -1 && v.pres != -1)
        return (apply_width_pres(v, len, str, 0));
    ft_strdel(&str);
    return (len);
}