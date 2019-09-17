//
#include <stdio.h>
#include "ft_printf.h"

int	conv(char c)
{
	if (c == '%' ||\
	    c == 'c' ||\
	    c == 's' ||\
	    c == 'p' ||\
	    c == 'd' ||\
	    c == 'i' ||\
	    c == 'o' ||\
	    c == 'u' ||\
	    c == 'x' ||\
	    c == 'X' ||\
	    c == 'f')
	{
	       return (1);
	}
	return (0);
}

int	newarg(char c)
{
	if (c == '#' ||\
	    c == '+' ||\
	    c == '-' ||\
	    c == '0' ||\
	    (c >= '0' && c <= '9'))
	{
	       return (1);
	}
	return (0);
}

int	simple_len(char *s)
{
	int	counter;

	counter = 0;
	while (*s && *s != '%')
	{
		counter++;
		s++;
	}
	return (counter);
}

int	complex_len(char *s)
{
	int	counter;

	counter = 0;
	if (*s == '%' && *(s + 1) == '%')
	{
		while (*s && *s == '%')
		{
			if (newarg(*(s + 1)))
				return (counter);
			counter++;
			s++;
		}
		return (counter);
	}
	while (*s)
	{
		if (conv(*(s + 1)))
			return (counter + 2);
		counter++;
		s++;
	}
	return (counter);
}

void list_push(t_arg **head, t_arg **tail, char *arg, int flag)
{
	t_arg *node;

	if (!(node = (t_arg *)malloc(sizeof(t_arg))))
		return ;
	node->arg = ft_strdup(arg);
	node->flag = flag;
	node->next = NULL;
	if (!(*head))
	{
		*head = *tail = node;
		return ;
	}
	(*tail)->next = node;
	(*tail) = node;
}

int  simple_arg(char **format, char **arg, t_arg **head, t_arg **tail)
{
	int	len;

	if ((*format)[0] != '%')
	{
		len = simple_len((*format));
		(*arg) = ft_strsub((*format), 0, len);
		(*format) += len;
		list_push(head, tail, *arg, 0);
		return (1);
	}
	else if ((*format)[0])
		return (1);
	return (0);

}

int  complex_arg(char **format, char **arg, t_arg **head, t_arg **tail)
{
	int	len;

	if ((*format)[0] == '%')
	{
		len = complex_len((*format));
		(*arg) = ft_strsub((*format), 0, len);
		(*format) += len;
		list_push(head, tail, *arg, 1);
		return (1);
	}
	else if ((*format)[0])
		return (1);
	return (0);
}

t_arg *parser(char *format)
{
	char	*arg;
	t_arg	*head;
	t_arg	*tail;

	arg = NULL;
	head = NULL;
	tail = NULL;
	while ("1337")
	{
		if (!(simple_arg(&format, &arg, &head, &tail)))
			break;
		else if (!(complex_arg(&format, &arg, &head, &tail)))
			break;
		ft_strdel(&arg);
	}
	return (head);
}
