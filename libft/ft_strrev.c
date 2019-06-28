#include "libft.h"

void    ft_strrev(char *s)
{
    int i;
    int j;
    char tmp;

    j = (int)ft_strlen(s);
    i = -1;
    while (++i < --j)
    {
       tmp = s[i];
       s[i] = s[j];
       s[j] = tmp;
    }
}