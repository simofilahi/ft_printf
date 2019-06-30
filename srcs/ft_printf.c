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
    char conv[7] = "cspdio";
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
    else if (*s == '%' && *(s + 1) != '%')
    {
         while (*s && !ft_cmp(*s, &conv[0]))
         {
            counter++;
            s++;
         }
         counter++;
    }
    else
    {
        while (*s && *s == '%')
         {
            counter++;
            s++;
         }
         s--;
         counter--;
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
    const char conv[7] = "cspdio";

    len = arg_len((*s)) + 1;
    if (!(arg = (char *)malloc(sizeof(char) * len)))
        return ;
    i = 0;
    flag = 0;
    if (*(*s) != '%')
    {
        while (*(*s) && *(*s) != '%')
        {

            arg[i++] = *(*s);
            (*s)++;
        }
        (*s)--;
    }
    else if (*(*s) == '%' && *(*s + 1) != '%')
    {
         while (*(*s) && !ft_cmp(*(*s), &conv[0]))
         {
            arg[i++] = *(*s);
            (*s)++;
         }
         arg[i++] = *(*s);
         flag = 1;
    }
    else
    {
        while (*(*s) && *(*s) == '%' &&\
         ((*(*s + 1) == '%') ||\
           ft_isspace((*(*s + 1)))))
        {
            arg[i++] = *(*s);
            (*s)++;
        }
        arg[i++] = *(*s);
        (*s)--;
        flag = -1;
    }
    arg[i] = '\0';
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
        else if (holder->head_ref->flag == -1)
        {
            ret += ft_strlen(holder->head_ref->arg) / 2;
            print((int)ft_strlen(holder->head_ref->arg) / 2, '%');
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
            else if (conversion(holder->head_ref->arg) == 'i')
                ret += conv_d(holder->head_ref->arg, args);
            else if (conversion(holder->head_ref->arg) == 'o')
                ret += conv_o(holder->head_ref->arg, args);
        }
        //printf("f_flag ==> %d\n arg ===> %s\n", holder->head_ref->f_flag, holder->head_ref->arg);
        holder->head_ref = holder->head_ref->next;
    }
    va_end(args);
    return (ret);
}

int main()
{
    int ret;
    //int var = 400;
   // int var1 = 600;

   /* ret = ft_printf("%%%%%%%%%+7.6d%%%%%%% %%%%%%%%%%%% %%%%%%+7.6i\n", var, var1);
    printf("ret ==> %d\n", ret);
    ret = ft_printf("%%%%%%%%%+7.6d%%%%%%% %%%%%%%%%%%% %%%%%%+7.6i\n", var, var1);
    printf("ret ==> %d\n", ret);*/

    ret = ft_printf("%#5.5o\n", 100);
    printf("ret ==> %d\n", ret);
    ret = printf("%#5.5o\n", 100);
    printf("ret ==> %d\n", ret);
    return 0;
}

//printf("hello%-4.2s\nhow old are you %.2f\n tell first char of your name %c", simo, 23.5, 'm');


/*
  --- 

*/