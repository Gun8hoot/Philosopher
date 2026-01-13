/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nclavel <nclavel@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 20:16:37 by nclavel           #+#    #+#             */
/*   Updated: 2026/01/13 08:32:08 by nclavel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "incs/philosophers.h"

void  forks_breakdown(t_shared *share)
{
	int	  i;

	i = 0;
	while (i < share->philo[0].nb_max)
	{
		if (i == 0)
			share->philo[i].fork_r = &share->philo[share->philo[i].nb_max - 1].fork_l;
		else
			share->philo[i].fork_r = &share->philo[i - 1].fork_l;
		i++;
	}
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

bool  put_in_struct(t_shared *share, int nb_max_philo, int argc, char **argv)
{
	int	i;

	i = 0;
	share->philo = calloc(nb_max_philo, sizeof(t_philo));
	if (!share->philo)
		return (mod_perror(EALLOC));
	while (i < nb_max_philo)
	{
		memset(&share->philo[i], 0, sizeof(t_philo));
		share->philo[i].stdout_lock = &share->stdout_lock;
		share->philo[i].dead_status = &share->dead_status;
		share->philo[i].dead_lock = &share->dead_lock;
		share->philo[i].nb_max = nb_max_philo;
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
		if (string_isdigit(argv[i + 1]))
			return (false);
		i++;
	}
	if (!put_in_struct(shared, ft_atoi(argv[1]), argc, argv))
		return (false);
	forks_breakdown(shared);
	return (true);
}
