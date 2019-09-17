#include "ft_printf.h"

char *ConvertMantisatoDecimal(char *arr, t_properties v, int *index)
{
    char    *result;
    char    *tmp;
    char    **tab;
    int     i;
    int     k;

    result = NULL;
    k = 1;
    i = 0;
    while (arr[i])
    {
        if (arr[i] == '1')
        {
            tmp = multiplication(k, v);
            result = (result == NULL) ? ft_strjoin("", tmp) : ft_strjoin(result, tmp);
            result = ft_strjoin(result, "+");
            *index = k;
        }
        k++;
        i++;
    }
    tab = ft_strsplit(result, '+');
    result = add(tab[0], tab[1]);
    i = 2;
    while (tab[i])
         result = add(result, tab[i++]);
   return (result);
}


char     *expo_calc(n_data var)
{
    char *expo_calc;
    char *tmp;
    int  expo;
    int  flag;

    tmp = NULL;
    expo = var.doublevar.expo - 16383;
    printf("%d\n", expo);
    flag = 0;
    if (expo < 0)
    {
        expo *= -1;
        expo_calc = ft_strdup("5");
        flag = 1;
    }
    else if (expo > 0)
        expo_calc = ft_strdup("2");
    else if (expo == 0)
        expo_calc = ft_strdup("1");
     while (expo > 1)
    {
        tmp = expo_calc;
        if (flag)
            expo_calc = multi(expo_calc, "5");
        else
            expo_calc = multi(expo_calc, "2");
        ft_strdel(&tmp);
        expo--;
    }
    return (expo_calc);
}

char    *move_point_2(char *final_result, int index)
{
    char    *new_str;
    int     len;
    int     i;
    int     j;
    int     diff;

    len = ft_strlen(final_result);
    if (!(new_str = ft_strnew(len + 1)))
        return (NULL);
    diff = len - index;
    i = 0;
    j = 0;
    while (i < len + 1)
    {
        if (i == diff)
            new_str[i] = '.';
        else
            new_str[i] = final_result[j++];
        i++;
    }
    new_str[i] = '\0';
    if (new_str[0] == '.')
        new_str = ft_strjoin("0", new_str);
    return (new_str);
}

char *correct_mant(char *bin_mant)
{
    int len;
    int  i;
    char *new_mant;

    len = (int)ft_strlen(bin_mant) - 1;
    if (!(new_mant = ft_strnew(63)))
        return (NULL);
    new_mant[63] = '\0';
    i = 62;
    while (i >= 0)
    {
        if (len >= 0)
            new_mant[i--] = bin_mant[len--];
        else
            new_mant[i--] = '0';
    }
    return(new_mant);
}

char    *float_calc(t_properties v, va_list args)
{
    n_data  var;
    char    *bin_mant;
    char    *expo;
     char    *decimal_mant;
    char    *final_result;
    int     index;

    v.base = 2;
    index = 0;
    var.nbr = va_arg(args, double);
            // printf("here bin_mantissa %s\n", bin_mant);
        // printf("here mantissa %ld\n", var.doublevar.mantisa);
        // printf("here expo %ld\n", var.doublevar.expo);
        //  printf("here d %d\n", var.doublevar.d);
    final_result = NULL;
    if (var.doublevar.expo == 32767 && var.doublevar.mantisa > 0)
        return (ft_strdup("nan"));
    else if (var.doublevar.expo == 32767 && var.doublevar.mantisa == 0)
    {
        if (var.doublevar.sign == 0)
            return (ft_strdup("inf"));
        return (ft_strdup("-inf"));
    }
    else if (var.doublevar.expo == 0 && var.doublevar.mantisa == 0)
    {
        if (var.doublevar.sign == 0)
            return ((v.pres != 0) ? ft_strdup("0.000000") : ft_strdup("0"));
        return ((v.pres != 0) ? ft_strdup("-0.000000") : ft_strdup("-0"));
    }
    else if (var.doublevar.expo >= 0 && var.doublevar.mantisa > 0)
    {
        bin_mant = ft_llitoa_base(var.doublevar.mantisa, v);
        char *tmp;
        tmp = bin_mant;
        bin_mant = correct_mant(bin_mant);
        ft_strdel(&tmp);
        final_result = NULL;
        expo = expo_calc(var);
        decimal_mant = ConvertMantisatoDecimal(bin_mant, v, &index);
        decimal_mant = ft_strjoin((var.doublevar.d == 1) ? "1" : "0", decimal_mant);
        final_result = multi(expo, decimal_mant);
        index = (var.doublevar.expo - 16383 < 0) ? index + ((var.doublevar.expo - 16383) * -1) : index;
        final_result = move_point_2(final_result, index);
        if (var.doublevar.sign == 1)
            final_result = ft_strjoin("-", final_result);
    }
    return (final_result);
}

int     conv_f(t_properties v, va_list args)
{
    char *float_nbr;
    char **arr;
    int n;
    //  debug(v);
    float_nbr = float_calc(v, args);
    n = 0;
    if (ft_strcmp(float_nbr, "nan") == 0)
        float_nbr = apply_width(v,float_nbr, n, 0);
    else if (ft_strcmp(float_nbr, "inf") == 0 || ft_strcmp(float_nbr, "-inf") == 0)
    {
        if (v.f_flag == '+' && v.s_flag == '0')
            v.s_flag = -1;
         v.f_flag = (v.f_flag == '0') ? -1 : v.f_flag;
        float_nbr = apply_flags(v,float_nbr, n);
        float_nbr = apply_width(v,float_nbr, n, 0);
    }
    else
    {
        arr = ft_strsplit(float_nbr, '.');
        arr[0] = ft_strjoin(arr[0], ".");
        if ((v.f_flag == '+' && (v.s_flag == '-' || v.t_flag == '-')))
            v.f_flag = '-';
        if (v.width == -1 && v.pres != -1)
        {
                arr[1] = apply_pres(v, arr[1], n,0);  
                float_nbr = ft_strjoin(arr[0], arr[1]);
            float_nbr = apply_flags(v, float_nbr, n);
        }
        else if (v.width != -1 && v.pres == -1)
        {
            float_nbr = apply_flags(v,float_nbr, n);
            float_nbr = apply_width(v,float_nbr, n, 0);
        }
        else if (v.width != -1 && v.pres != -1)
        {
             arr[1] = apply_pres(v,arr[1], n, 0);
             float_nbr = ft_strjoin(arr[0], arr[1]);
             float_nbr = apply_flags(v, float_nbr, n);
             float_nbr = apply_width(v, float_nbr, n, 0);
        }
        else
            float_nbr = apply_flags(v, float_nbr, n);
    }
    ft_putstr(float_nbr);
    return (ft_strlen(float_nbr));
}