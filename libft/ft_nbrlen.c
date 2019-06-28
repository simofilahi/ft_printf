#include "libft.h"

int ft_nbrlen(int nbr)
{
    int counter;

    counter = 1;
    if (nbr < 0)
    {
        nbr *= -1;
        counter++;
    }
    while (nbr / 10 > 0)
    {
        nbr /= 10;
        counter++;
    }
    return (counter);
}