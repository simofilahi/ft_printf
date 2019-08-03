#include "ft_printf.h"

char  *multi(char *n1, char *n2)
{
	char *result;
	int  n1_len;
	int  n2_len;
	int  i;
	int  j;
	int carry;
	int nbr;
	int k;

	if (!(result = (char *)malloc(sizeof(char) * 1000000)))
		return (NULL);
	ft_bzero(result, 1000000);
	n1_len = ft_strlen(n1) - 1;
	n2_len = ft_strlen(n2) - 1;
	k = 0;
	while (n2_len >= 0)
	{
		j = k;
		carry = 0;
		i = n1_len;
		while (i >= 0)
		{
			nbr = (n2[n2_len] - '0') * (n1[i] - '0') + carry;
			if (result[j])
				nbr += result[j] - '0';
			result[j++] = nbr % 10 + '0';
			carry = nbr / 10;
			i--;
		}
        if (carry > 0)
			result[j] = carry + '0';
		k++;
		n2_len--;
	}
	ft_strrev(result);
	return (result);
}

void swap(char **n1, char **n2)
{
    char *tmp;

    tmp = *n1;
    *n1 = *n2;
    *n2 = tmp;
}

char *add(char *n1, char *n2)
{
    int len_n1;
    int len_n2;
    char *add;
    int carry;
    int index;

    if (!(strlen(n1) > strlen(n2)))
        swap(&n1, &n2);
    len_n1 = strlen(n1) - 1;
    len_n2 = strlen(n2) - 1; 
    if (!(add = ft_strnew(1000000)))
        return (NULL);
    ft_bzero(add, 1000000);
    index = 0;
    carry = 0;
    int sum = 0;
    while (len_n1 >= 0)
    {
        if (len_n1 > len_n2)
        {
            sum = n1[len_n1] - '0' + carry;
            add[index] = sum % 10 + '0';
            carry = sum / 10;
        }
        else
        {
            sum = (n1[len_n1] - '0') + (n2[len_n2] - '0') + carry;
            add[index] = sum % 10 + '0';
            carry = sum / 10;	
            len_n2--;
        }
        index++;
        len_n1--;
    }
    if (carry)
        add[index++] = carry % 10 +'0';
    add[index] = '\0';
    ft_strrev(add);
    return (add);
}

char   *delete_range_before_point(char *str)
{
    int i;
    char *tmp;

    i = 0;
    while (str[i] && str[i] != '.')
            i++;
    tmp = str;
    str = ft_strsub(str, i + 1, ft_strlen(str));
    ft_strdel(&tmp);
    return (str);
}

int    move_point(char *arr, int index)
{
    int len;
    int j;
    char tmp;

    len = ft_strlen(arr) - 1;
    j = 0;
    while (len >= 0)
    {
        if (j == index)
        {
            tmp = arr[len];
            arr[len] = '.';
            arr[len - 1] = tmp;
            j++;
        }
        if (j == index)
            return (j);
        len--;
        j++;
    }
    return (j);
}

char *multiplication(int j, t_properties v)
{
    char *n1;
    char *n2;
    int   k;
     char  *ret;
    char  *tmp;
    int f;

    k = j;
    v.base = 10;
    n1 = ft_strdup("10");
    tmp = ft_strdup("10");
   
    while (k > 1)
    {
        n1 = multi(n1, tmp);
        k--;
    }
    k = j;
    n2 = ft_strdup("5");
    tmp = ft_strdup("5");
    while (k > 1)
    {
        char *ptr;
        ptr = n2;
        n2 = multi(n2, tmp);
        ft_strdel(&ptr);

        k--;
    }
     ret = ft_strjoin(n1, n2);
     f = move_point(ret, j);
     ret = delete_range_before_point(ret);
     return (ret);
}

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
    ft_putstr("count ==>");
    ft_putnbr(i);
    tab = ft_strsplit(result, '+');
    result = add(tab[0], tab[1]);
    i = 2;
    while (tab[i])
         result = add(result, tab[i++]);
   return (result);
}

// void move_point_2(char *str, int index)
// {
//     int len;

//     len = ft_strlen(str) - 1;
//     while (len >= 0 && str[len] == '0')
//         len--;
//     while (len >= 0)
//     {
        
//     }
// }

char     *expo_calc(n_data var)
{
    char *expo_calc;
    char *tmp;
    int  expo;
    int  flag;

    tmp = NULL;
    expo = var.data.expo - 127;
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

char    *copy_mantissa(char *mantissa)
{
    int     len;
    char    *new_mant;
    int     i;

    len = ft_strlen(mantissa) - 1;
    if (!(new_mant = ft_strnew(23)))
        return (0);
    i = 0;
    while (i < 22)
        new_mant[i++] = '0';
    new_mant[i] = '\0';
    while (len >= 0)
    {
        new_mant[len] = mantissa[len];
        len--;
    }
    return (new_mant);
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

char    *float_calc(t_properties v, va_list args)
{
    n_data  var;
    char    *bin_mant;
//    char    *new_bin_mant;
    char    *expo;
    char    *decimal_mant;
    char    *final_result;
    int     index;

    v.base = 2;
    index = 0;
    var.nbr = va_arg(args, double);
    bin_mant = ft_llitoa_base(var.data.mantisa, v);
    if (v.type == 'f')
        bin_mant = ft_strsub(bin_mant, 0, 23);
    ft_putstr("bin_mant ==>");
    ft_putendl(bin_mant);
    // new_bin_mant = copy_mantissa(bin_mant);
    // ft_putstr("new_bin_mant ==>");
    // ft_putendl(new_bin_mant);
    expo = expo_calc(var);
    decimal_mant = ConvertMantisatoDecimal(bin_mant, v, &index);
    ft_putendl("hello");
    if (expo[0] != '0')
        decimal_mant = ft_strjoin("1", decimal_mant);
    final_result = multi(expo, decimal_mant);
    index = (var.data.expo - 127 < 0) ? index + ((var.data.expo - 127) * -1) : 0;
    final_result = move_point_2(final_result, index);
    ft_putstr("final_result ==>");
    ft_putendl(final_result);
    return (final_result);
}
int     conv_f(t_properties v, va_list args)
{
    char *float_nbr;

    float_nbr = float_calc(v, args);
    // if (v.width == -1 && v.pres != -1)
    // {
    //     float_nbr = apply_pres(v, float_nbr, n,0);
    //     float_nbr = apply_flags(v, float_nbr, n);
    // }
    // else if (v.width != -1 && v.pres == -1)
    // {
    //     str = apply_flags(v, str, n);
    //     str = apply_width(v, str, n, 0);
    // }
    // else if (v.width != -1 && v.pres != -1)
    //     str = apply_width_pres(v, str, n, 0);
    // else
    //     str = apply_flags(v, str, n);
    // ft_putstr(str);
    // len = (int)ft_strlen(str);
    return (0);
}
