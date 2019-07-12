#include "ft_printf.h"

t_var fill_structure(char *s, char c)
{
    t_var v;

    v.pres = get_precision(s);
    v.width = get_width(s);
    v.f_flag = get_fflag(s);
    v.s_flag = get_sflag(s);
    v.f_flag = (v.width == v.f_flag - '0') ? -1 : v.f_flag;
    v.s_flag = (v.width == v.s_flag - '0') ? -1 : v.s_flag;
    if ((v.f_flag == '-' && v.s_flag == '0') || (v.f_flag == '0' && v.s_flag == '-'))
    {
        v.f_flag = '-';
        v.s_flag = -1;
    }
    else if ((v.f_flag == ' ' && v.s_flag == '+') || (v.f_flag == '+' && v.s_flag == ' '))
    {
        v.f_flag = '+';
        v.s_flag = -1;
    }
  /*  else if ((v.f_flag == ' ' && v.s_flag == '0') || (v.f_flag == '0' && v.s_flag == ' '))
    {
        v.f_flag = '0';
        v.s_flag = -1;
    }*/
    v.length = get_length(s);
    v.type = c;
    return (v);
}

int  is_found(char c)
{
    char conv[10] = "cspdiouxX";
    int i;

    i = 0;
    while (i < 10)
    {
        if (conv[i] == c)
            return (1);
        i++;
    }
    return (0);
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

int get_fflag(char *s)
{
    while (*s)
    {
        if ((*s == '%') && \
            (*(s + 1) == '-' ||\
             *(s + 1) == '0' ||\
             *(s + 1) == '+' ||\
             *(s + 1) == '#' || \
             *(s + 1) == ' '))
                 return (*(s + 1));
        s++;
    }
    return (-1);
}

int get_sflag(char *s)
{
    while (*s)
    {
        if ((*s == '%') && \
            (*(s + 2) == '-' ||\
             *(s + 2) == '0' ||\
             *(s + 2) == '+' ||\
             *(s + 2) == '#' ||\
             *(s + 2) == ' '))
                 return (*(s + 2));
        s++;
    }
    return (-1);
}

char    *get_length(char *s)
{
    int j;
    int i;
    char *ret;

    j = 0;
    i = 0;
    while (s[i] && !ft_isalpha(s[i]))
        i++;
    j = i;
    while (s[i] && !is_found(s[i]))
        i++;
    ret = ft_strsub(s, j, i);
    return (ret);
}
