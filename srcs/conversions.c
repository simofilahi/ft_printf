#include "ft_printf.h"


void casting(t_properties v, long long int *n, va_list args)
{
    if (ft_strcmp(v.length, "d") == 0 || ft_strcmp(v.length, "i") == 0)
        *n = (int)va_arg(args, long long int);
    else if (ft_strcmp(v.length, "o") == 0 || ft_strcmp(v.length, "u") == 0 ||\
             ft_strcmp(v.length, "x") == 0 || ft_strcmp(v.length, "X") == 0)
        *n = (unsigned int)va_arg(args, unsigned long long int);
    if (ft_strcmp(v.length, "hd") == 0 || ft_strcmp(v.length, "hi") == 0)
        *n = (short)va_arg(args, long long int);
    else if (ft_strcmp(v.length, "ho") == 0 || ft_strcmp(v.length, "hu") == 0 ||\
             ft_strcmp(v.length, "hx") == 0 || ft_strcmp(v.length, "hX") == 0)
        *n = (unsigned short)va_arg(args, unsigned long long int);
    else if (ft_strcmp(v.length, "hhd") == 0 || ft_strcmp(v.length, "hhi") == 0)
        *n = (signed short)va_arg(args, long long int);
    else if (ft_strcmp(v.length, "hho") == 0 || ft_strcmp(v.length, "hhu") == 0 ||\
            ft_strcmp(v.length, "hhx") == 0 || ft_strcmp(v.length, "hhX") == 0)
        *n = (unsigned char)va_arg(args, unsigned long long int);
    else if (ft_strcmp(v.length, "ld") == 0 || ft_strcmp(v.length, "li") == 0)
        *n = (long)va_arg(args, long long int);
    else if (ft_strcmp(v.length, "lo") == 0 || ft_strcmp(v.length, "lu") == 0 ||\
             ft_strcmp(v.length, "lx") == 0 || ft_strcmp(v.length, "lX") == 0)
        *n = (unsigned long)va_arg(args, unsigned long long int);
    else if (ft_strcmp(v.length, "lld") == 0 || ft_strcmp(v.length, "lli") == 0)
        *n = va_arg(args, long long int);
    else if (ft_strcmp(v.length, "llo") == 0 || ft_strcmp(v.length, "llu") == 0 ||\
            ft_strcmp(v.length, "llx") == 0 || ft_strcmp(v.length, "llX") == 0)
        *n = va_arg(args, unsigned long long int);
}

int     conv_o(t_properties v, va_list args)
{
    t_holder var;

    init_structure(&var);
    casting(v, &var.n, args);
    var.str = ft_llitoa_base(var.n, 8, 0);
    var.n = (var.n < 0) ? var.n * -1 : var.n;
    if (v.width == -1 && v.pres != -1)
    {
        var.str = apply_pres(v, var.str, var.n,0);
        var.str = apply_flags(v, var.str, var.n);
    }
    else if (v.width != -1 && v.pres == -1)
    {
        var.str = apply_flags(v, var.str, var.n);
        var.str = apply_width(v, var.str, var.n, 0);
    }
    else if (v.width != -1 && v.pres != -1)
        var.str = apply_width_pres(v, var.str, var.n, 0);
    else
        var.str = apply_flags(v, var.str, var.n);
    var.len = ft_strlen(var.str);
    ft_putstr(var.str);
    ft_strdel(&var.str);
    return (var.len);
}

int     conv_d(t_properties v, va_list args)
{
    t_holder var;

    init_structure(&var);
    casting(v, &var.n, args);
    var.str = ft_llitoa_base(var.nbr, 10, 0);
    if (v.width == -1 && v.pres != -1)
    {
        var.str = apply_pres(v, var.str, var.n,0);
        var.str = apply_flags(v, var.str, var.n);
    }
    else if (v.width != -1 && v.pres == -1)
    {
        var.str = apply_flags(v, var.str, var.n);
        var.str = apply_width(v, var.str, var.n, 0);
    }
    else if (v.width != -1 && v.pres != -1)
        var.str = apply_width_pres(v, var.str, var.n, 0);
    else
        var.str = apply_flags(v, var.str, var.n);
    ft_putstr(var.str);
    var.len = (int)ft_strlen(var.str);
    return (var.len);
}

