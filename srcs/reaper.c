/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reaper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nclavel <nclavel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 10:59:21 by nclavel           #+#    #+#             */
/*   Updated: 2026/02/17 07:56:51 by nclavel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "incs/philosophers.h"

static void	is_dead(t_philo philo)
{
	pthread_mutex_lock(&*philo.stdout_lock);
	*philo.shut_up = true;
	pthread_mutex_unlock(&*philo.stdout_lock);
	pthread_mutex_lock(&*philo.dead_lock);
	*philo.dead_status = true;
	pthread_mutex_unlock(&*philo.dead_lock);
}

static bool	check_must_eat(t_shared *shared)
{
	int32_t	i;
	int32_t	counter;

	i = 0;
	counter = 0;
	pthread_mutex_lock(&shared->dead_lock);
	if (shared->data->must_eat != -1 && !shared->dead_status)
	{
		pthread_mutex_unlock(&shared->dead_lock);
		while (i < shared->data->nb_max)
		{
			pthread_mutex_lock(&shared->philo[i].info);
			if (shared->philo[i].meal_eated >= shared->data->must_eat)
				counter++;
			pthread_mutex_unlock(&shared->philo[i].info);
			i++;
		}
		if (counter == shared->data->nb_max)
			return (is_dead(shared->philo[0]), false);
	}
	return (true);
}

static bool	check_ttd(t_shared *shared)
{
	int32_t	i;

	i = 0;
	while (i < shared->data->nb_max)
	{
		pthread_mutex_lock(&shared->philo[i].info);
		if (shared->philo[i].since_meal == 0)
		{
			pthread_mutex_unlock(&shared->philo[i].info);
			i++;
			continue ;
		}
		if (get_mstime()
			- shared->philo[i].since_meal >= shared->data->time_to_die)
		{
			is_dead(shared->philo[i]);
			printf("%d %d died\n", get_mstime() - shared->philo[i].start_time,
				shared->philo[i].number);
			pthread_mutex_unlock(&shared->philo[i].info);
			return (false);
		}
		pthread_mutex_unlock(&shared->philo[i].info);
		i++;
	}
	return (true);
}

void	*reaper(void *ptr_share)
{
	t_shared	*shared;

	shared = (t_shared *)ptr_share;
	usleep(500);
	while (1)
	{
		if (check_die(&shared->philo[0]))
			break ;
		if (!check_must_eat(shared))
			break ;
		if (!check_ttd(shared))
			break ;
		usleep(1000);
	}
	return (NULL);
}
