#include "ft_printf.h"


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
             *(s + 2) == '#'))
                 return (*(s + 2));
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