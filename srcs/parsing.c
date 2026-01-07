/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nclavel <nclavel@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 20:16:37 by nclavel           #+#    #+#             */
/*   Updated: 2026/01/07 01:31:13 by nclavel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "incs/philosophers.h"

bool  check_overflow(char *number)
{
	if (ft_strlen(number) > 10 || (ft_atol(number) < 0 || ft_atol(number) > INT_MAX))	
		return (mod_perror(EOOB));
	return (0);
}

bool  string_isdigit(char *number)
{
	int i;

	i = 0;
	while (number[i])
	{
		if (!(number[i] >= '0' && number[i] <= '9'))
			return (mod_perror(EALNUM));
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

bool  put_in_struct(t_shared *share, int nb_philo, int argc, char **argv)
{
	int	i;

	i = 0;
	share->philo = calloc(nb_philo, sizeof(t_philo));
	if (!share->philo)
		return (mod_perror(EALLOC));
	while (i < nb_philo)
	{
		memset(&share->philo[i], 0, sizeof(t_philo));
		share->philo[i].stdout_lock = &share->stdout_lock;
		share->philo[i].dead_status = &share->dead_status;
		share->philo[i].dead_lock = &share->dead_lock;
		share->philo[i].number_philosophers = nb_philo;
		share->philo[i].time_to_die = ft_atoi(argv[2]);
		share->philo[i].time_to_eat = ft_atoi(argv[3]);
		share->philo[i].time_to_sleep = ft_atoi(argv[4]);
		if (argc == 6)
			share->philo[i].must_eat = ft_atoi(argv[5]);
		else
			share->philo[i].must_eat = -1;
		i++;
	}
	return (true);
}

bool  parsing(int argc, char **argv, t_shared *shared)
{
	int	i;

	i = 0;
	memset(shared, 0, 5);
	while (i < argc - 1)
	{
		if (check_number(argv[i + 1]))
			return (false);
		i++;
	}
	if (!put_in_struct(shared, ft_atoi(argv[1]), argc, argv))
		return (false);
	return (true);
}
