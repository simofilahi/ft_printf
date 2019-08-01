#include "ft_printf.h"

int    conv_type(char *s, t_properties *v, void (*f)(char *, t_properties **, char ), char *conv_arr)
{
    int len;
    int len_2;

    len  = (int)ft_strlen(s) - 1;
    len_2 = (int)ft_strlen(conv_arr);
    // ft_putstr_fd("here str ==>",2);
    // ft_putstr_fd(s, 2);
 //   printf("s ==> %s\n", s);
    //ft_putendl_fd("HERE", 2);
    if (len_2 == 1)
    {
    //         printf("s[len] == %c\n", s[len]);
    // printf("conv_arr[0] ==> %c\n", conv_arr[0]);
        if (conv_arr[0] == s[len])
        {
              
            f(s, &v, s[len]);
            return (1);
        }
        return (0);
    }
    while (*conv_arr)
    {
        if (s[len] == *conv_arr)
        {
            f(s, &v, s[len]);
            return (1);
        }
        conv_arr++;
    }
    return (0);
}


int     conv_c(t_properties v, va_list args)
{
    char c;
    int len;

    c = va_arg(args, int);
    len = 1;
    if (v.f_flag == '-')
    {
        ft_putchar(c);
        if (v.width > len)
             print(v.width - len, ' ');
    }
    else if (v.width > len)
    {
        if (v.width > len)
            print(v.width - len, ' ');
        ft_putchar(c);
    }
    else
        ft_putchar(c);
    return ((v.width > len) ? v.width : len);
}

int     conv_s(t_properties v, va_list args)
{
    char *string;
    int  len;

    string = va_arg(args, char *);
    if (string == NULL)
        string = ft_strdup("(null)");
    len = (int)ft_strlen(string);
    if (v.pres != -1 && v.width == -1)
        string = apply_pres(v, string, 0, 1);
    else if (v.pres == -1 && v.width != -1)
        string = apply_width(v, string, 0, 1);
    else if (v.pres != -1 && v.width != -1)
        string = apply_width_pres(v, string, 0, 0);
    ft_putstr(string);
    len = (int)ft_strlen(string);
    return (len);
}

int     conv_p(t_properties v, va_list args)
{
    long long int   ret;
    char            *str;
    char            *tmp;
    int             len;

    ret = va_arg(args, long long int);
    str = ft_llitoa_base(ret, v);
    tmp = str;
    str = ft_strjoin("0x", str);
    ft_strdel(&tmp);
    if (v.width != -1)
       str = apply_width(v, str, 0, 0);
    ft_putstr(str);
    len = (int)ft_strlen(str);
    ft_strdel(&str);
    return (len);
}

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

    //  ft_putstr("here n1 ==>");
    // ft_putstr(n2);
    // ft_putchar('\n');
    //  ft_putstr("here n2 ==>");
    // ft_putstr(n2);
    // ft_putchar('\n');
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
    // ft_putstr("here result ==>");
    // ft_putstr(result);
    // ft_putchar('\n');
	return (result);
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
    // ret = ft_strsub(ret, j - 1, ft_strlen(ret));
       ft_putstr("here ret ==> ");
    ft_putendl(ret);
  return (ret);
}

char *ConvertMantisatoDecimal(char *arr, t_properties v)
{
  
    int i;
    int j;
    // char *new_str;
    char *tmp;

    (void)v;
    i = 0;
    j = 1;
    // new_str = NULL;
    while (i < 24)
    {
        if (arr[i] == '1')
        {
             ft_putstr("here j ==> ");
    ft_putnbr(j);
    ft_putchar('\n');
            tmp = multiplication(j, v);
            // new_str = (new_str == NULL) ? ft_strjoin("", tmp) : ft_strjoin(new_str, tmp);
            // new_str = ft_strjoin(new_str, "+");
        }
        j++;
        i++;
    }
    // ft_putstr("new_str ==> ");
    // ft_putendl(new_str);
//    new_str = addition(new_str);
   return (NULL);
}

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
    ft_putstr("mantissa ==>");
    ft_putendl(new_mant);
    expo = var.data.expo - 127;
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
    
     char *string = ConvertMantisatoDecimal(new_mant, v);
    (void)string;
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

int conv_b(t_properties v, va_list args)
{
     long long int   n;
     char            *str;
     int             len;

    n = va_arg(args, long int);
    str = ft_llitoa_base(n, v);
    ft_putstr(str);
    ft_strdel(&str);
    len = (int)ft_strlen(str);
    return (len);
}