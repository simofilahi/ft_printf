#include "ft_printf.h"

int is_dot(char *s)
{
    while (*s)
        if (*s++ == '.')
            return (1);
    return (0);
}

void debug(t_var v)
{
    ft_putstr("v.pres ==> ");
    ft_putnbr(v.pres);
    ft_putchar('\n');
    ft_putstr("v.width ==> ");
    ft_putnbr(v.width);
    ft_putchar('\n');
    ft_putstr("v.f_flag ==> ");
    ft_putchar(v.f_flag);
    ft_putchar('\n');
    ft_putstr("v.s_flag ==> ");
    ft_putchar(v.s_flag);
    ft_putchar('\n');
    ft_putstr("v.v_length ==> ");
    ft_putchar('\n');
    ft_putendl(v.length);
}

void print(int count, char c)
{
    if (count <= 0)
        return ;
    while (count--)
        ft_putchar(c);
}

char    *apply_width(t_var v, char *str, int flag)
{
     char *src;
     int len;

    str = (flag == 1) ? ft_strsub(str, 0, 1) : str;
    src = NULL;
    len = (int)ft_strlen(str);
    if ((v.f_flag == '-' || v.s_flag == '-') && v.width > len)
    {
        src = ft_strnew(v.width - len);
        src = (char *)ft_memset(src, ' ', v.width - len);
        str = ft_strjoin(str, src);
    }
    else if (v.width > len)
    {
       src = ft_strnew(v.width - len);
       src = (char *)memset(src, ' ', v.width - len);
       str =  ft_strjoin(src, str);
    }
    (src != NULL) ? ft_strdel(&src) : 0;
    return(str);
}

char    *apply_pres(t_var v, char *str, int flag)
{
    char *src;
    int len;

    (void)flag;
    src = NULL;
    len = (int)ft_strlen(str);
    if (str[0] == '0' && str[1] == '\0' && v.pres == 0)
        str = ft_strdup("");
    else if (v.pres < len && v.type == 's')
        str = ft_strsub(str, 0, v.pres);
    else if (v.pres > len && v.type != 's')
    {
       src = ft_strnew(v.pres - len);
       src = (char *)ft_memset(src, '0', v.pres - len);
       str = ft_strjoin(src, str);
    }
    return (str);
}

char    *apply_width_pres(t_var v, char *str, char *conv, int n, int flag)
{
    int len;

    len = (int)ft_strlen(str);
    str = apply_pres(v, str, flag);
    str = apply_flags(v, str, conv, n);
    str = apply_width(v, str, flag);
    return(str);
}