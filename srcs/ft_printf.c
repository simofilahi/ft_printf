#include "ft_printf.h"

int     ft_cmp(char c, const char *p)
{
    while (*p)
        if (c == *p++)
            return (1);
    return (0);
}

int     arg_len(const char *s)
{
    char conv[5] = "cspd";
    int  counter;
    
    counter = 0;
    if (*s != '%')
    {
        while (*s && *s != '%')
        {
            counter++;
            s++;
        }
        counter--;
    }
    else
    {
         while (*s && !ft_cmp(*s, &conv[0]))
         {
            counter++;
            s++;
         }
         counter++;
    }
    return (counter);
}

void    create_list(t_arg **head_ref, t_arg **tail_ref, char *s, int flag)
{
    t_arg *new_node;

    if (!(new_node = (t_arg *)malloc(sizeof(t_arg))))
        return ;
    new_node->arg = ft_strdup(s);
    new_node->flag = flag;
    new_node->next = NULL;
    if (!(*head_ref))
    {
        (*head_ref) = new_node;
        (*tail_ref) = new_node;
    }
    else
    {
        (*tail_ref)->next = new_node;
        (*tail_ref) = new_node;
    }
}

void    split(char **s, t_arg **head_ref, t_arg **tail_ref)
{
    char    *arg;
    int     len;
    int     i;
    int     flag;
    const char conv[5] = "cspd";

    len = arg_len((*s)) + 1;
    if (!(arg = (char *)malloc(sizeof(char) * len)))
        return ;
    i = 0;
    if (*(*s) != '%')
    {
        while (*(*s) && *(*s) != '%')
        {
            arg[i++] = *(*s);
            (*s)++;
        }
        (*s)--;
        flag = 0;
    }
    else
    {
         while (*(*s) && !ft_cmp(*(*s), &conv[0]))
         {
            arg[i++] = *(*s);
            (*s)++;
         }
         arg[i++] = *(*s);
         flag = 1;
    }
    arg[i] = '\0';
  //  ft_putstr(arg);
    create_list(head_ref, tail_ref, arg, flag);
    ft_strdel(&arg);
}

t_info    *parsing(char *s)
{
    t_info *ret;

    ret = ft_memalloc(sizeof(t_info));
    while (*s)
    {
        split(&s, &ret->head_ref, &ret->tail_ref);
        if (!*s)
            break ;
        s++;
    }
    return (ret);
}

int ft_printf(const char *format, ...)
{
    va_list args;
    va_start(args, format);
    t_info  *holder;

    char *tmp = ft_strdup(format);
    holder = parsing(tmp);
    int ret = 0;
    while (holder->head_ref)
    {
        if (!holder->head_ref->flag)
        {
            ft_putstr_fd(holder->head_ref->arg, 1);
            ret += ft_strlen(holder->head_ref->arg);
        }
        else
        {
            if (conversion(holder->head_ref->arg) == 'c')
                ret += conv_c(holder->head_ref->arg, args);
            else if (conversion(holder->head_ref->arg) == 's')
                ret += conv_s(holder->head_ref->arg, args);
            else if (conversion(holder->head_ref->arg) == 'p')
                ret += conv_p(holder->head_ref->arg, args);
            else if (conversion(holder->head_ref->arg) == 'd')
                ret += conv_d(holder->head_ref->arg, args);
        }
        holder->head_ref = holder->head_ref->next;
    }
    va_end(args);
    return (ret);
}

int main()
{
    int ret;


    ret = ft_printf("%0.0s\n", ft_strdup("Hello World"));
    printf("ret ==> %d\n", ret);
    ret = printf("%0.0s\n", ft_strdup("Hello World"));
     printf("ret ==> %d\n", ret);
    return 0;
}

//printf("hello%-4s\nhow old are you %.2f\n tell first char of your name %c", simo, 23.5, 'm');
