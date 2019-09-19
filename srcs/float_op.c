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

	if (!(result = (char *)malloc(sizeof(char) * 1000)))
		return (NULL);
	ft_bzero(result, 1000);
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

    if (!(ft_strlen(n1) > ft_strlen(n2)))
        swap(&n1, &n2);
    len_n1 = ft_strlen(n1) - 1;
    len_n2 = ft_strlen(n2) - 1;
    if (!(add = ft_strnew(1000)))
        return (NULL);
    ft_bzero(add, 1000);
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

char *multiplication(int j, t_properties v)
{
    char *n1;
    char *n2;
    int   k;
     char  *ret;
    char  *tmp;
    int f;

    k = j;
    (void)v;
    n1 = ft_strdup("10");
    while (k > 1)
    {
        tmp = n1;
        n1 = multi(n1, "10");
        ft_strdel(&tmp);
        k--;
    }
    k = j;
    n2 = ft_strdup("5");
    while (k > 1)
    {
        tmp = n2;
        n2 = multi(n2, "5");
        ft_strdel(&tmp);
        k--;
    }
    ret = ft_strjoin(n1, n2);
    f = move_point(ret, j);
    ret = delete_range_before_point(ret);
    return (ret);
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

char    *rounding(char *float_nbr, t_properties v)
{
    int i;
    int j;
    int flag;
    int flag2;
    int k;

    i = -1;
    flag = 0;
    flag2 = 0;
    j = 0;
    while (float_nbr[++i])
    {
        if (float_nbr[i] == '.')
        {
            k = i - 1;
            flag = 1;
            continue;
        }
        if (flag)
        {
            if (v.pres == j)
            {
                flag2 = 1;
                if (float_nbr[i] - '0' > 5)
                    float_nbr[k] = (float_nbr[k] - '0') + 1 + '0';
                else if (float_nbr[i] - '0' == 5)
                {
                    if ((float_nbr[k] - '0') % 2 == 1)
                        float_nbr[k] = (float_nbr[k] - '0') + 1 + '0';
                    return (float_nbr);
                }
                else if (float_nbr[i] - '0' < 5)
                    break ;
                k--;
                if (k < 0)
                    break ;
            }
            if (!flag)
                k = i;
            j++;
        }
    }
    return (float_nbr);
}