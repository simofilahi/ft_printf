#include "ft_printf.h"

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

int get_flag(char *s)
{
    while (*s)
    {
        if ((*s == '%') && \
            (*(s + 1) == '-' ||\
             *(s + 1) == '0' ||\
             *(s + 1) == '+' ||\
             *(s + 1) == '#'))
                 return (*(s + 1));
        s++;
    }
    return (-1);
}

char    *get_length(char *s)
{
    size_t len;
    int i;
    char *ret;

    len = ft_strlen(s);
    i = len - 2;
    while (s[i]  && ft_isalpha(s[i]))
        i--;
    ret = ft_strsub(s, i + 1, len - 2);
    return (ret);
}