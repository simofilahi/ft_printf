#include "ft_printf.h"

int ft_printf(const char *format, ...)
{
    va_list args;
    va_start(args, format);
    t_arg *head_ref;
    t_properties   v;

    
    char *tmp = ft_strdup(format);
    head_ref = parser(tmp);

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
                ret += conv_f(v, args);
            else if (conv_type(head_ref->arg, &v, &fill_structure, "b"))
                 ret += conv_b(v, args);
            if (conv_type(head_ref->arg, &v, &fill_structure, "%"))
                 ret += conv_percent(head_ref->arg ,v);
            else if (conv_type(head_ref->arg, &v, &fill_structure, "diouxX"))
            {
                
                ret += conv_diouxX(v, args);
            }
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