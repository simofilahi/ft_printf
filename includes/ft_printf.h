#ifndef FT_PRINTF_H
#define FT_PRINTF_H

#include "../libft/libft.h"
#include <stdarg.h>
#include <fcntl.h>
//
#include <stdio.h>

int fd;
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
   char     type;
   char     *length;
   int      base;
   int      pres;
   int      width;
   int      f_flag;
   int      s_flag;
   int      t_flag;
}              t_properties;

typedef struct           s_holder
{
  long long  int         n;
  int                    len;
  char                   *str;
  long long int          nbr;
}                        t_holder;

// typedef struct           s_double
// {
//   unsigned long mantisa : 53;
//   unsigned long expo : 11;
//   unsigned long sign : 1;
// }                        t_double;

typedef struct           s_longdouble
{
  unsigned  long int mantisa : 63;
  unsigned long int d : 1;
  unsigned long int expo : 15;
  unsigned  long int sign : 1;
}                       t_longdouble;

typedef union u_data{
  long double nbr;
  t_longdouble doublevar;
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
int     conv_percent(char *str, t_properties v);
int     conv_diouxX(t_properties v, va_list args);
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
int     get_tflag(char *s);
/*
**
*/
int     ft_printf(const char *format, ...);
void    fill_structure(char *s, t_properties **v, char c);
int     conv_type(char *s, t_properties *v, void (*f)(char *, t_properties **, char ), char *str);
char    *get_length(char *s);
void    print(int count, char c);
char    *ft_llitoa_base(unsigned long long int n, t_properties v);
int     is_dot(char *s);
void    init_structure(t_holder *var);
t_arg *parser(char *format);
/*
** FLOAT OPERATION;
*/
char  *multi(char *n1, char *n2);
char  *add(char *n1, char *n2);
char  *multiplication(int j, t_properties v);
int    move_point(char *arr, int index);
char   *delete_range_before_point(char *str);
char *multiplication(int j, t_properties v);
char    *rounding(char *float_nbr, t_properties v);
void    debug(t_properties v);
#endif
