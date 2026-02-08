/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reaper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nclavel <nclavel@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 10:59:21 by nclavel           #+#    #+#             */
/*   Updated: 2026/01/31 10:40:13 by nclavel          ###   ########.fr       */
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

static bool	check_must_eat(t_shared *share)
{
	int32_t	i;
	int32_t	counter;

	i = 0;
	counter = 0;
	if (share->data->must_eat != -1 && !share->dead_status)
	{
		while (i < share->data->nb_max)
		{
			if (share->philo[i].meal_eated >= share->data->must_eat)
				counter++;
			i++;
		}
		if (counter == share->data->nb_max)
			return (is_dead(share->philo[i]), false);
	}
	return (true);
}

static bool	check_ttd(t_shared *share)
{
	int32_t	i;

	i = 0;
	while (i < share->data->nb_max)
	{
		pthread_mutex_lock(&share->philo[i].info);
		if (share->philo[i].since_meal == 0)
		{
			i++;
			pthread_mutex_unlock(&share->philo[i].info);
			continue ;
		}
		if (get_mstime()
			- share->philo[i].since_meal >= share->data->time_to_die)
		{
			is_dead(share->philo[i]);
			printf("%d %d died\n", get_mstime() - share->philo[i].start_time, share->philo[i].number);
			pthread_mutex_unlock(&share->philo[i].info);
			return (false);
		}
		pthread_mutex_unlock(&share->philo[i].info);
		i++;
	}
	return (true);
}

void	*reaper(void *ptr_share)
{
	t_shared	*share;

	share = (t_shared *)ptr_share;
	while (!share->dead_status)
	{
		if (!check_must_eat(share))
			break ;
		if (!check_ttd(share))
			break ;
		usleep(500);
	}
	printf("REAPER is gone\n");
	return (NULL);
}
