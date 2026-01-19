/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nclavel <nclavel@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 20:16:37 by nclavel           #+#    #+#             */
/*   Updated: 2026/01/16 08:41:41 by nclavel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "incs/philosophers.h"

bool	forks_attribution(t_shared *share)
{
	int	i;
	int	nb_max;

	nb_max = share->philo[0].nb_max;
	i = 0;
	while (i < nb_max)
	{
		if (pthread_mutex_init(&share->philo[i].fork_l, NULL))
			return (mod_perror(EMTX));
		if (i == 0)
			share->philo[i].fork_r = &share->philo[nb_max - 1].fork_l;
		else
			share->philo[i].fork_r = &share->philo[i - 1].fork_l;
		i++;
	}
	return (true);
}

bool	string_isdigit(char *number)
{
	int	i;

	i = 0;
	while (number[i])
	{
		if (!(number[i] >= '0' && number[i] <= '9'))
			return (mod_perror(EALNUM));
		i++;
	}
	return (0);
}

bool	init_philo(t_shared *share, int iter, int nb)
{
	memset(&share->philo[iter], 0, sizeof(t_philo));
	share->philo[iter].stdout_lock = &share->stdout_lock;
	share->philo[iter].dead_status = &share->dead_status;
	share->philo[iter].dead_lock = &share->dead_lock;
	share->philo[iter].shut_up_lock = &share->shut_up_lock;
	share->philo[iter].shut_up = &share->shut_up;
	share->philo[iter].nb_max = nb;
	share->philo[iter].time_to_die = ft_atoi(share->argv[2]);
	share->philo[iter].time_to_eat = ft_atoi(share->argv[3]);
	share->philo[iter].time_to_sleep = ft_atoi(share->argv[4]);
	if (share->argc == 6)
		share->philo[iter].must_eat = ft_atoi(share->argv[5]);
	else
		share->philo[iter].must_eat = -1;
	return (true);
}

bool	init_shared(t_shared *share, int nb_max_philo, int argc, char **argv)
{
	int	iter;

	iter = 0;
	share->philo = calloc(nb_max_philo, sizeof(t_philo));
	share->argc = argc;
	share->argv = argv;
	if (!share->philo)
		return (mod_perror(EALLOC));
	share->dead_status = false;
	while (iter < nb_max_philo)
	{
		init_philo(share, iter, nb_max_philo);
		iter++;
	}
	return (true);
}

bool	parsing(int argc, char **argv, t_shared *shared)
{
	int	i;

	i = 0;
	memset(shared, 0, sizeof(t_shared));
	while (i < argc - 1)
	{
		if (string_isdigit(argv[i + 1]))
			return (false);
		i++;
	}
	if (!init_shared(shared, ft_atoi(argv[1]), argc, argv))
		return (false);
	if (!forks_attribution(shared))
		return (false);
	return (true);
}
