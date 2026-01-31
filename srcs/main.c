/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nclavel <nclavel@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 00:53:06 by nclavel           #+#    #+#             */
/*   Updated: 2026/01/20 09:06:30 by nclavel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "incs/philosophers.h"

// https://nafuka11.github.io/philosophers-visualizer/

static bool  thread_creation(t_shared *shared, size_t start_time)
{
	size_t i;

	i = 0;
	while (i < shared->philo[0].nb_max)
	{
		pthread_mutex_init(&shared->philo[i].mtx_last_meal, NULL);
		shared->philo[i].number = i + 1;
		shared->philo[i].start_time = start_time;
		
		if (pthread_create(&shared->philo[i].id, NULL, &philosophers,
				&shared->philo[i]))
		{
			failed_exit(shared, i);
			return (mod_perror(ETHREAD), false);
		}
		i++;
	}
	return (true);
}

static bool	init(t_shared *shared)
{
	size_t	start_time;

	pthread_mutex_init(&shared->stdout_lock, NULL);
	pthread_mutex_init(&shared->dead_lock, NULL);
	pthread_mutex_init(&shared->shut_up_lock, NULL);

	if (pthread_create(&shared->id_reaper, NULL, &reaper, shared))
	{
		failed_exit(shared, 1);
		return (mod_perror(ETHREAD));
	}
	
	start_time = get_mstime();
	if (!thread_creation(shared, start_time))
		return (false);
	return (true);
}

int	main(int argc, char **argv)
{
	t_shared	shared;

	if (argc != 5 && argc != 6)
		return (mod_perror(EARGNB));
	if (!parsing(argc, argv, &shared))
		return (1);
	if (!init(&shared))
		return (1);
	succes_exit(&shared);
	return (0);
}
