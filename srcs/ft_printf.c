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
    char conv[10] = "cspdiouxX";
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

/*
** - create linked list for hold splited arguments;
*/

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
    const char conv[10] = "cspdiouxX";

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

t_arg    *parsing(char *s)
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
    return (ret->head_ref);
}

int ft_printf(const char *format, ...)
{
    va_list args;
    va_start(args, format);
    t_arg *head_ref;
    t_properties   v;

    
    char *tmp = ft_strdup(format);
    head_ref = parsing(tmp);

    int ret = 0;
    int i;
    i = 0;
    (void)v;
    fd = open("/dev/ttys000", O_WRONLY);
    while (head_ref)
    {     
        if (!head_ref->flag)
        {
            ft_putstr_fd(head_ref->arg, 1);
            ret += ft_strlen(head_ref->arg);
        }
        else if (head_ref->flag)
        {
            if (conv_type(head_ref->arg, &v, &fill_structure, "c"))
                ret += conv_c(v, args);
            else if (conv_type(head_ref->arg, &v, &fill_structure, "s"))
                ret += conv_s(v, args);
            else if (conv_type(head_ref->arg, &v, &fill_structure, "p"))
                ret += conv_p(v, args);
            else if (conv_type(head_ref->arg, &v, &fill_structure, "f"))
            {
                
                ret += conv_f(v, args);
            }
            else if (conv_type(head_ref->arg, &v, &fill_structure, "b"))
                 ret += conv_b(v, args);
            if (conv_type(head_ref->arg, &v, &fill_structure, "%"))
                 ret += conv_percent(head_ref->arg ,v);
            else if (conv_type(head_ref->arg, &v, &fill_structure, "diouxX"))
                ret += conv_diouxX(v, args);
        }
        // ft_putstr("here arg ==>");
        // ft_putendl(head_ref->arg);
        // ft_putstr("flag ==>");
        // ft_putnbr(head_ref->flag);
        // ft_putendl("");
         head_ref = head_ref->next;
    }
    va_end(args);
    return (ret);
}



//printf("hello%-4.2s\nhow old are you %.2f\n tell first char of your name %c", simo, 23.5, 'm');


/*
  --- 
*/