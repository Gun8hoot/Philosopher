/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nclavel <nclavel@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/15 22:26:39 by nclavel           #+#    #+#             */
/*   Updated: 2026/02/15 22:53:26 by nclavel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "incs/philosophers.h"

static void	clean_mutex(t_shared *shared)
{
	int32_t	i;

	i = 0;
	if (shared->philo)
	{
		while (i < shared->data->nb_max)
		{
			if (shared->philo[i].mtx_status_info)
				pthread_mutex_destroy(&shared->philo[i++].info);
		}
	}
	if (shared->mtx_status_stdout)
		pthread_mutex_destroy(&shared->stdout_lock);
	if (shared->mtx_status_deadlock)
		pthread_mutex_destroy(&shared->dead_lock);
	if (shared->mtx_status_shutup)
		pthread_mutex_destroy(&shared->shut_up_lock);
}

static void	clean_structure(t_shared *shared)
{
	clean_mutex(shared);
	if (shared->fork_arr)
		free(shared->fork_arr);
	if (shared->data)
		free(shared->data);
	if (shared->philo)
		free(shared->philo);
}

void	ft_exit(t_shared *shared)
{
	int32_t	i;

	i = 0;
	if (shared->philo)
	{
		while (i < shared->data->nb_max)
		{
			if (shared->philo[i].created)
				pthread_join(shared->philo[i].id, NULL);
			i++;
		}
		if (shared->reaper_created)
			pthread_join(shared->id_reaper, NULL);
	}
	clean_structure(shared);
}
