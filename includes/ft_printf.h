#ifndef FT_PRINTF_H
#define FT_PRINTF_H

#include "../libft/libft.h"
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
   int      pres;
   int      width;
   int      f_flag;
   int      s_flag;
   char     *length;
   char     type;
}              t_var;

int ft_printf(const char *format, ...);
t_var   fill_structure(char *s, char c);
char    conversion(char *s);
int     get_precision(char *s);
int     get_width(char *s);
int     get_fflag(char *s);
int     get_sflag(char *s);
char    *get_length(char *s);
int     conv_c(char *s, va_list args);
int     conv_s(char *s, va_list args);
int     conv_p(char *s, va_list args);
int     conv_d(char *s, va_list args);
int     conv_o(char *s, va_list args);
int     conv_u(char *s, va_list args);
int     conv_x(char *s, va_list args);
int     conv_X(char *s, va_list args);
int     apply_width_pres(t_var v, int len, char *s, int sign);
int     apply_pres(t_var v, int len, char **s, int sign);
int     apply_width(t_var v, int len, char *s, int flag);
void    apply_signs(t_var v, int sign);
int     calcu_for_signs(t_var v, int len, int sign);
void    c_s_p_common(t_var v, int len, char *s);
char    *hex(long int n, int flag);
char    *octal(long long int n);
void    print(int count, char c);
char	*ft_llitoa(long long int n);
int     is_dot(char *s);
// 
void    debug(t_var v);
#endif
