#include "incs/philosophers.h"

int	mod_perror(char *error)
{
	int	i;

	i = 0;
	while (error[i])
	{
		write(2, &error[i], 1);
		i++;
	}
	return (1);
}
