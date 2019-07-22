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

typedef struct s_properties
{
   int      pres;
   int      width;
   int      f_flag;
   int      s_flag;
   char     *length;
   char     type;
}              t_properties;

typedef struct           s_holder
{
  int long long          n;
  int                    len;
  char                   *str;
  unsigned long long int nbr;
}                        t_holder;

typedef struct           s_floatdata
{
  int sign : 1;
  int expo : 8;
  int mantisa : 23;
}                        t_floatdata;

typedef union u_data{
  float nbr;
  t_floatdata data;
}     n_data;

// typedef struct s_norm
// {
//    int      pres;
//    int      width;
//    int      f_flag;
//    int      s_flag;
//    char     *length;
//    char     type;
// }              t_norm;

/*
** Conversion
*/
int     conv_c(t_properties v, va_list args);
int     conv_s(t_properties v, va_list args);
int     conv_p(t_properties v, va_list args);
int     conv_d(t_properties v, va_list args);
int     conv_i(t_properties v, va_list args);
int     conv_o(t_properties v, va_list args);
int     conv_u(t_properties v, va_list args);
int     conv_x(t_properties v, va_list args);
int     conv_X(t_properties v, va_list args);
int     conv_f(t_properties v, va_list args);
int     conv_b(t_properties v, va_list args);
/*
** handlers
*/
char    *apply_width_pres(t_properties v, char *str, int long long n, int flag);
char    *apply_pres(t_properties v, char *s, int long long n, int sign);
char    *apply_width(t_properties v, char *s, int long long n, int flag);
char    *apply_flags(t_properties v, char *s, int long long n);
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
void    fill_structure(char *s, t_properties **v, char c);
int     conversion(char *s, t_properties *v, void (*f)(char *, t_properties **, char ), char c);
char    *get_length(char *s);
char    *hex(unsigned long long int n, int flag);
char    *octal(unsigned long long int n);
void    print(int count, char c);
char    *ft_llitoa_base(unsigned long long int n, int base, int flag);
int     is_dot(char *s);
void    init_structure(t_holder *var);
// 
void    debug(t_properties v);
#endif
