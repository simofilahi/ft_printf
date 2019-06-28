#ifndef FT_PRINTF_H
#define FT_PRINTF_H

#include "libft.h"
#include <stdarg.h>
//
#include <stdio.h>

typedef struct s_arg
{
    int         flag;
    char        *arg;
    struct s_arg *next;
    struct s_arg *prev;
}              t_arg;

typedef struct s_info
{
     t_arg *head_ref;
     t_arg *tail_ref;
}              t_info;

typedef struct s_var
{
   int pres;
   int width;
   int  flag;
}              t_var;

char    conversion(char *s);
int     conv_c(char *s, va_list args);
int     conv_s(char *s, va_list args);
int     conv_p(char *s, va_list args);
int     conv_d(char *s, va_list args);
#endif