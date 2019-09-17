#include "ft_printf.h"


void init_structure(t_holder *var)
{
    var->n = 0;
    var->len = 0;
    var->str = NULL;
    var->nbr = 0;
}

int  find_base(char conv_type)
{
    if (conv_type == 'b')
        return (2);
    else if (conv_type == 'o')
        return (8);
    else if (conv_type == 'd' || conv_type == 'i' || conv_type == 'u')
        return (10);
    else if (conv_type == 'x' || conv_type == 'X' || conv_type == 'p')
         return (16);
    return (0);
}

void fill_structure(char *s, t_properties **v, char c)
{
     (*v)->pres = get_precision(s);
     (*v)->width = get_width(s);
     (*v)->f_flag = get_fflag(s);
     (*v)->s_flag = get_sflag(s);
     (*v)->t_flag = get_tflag(s);
     (*v)->length = get_length(s);
     (*v)->type = c;
     (*v)->base = find_base((*v)->type);
     (*v)->f_flag = ( (*v)->width ==  (*v)->f_flag - '0') ? -1 : (*v)->f_flag;
     (*v)->s_flag = ( (*v)->width ==  (*v)->s_flag - '0') ? -1 : (*v)->s_flag;
    if (( (*v)->f_flag == '-' &&  (*v)->s_flag == '0') ||\
       ( (*v)->f_flag == '0' &&  (*v)->s_flag == '-'))
    {
        ( (*v))->f_flag = '-';
         (*v)->s_flag = -1;
    }
    else if (((*v)->f_flag == ' ' &&  (*v)->s_flag == '+') ||\
            ((*v)->f_flag == '+' &&  (*v)->s_flag == ' '))
    {
         (*v)->f_flag = '+';
         (*v)->s_flag = -1;
    }
}

int  is_found(char c)
{
    char conv[10] = "cspdiouxXf";
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

int get_tflag(char *s)
{
    while (*s)
    {
        if ((*s == '%') && \
            (*(s + 3) == '-' ||\
             *(s + 3) == '0' ||\
             *(s + 3) == '+' ||\
             *(s + 3) == '#' ||\
             *(s + 3) == ' '))
                 return (*(s + 3));
        s++;
    }
    return (-1);
}

// int get_fourthflag(char *s)
// {
//     while (*s)
//     {
//         if ((*s == '%') && \
//             (*(s + 2) == '-' ||\
//              *(s + 2) == '0' ||\
//              *(s + 2) == '+' ||\
//              *(s + 2) == '#' ||\
//              *(s + 2) == ' '))
//                  return (*(s + 2));
//         s++;
//     }
//     return (-1);
// }

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
