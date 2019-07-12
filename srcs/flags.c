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
    //
    if (v.f_flag == '+' && v.type == 'i' && n >= 0)
        str = ft_strjoin("+", str);
    return (str);
}

char    *apply_flag_hash(t_var v, char *str, int len, int long long n)
{
    char *src;
    char *tmp;
    src = NULL;
    
    tmp = ft_strdup(str);
    if (v.f_flag == '0' || v.s_flag == '0')
    {
        if ((n > 0) && (v.f_flag == '#' || v.s_flag == '#') && (v.type == 'x' || v.type == 'X'))
             len += 2;
       str = apply_flag_zero(v, str, len, n);
    }
    else if (v.f_flag == ' ' || v.s_flag == ' ')
        str = apply_flag_space(v, str);
    if (v.type == 'o' && \
       ((n > 0 && !(v.pres == len)) || (n == 0 && v.pres == 0)) &&\
       (v.f_flag == '#' || v.s_flag == '#') &&\
        ft_strcmp(str, tmp) == 0)
    {
        str = ft_strjoin("0", str);
    }
    else if ((v.type == 'x' || v.type == 'X') && \
        (n > 0) &&\
       (v.f_flag == '#' || v.s_flag == '#'))
    {
        if (v.type == 'x')
            str = ft_strjoin("0x", str);
        else if (v.type == 'X')
            str = ft_strjoin("0X", str);
    }
    return (str);
}

char    *apply_flags(t_var v, char *str, char *conv, int long long n)
{
    int len;
    int flag = 0;

    (void)conv;
    if (v.type == 'd')
    {
        if ((n < 0 && (v.f_flag == '0' || v.s_flag == '0') && (v.width != -1) && (v.pres != -1)) ||\
            (n < 0 && (v.f_flag != '0' && v.s_flag != '0') && (v.width != -1) && (v.pres == -1)) ||\
            (n < 0 && ((v.f_flag != '0' && v.s_flag != '0') && (v.width != -1) && (v.pres != -1)))
        )
        {
            flag = 1;
            str = ft_strjoin("-", str);
        } 
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
    if (v.f_flag == '+' || v.s_flag == '+')
        len += 1;
    if ((v.f_flag == '+' || v.s_flag == '+') && v.type == 'i' && n >= 0 && v.s_flag != '0')
        str = ft_strjoin("+", str);
    else if (((v.f_flag == ' ' && v.s_flag == '0') || (v.f_flag == '0' && v.s_flag == ' ')) && (v.type != 's'))
    {
        str = apply_flag_zero(v, str, len + 1, n);
        str = apply_flag_space(v, str);
    }
    else if ((v.f_flag == ' ' || v.s_flag == ' ') && v.type != 's')
        str = apply_flag_space(v, str);
    else if ((v.f_flag == '#' || v.s_flag == '#') && (v.type == 'o' || v.type == 'x' || v.type == 'X'))
        str = apply_flag_hash(v, str, len, n);
    else if ((v.f_flag == '0' || v.s_flag == '0') && v.type != 's')
        str = apply_flag_zero(v, str, len, n);
    if (!flag && n < 0)
        str = ft_strjoin("-", str);
    return (str);
}