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

static bool	thread_creation(t_shared *shared)
{
	int32_t	start_time;
	int32_t	i;

	i = 0;
	if (pthread_create(&shared->id_reaper, NULL, &reaper, shared))
		return (false);
	start_time = get_mstime();
	while (i < shared->data->nb_max)
	{
		pthread_mutex_init(&shared->philo[i].mtx_last_meal, NULL);
    pthread_mutex_init(&shared->philo[i].mtx_meal_eated, NULL);
		shared->philo[i].number = i + 1;
		shared->philo[i].start_time = start_time;
	  shared->philo[i].since_meal = get_mstime();
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
	pthread_mutex_init(&shared->stdout_lock, NULL);
	pthread_mutex_init(&shared->dead_lock, NULL);
	pthread_mutex_init(&shared->shut_up_lock, NULL);
	if (!thread_creation(shared))
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
