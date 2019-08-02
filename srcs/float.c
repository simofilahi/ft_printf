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

	if (!(result = (char *)malloc(sizeof(char) * 200)))
		return (NULL);
	ft_bzero(result, 200);
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
    if (!(add = ft_strnew(200)))
        return (NULL);
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

char *ConvertMantisatoDecimal(char *arr, t_properties v, int *j)
{
  
    int i;
    char *result;
    char *tmp;
     char **tab;
     int k;

    (void)v;
    i = 0;
    result = NULL;
    k = 1;
    while (i < 24)
    {
        if (arr[i] == '1')
        {
            tmp = multiplication(k, v);
            result = (result == NULL) ? ft_strjoin("", tmp) : ft_strjoin(result, tmp);
            result = ft_strjoin(result, "+");
            *j = k;
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

int     conv_f(t_properties v, va_list args)
{
    char *new_mant;
    char *mantissa;
    int i;
     int len_1;
     int len_2;
    int expo;
    (void)v;

    if (!(new_mant = ft_strnew(23)))
        return (0);
    i = 0;
    while (i < 23)
        new_mant[i++] = '0';
    n_data var;
    var.nbr = va_arg(args, double);
    v.base = 2;
    mantissa = ft_llitoa_base(var.data.mantisa, v);
    len_1 = 22;
    len_2 = ft_strlen(mantissa) - 1;
    while (len_1 >= 0)
        new_mant[len_1--] = mantissa[len_2--];
    // ft_putstr("mantissa ==>");
    // ft_putendl(new_mant);
    expo = var.data.expo - 127;
     ft_putstr("expo before ==> ");
    ft_putnbr(expo);
    ft_putchar('\n');
    // ft_putchar('\n');
    // v.base = 10;
   
    // printf("expo ==> %d\n", expo);
    // arr = (expo > 0) ? ft_strjoin("1.", arr) : ft_strjoin("0.", arr);
    // move_point(arr, expo);
    // // tab = ft_strsplit(arr, '.');
    // printf("new arr ==> %s\n", arr);
    // printf("tab[0] ==>%s\ntab[1] ==>%s\n", tab[0], tab[1]);
    // //  printf("final arr ==> %s\n", arr);
    // //var.nbr = (double)var.nbr;
    // printf("var.nbr ==> %f\n", var.nbr);
    // printf("mantissa ==> %d\n", var.data.mantisa);
    // printf("expo ==> %d\n", var.data.expo);
    // printf("sign ==> %d\n", var.data.sign);
    // tab[0] = ConvertToDecimal(tab[0],)
    int flag = 0;
    if (expo < 0)
    {
        expo *= -1;
        flag = 1;
    }
    char *n1 ;

    if (expo > 0)
            n1 = ft_strdup("2");
    else if (expo == 0)
        n1 = ft_strdup("1");
    // if (!flag)
    // {
        while (expo > 1)
        {
            n1 = multi(n1, "2");
            expo--;
        }
    // }
    // else
    // // {
    //     char *tmp = multiplication(expo, v);
    //     ft_putstr("here tmp ==> ");
    //     ft_putendl(tmp);
    // }
    
    ft_putstr("n1 ==> ");
    ft_putendl(n1);
    int j = 0;
     char *man_result = ConvertMantisatoDecimal(new_mant, v, &j);
    //  ft_putstr("final result ==> ");
    // ft_putendl(man_result);
     char *final_result = multi(n1, man_result);
     int len = ft_strlen(final_result);
      i = len - j;
    char *ffinal_result = ft_strsub(final_result, i, len);
    char *ordinary = ft_strsub(final_result, 0, i);
    ordinary = add(n1, ordinary);
    ffinal_result = ft_strjoin(".", ffinal_result);
    ffinal_result = ft_strjoin(ordinary, ffinal_result);
    ft_putstr("final result ==> ");
    ft_putendl(ffinal_result);
    // ft_putstr("ordinary  ==> ");
    // ft_putendl(ordinary);

    //(void)string;
   // str = float_to_str(v, n);
    // n = (n < 0) ? n * -1 : n;
    // if (v.width == -1 && v.pres != -1)
    // {
    //     str = apply_pres(v, str, n,0);
    //     str = apply_flags(v, str, n);
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
