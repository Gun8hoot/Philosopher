/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nclavel <nclavel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 00:53:06 by nclavel           #+#    #+#             */
/*   Updated: 2026/02/13 09:16:03 by nclavel          ###   ########.fr       */
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
	shared->reaper_created = true;
	start_time = get_mstime();
	while (i < shared->data->nb_max)
	{
		pthread_mutex_lock(&shared->philo[i].info);
		shared->philo[i].number = i + 1;
		shared->philo[i].start_time = start_time;
		pthread_mutex_unlock(&shared->philo[i].info);
		if (pthread_create(&shared->philo[i].id, NULL, &philosophers,
				&shared->philo[i]))
		{
			failed_exit(shared, i);
			return (mod_perror(ETHREAD), false);
		}
		shared->philo[i].created = true;
		i++;
	}
	return (true);
}

static bool	init(t_shared *shared)
{
	pthread_mutex_init(&shared->stdout_lock, NULL);
	shared->mtx_status_stdout = true;
	pthread_mutex_init(&shared->dead_lock, NULL);
	shared->mtx_status_deadlock = true;
	pthread_mutex_init(&shared->shut_up_lock, NULL);
	shared->mtx_status_shutup = true;
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
		return (ft_exit(&shared), EXIT_FAILURE);
	if (!init(&shared))
		return (ft_exit(&shared), EXIT_FAILURE);
	ft_exit(&shared);
	return (EXIT_SUCCESS);
}
