#include "incs/philosophers.h"

bool  check_overflow(char *number)
{
	if (ft_strlen(number) > 10 || (ft_atol(number) < 0 || ft_atol(number) > INT_MAX))	
		return (mod_perror("[!] Number go out of bound (max 32bit sint) !\n"));
	return (0);
}

bool  string_isdigit(char *number)
{
	int i;

	i = 0;
	while (number[i])
	{
		if (!(number[i] >= '0' && number[i] <= '9'))
			return (mod_perror("[!] Non-number character detected !"));
		i++;
	}
	return (0);
}

bool  check_number(char *number)
{
	if (string_isdigit(number) || check_overflow(number))
		return (1);
	return (0);
}

bool  parsing(int argc, char **argv, t_philo *philo)
{
	int	i;

	i = 0;
	memset(philo, 0, 5);
	while (i < argc - 1)
	{
		if (check_number(argv[i + 1]))
			return (1);
		philo->parameter[i] = ft_atoi(argv[i + 1]);
		i++;
	}
	if (philo->parameter[4] == 0)
		philo->parameter[4] = -1;
	philo->nb_fork = philo->parameter[0];
	return (0);
}
