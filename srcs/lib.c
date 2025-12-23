#include "incs/philosophers.h"

size_t	ft_strlen(char *str)
{
	size_t len;

	len = 0;
	if (!str)
		return (0);
	while (str[len])
		len++;
	return (len);
}

int	ft_atoi(char *number)
{
	int nb;
	int i;
	int sign;

	nb = 0;
	i = 0;
	sign = 1;
	if (number < 0)
		sign = -sign;
	while (number[i])
	{
		nb = nb * 10 + (number[i] - '0');
		i++;
	}
	return (nb);
}

int	ft_atol(char *number)
{
	long  nb;
	int	  i;
	int	  sign;

	nb = 0;
	i = 0;
	sign = 1;
	if (number < 0)
		sign = -sign;
	while (number[i])
	{
		nb = nb * 10 + (number[i] - '0');
		i++;
	}
	return (nb);
}
