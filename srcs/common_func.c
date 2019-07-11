#include "ft_printf.h"

int is_dot(char *s)
{
    while (*s)
        if (*s++ == '.')
            return (1);
    return (0);
}

void print(int count, char c)
{
    if (count <= 0)
        return ;
    while (count--)
        ft_putchar(c);
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

char    *apply_width(t_var v, char *str, int long long n, int flag)
{
     char   *src;
     int    len;

    str = (flag == 1) ? ft_strsub(str, 0, 1) : str;
    len = (n < 0 && (v.f_flag == '0' || v.s_flag == '0') && (v.pres == -1)) ? (int)ft_strlen(str) + 1 : (int)ft_strlen(str);
    src = NULL;
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

char    *apply_pres(t_var v, char *str, int long long n, int flag)
{
    char    *src;
    int     len;

    (void)flag;
    (void)n;
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

char    *apply_width_pres(t_var v, char *str, char *conv, int long long n, int flag)
{
    int len;

    //printf("str one ==>%s\n", str);
    len = (int)ft_strlen(str);
    str = apply_pres(v, str, n, flag);
    //printf("str two ==>%s\n", str);
    str = apply_flags(v, str, conv, n);
   // printf("str three ==>%s\n", str);
    str = apply_width(v, str, n, flag);
    //printf("str four ==> %s\n", str);
    return(str);
}