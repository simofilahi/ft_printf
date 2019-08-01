#include "ft_printf.h"

int     ft_cmp(char c, const char *ptr)
{
    while (*ptr)
        if (c == *ptr++)
            return (1);
    return (0);
}
// int     arg_len(char *str, int len)
// {

// }

void    create_list(t_arg **tail_ref, char *s, int flag)
{
    t_arg *new_node;

    if (!(new_node = (t_arg *)malloc(sizeof(t_arg))))
        return ;
    new_node->arg = ft_strdup(s);
    new_node->flag = flag;
    new_node->next = NULL;
    if (!(*tail_ref))
    {
        (*tail_ref) = new_node;
		(*tail_ref)->prev = NULL;
    }
    else
    {
        (*tail_ref)->next = new_node;
		new_node->prev = (*tail_ref);
        (*tail_ref) = new_node;
    }
}

t_arg    *parsing(const char *s, const char *conv)
{
	t_arg *tail_ref;
	int len;
	char *arr;
	int flag;
	int count;

	len = strlen(s) - 1;
	arr = NULL;
	(void)conv;
	tail_ref = NULL;
	int i;
	while (len >= 0)
	{
		arr = malloc(sizeof(char)*50);
		flag = 0;
		// if (s[len] == '\n')
		// {
		// 	i = 0;
		// 	while (len >= 0 && s[len] == '\n')
		// 		arr[i++] = s[len--];
		// 	arr[i] = '\0';
		// 	len++;
		// 	ft_strrev(arr);
		// }
		// else if (ft_cmp(s[len], conv) && s[len] != '%')
		// {
		// 	i = 0;
		// 	count = 0;
		// 	while (len >= 0 && s[len] != '\n')
		// 	{
		// 		if (count >= 3 && (s[len] == ' ' || ft_cmp(s[len], conv)))
		// 		{
		// 			len++;
		// 			break;
		// 		}
		// 		if (s[len] == '%' && (ft_isalpha(s[len + 1]) || s[len + 1] == ' '))
		// 		{
		// 			len++;
		// 			break;
		// 		}
		// 		else if (s[len] == '%' && !ft_isalpha(s[len + 1]))
		// 		{
		// 			arr[i++] = s[len];
		// 			break ;
		// 		}
		// 		else
		// 			arr[i++] = s[len];
		// 		if (ft_isalpha(arr[i - 1]))
		// 			count++;
		// 		len--;
		// 	}
		// 	arr[i] = '\0';
		// 	if (s[len] == '\n')
		// 		len++;
		// 	ft_strrev(arr);
		// }
		// else if (s[len] == '%' && s[len - 1] != '%')
		// {
		// 	i = 0;
		// 	arr[i++] = s[len--];
		// 	while (len >= 0 && s[len] != '%' && s[len] != '\n')
		// 		arr[i++] = s[len--];
		// 	arr[i++] = s[len];
		// 	arr[i] = '\0';
		// 	if (s[len] == '\n')
		// 		len++;
		// 	flag = 1;
		// 	ft_strrev(arr);
		// }
		// else if (s[len] == '%' && s[len - 1] == '%')
		// {
		// 	i = 0;
		// 	while (s[len] == '%' && len >= 0)
		// 		arr[i++] = s[len--];
		// 	arr[i] = '\0';
		// 	len++;
		// 	ft_strrev(arr);
		// 	flag = 1;
		// }
		// else if (ft_isalpha(s[len]))
		// {
		// 	i = 0;
		// 	while (len >= 0 && ft_isalpha(s[len]))
		// 		arr[i++] = s[len--];
		// 	if (s[len] == '%')
		// 	{
		// 		arr[i++] = s[len];
		// 		flag = 1;
		// 	}
		// 	else
		// 		len++;
		// 	arr[i] = '\0';
		// 	ft_strrev(arr);
		// }
		if (ft_cmp(s[len], conv))
		{
			count = 0;
			i = 0;
			while (len >= 0 && s[len] != '\n')
			{
				if (count > 3)
				{
					if (s[len] == '%' || ft_cmp(s[len], conv))
					{
						len++;
						break ;
					}
				}
				if (s[len] == '%')
				{
					arr[i++] = s[len];
					break ;
				}
				else
				{
					arr[i] = s[len];
					if (ft_isalpha(arr[i]))
						count++;
					i++;
				}
				len--;
			}
			arr[i] = '\0';
			ft_strrev(arr);
			if (s[len] == '\n')
				len++;
		}
		else if ((ft_isalpha(s[len]) || s[len] == '\n') && !ft_cmp(s[len], conv))
		{
			i = 0;
			while (len >= 0)
			{
				if (ft_cmp(s[len], conv))
				{
					len++;
					break ;
				}
				else
					arr[i++] = s[len];
				len--;
			}
			arr[i] = '\0';
			ft_strrev(arr);
		}
		else if (s[len] == '%' && s[len - 1] == '%')
		{
			i = 0;
			while (s[len] == '%' && len >= 0)
				arr[i++] = s[len--];
			arr[i] = '\0';
			len++;
			ft_strrev(arr);
			flag = 1;
		}
		create_list(&tail_ref, arr, flag);
		len--;
	}
	return (tail_ref);
}