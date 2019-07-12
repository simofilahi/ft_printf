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
   int      t_flag;
   int      fo_flag;
   char     *length;
   char     type;
}              t_var;

/*
** Conversion
*/
int     conv_c(char *s, va_list args);
int     conv_s(char *s, va_list args);
int     conv_p(char *s, va_list args);
int     conv_d(char *s, va_list args);
int     conv_o(char *s, va_list args);
int     conv_u(char *s, va_list args);
int     conv_x(char *s, va_list args);
int     conv_X(char *s, va_list args);
/*
** handlers
*/
char    *apply_width_pres(t_var v, char *str, char *conv, int long long n, int flag);
char    *apply_pres(t_var v, char *s, int long long n, int sign);
char    *apply_width(t_var v, char *s, int long long n, int flag);
char    *apply_flags(t_var v, char *s, char *conv, int long long n);
/*
** get properties
*/
int     get_precision(char *s);
int     get_width(char *s);
int     get_fflag(char *s);
int     get_sflag(char *s);
/*
**
*/
int     ft_printf(const char *format, ...);
t_var   fill_structure(char *s, char c);
char    conversion(char *s);
char    *get_length(char *s);
char    *hex(unsigned long long int n, int flag);
char    *octal(unsigned long long int n);
void    print(int count, char c);
char	*ft_llitoa(unsigned long long int n);
int     is_dot(char *s);
// 
void    debug(t_var v);
#endif