int     conv_i(t_properties v, va_list args)
{
    t_holder var;

    init_structure(&var);
    casting(v, &var.n, args);
    var.nbr = (var.n < 0) ? var.n * -1 : var.n;
    var.str = ft_llitoa_base(var.nbr, 10, 0);
    if (v.width == -1 && v.pres != -1)
    {
        var.str = apply_pres(v, var.str, var.n, 0);
        var.str = apply_flags(v, var.str, var.n);
    }
    else if (v.width != -1 && v.pres == -1)
    {
        var.str = apply_flags(v, var.str, var.n);
        var.str = apply_width(v, var.str, var.n, 0);
    }
    else if (v.width != -1 && v.pres != -1)
        var.str = apply_width_pres(v, var.str, var.n, 0);
    else
        var.str = apply_flags(v, var.str, var.n);
    ft_putstr(var.str);
    var.len = (int)ft_strlen(var.str);
    return (var.len);
}


int     conv_u(t_properties v, va_list args)
{
    t_holder var;

    init_structure(&var);
    casting(v, &var.n, args);
    var.str = ft_llitoa_base(var.n, 10, 0);
    var.n = (var.n < 0) ? var.n * -1 : var.n;
    if (v.width == -1 && v.pres != -1)
    {
        var.str = apply_pres(v, var.str, var.n,0);
        var.str = apply_flags(v, var.str, var.n);
    }
    else if (v.width != -1 && v.pres == -1)
    {
        var.str = apply_flags(v, var.str, var.n);
        var.str = apply_width(v, var.str, var.n, 0);
    }
    else if (v.width != -1 && v.pres != -1)
        var.str = apply_width_pres(v, var.str, var.n, 0);
    else
        var.str = apply_flags(v, var.str, var.n);
    ft_putstr(var.str);
    var.len = (int)ft_strlen(var.str);
    return (var.len);
}

int     conv_x(t_properties v, va_list args)
{
    t_holder var;

    init_structure(&var);
    casting(v, &var.n, args);
    var.str = ft_llitoa_base(var.n, 16, 0);
    var.n = (var.n < 0) ? var.n * -1 : var.n;
    if (v.width == -1 && v.pres != -1)
    {
        var.str = apply_pres(v, var.str, var.n, 0);
        var.str = apply_flags(v, var.str, var.n);
    }
    else if (v.width != -1 && v.pres == -1)
    {
        var.str = apply_flags(v, var.str, var.n);
        var.str = apply_width(v, var.str, var.n, 0);
    }
    else if (v.width != -1 && v.pres != -1)
        var.str = apply_width_pres(v, var.str, var.n, 0);
    else
        var.str = apply_flags(v, var.str, var.n);
    ft_putstr(var.str);
    var.len = (int)ft_strlen(var.str);
    return (var.len);
}

int     conv_X(t_properties v, va_list args)
{
    t_holder var;

    init_structure(&var);
    casting(v, &var.n, args);
    var.str = ft_llitoa_base(var.n, 16, 1);
    var.n = (var.n < 0) ? var.n * -1 : var.n;
    if (v.width == -1 && v.pres != -1)
    {
        var.str = apply_pres(v, var.str, var.n,0);
        var.str = apply_flags(v, var.str, var.n);
    }
    else if (v.width != -1 && v.pres == -1)
    {
        var.str = apply_flags(v, var.str, var.n);
        var.str = apply_width(v, var.str, var.n, 0);
    }
    else if (v.width != -1 && v.pres != -1)
        var.str = apply_width_pres(v, var.str, var.n, 0);
    else
        var.str = apply_flags(v, var.str, var.n);
    ft_putstr(var.str);
    var.len = (int)ft_strlen(var.str);
    return (var.len);
}