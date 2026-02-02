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

static bool	forks_attribution(t_shared *share, int max)
{
	int	i;

	i = 0;
	
	share->fork_arr = calloc(max, sizeof(pthread_mutex_t))
	while (i < max)
		pthread_mutex_init(&share->fork_arr[i++], NULL);
	i = 0;
	while (i < max)
	{
		if (i == 0)
		{
			share->philo[i].fork_r = &share->fork_arr[0];
			share->philo[i].fork_l = &share->fork_arr[max - 1];
		}
		else
		{
			share->philo[i].fork_r = &share->fork_arr[i];
			share->philo[i].fork_l = &share->fork_arr[i - 1];
		}
		i++;
	}
	return (true);
}

static bool	init_philo(t_shared *share, int iter, int argc, char **argv)
{
	memset(&share->philo[iter], 0, sizeof(t_philo));
	share->philo[iter].stdout_lock = &share->stdout_lock;
	share->philo[iter].dead_status = &share->dead_status;
	share->philo[iter].dead_lock = &share->dead_lock;
	share->philo[iter].shut_up_lock = &share->shut_up_lock;
	share->philo[iter].shut_up = &share->shut_up;
	share->philo[iter].nb_max = ft_atoi(argv[1]);
	share->philo[iter].time_to_die = ft_atoi(argv[2]);
	share->philo[iter].time_to_eat = ft_atoi(argv[3]);
	share->philo[iter].time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		share->philo[iter].must_eat = ft_atoi(argv[5]);
	else
		share->philo[iter].must_eat = -1;
	return (true);
}

static bool	init_shared(t_shared *share, int nb_max_philo, int argc, char **argv)
{
	int iter; 

	iter = 0;
	share->philo = calloc(nb_max_philo, sizeof(t_philo));
	if (!share->philo)
		return (mod_perror(EALLOC));
	share->dead_status = false;
	while (iter < nb_max_philo)
	{
		init_philo(share, iter, argc, argv);
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
	if (!forks_attribution(shared, ft_atoi(argv[1])))
		return (false);
	return (true);
}
