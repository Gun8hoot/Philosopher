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

static bool	check_must_eat(t_shared *share)
{
	int32_t	i;
	int32_t	counter;

	i = 0;
	counter = 0;
	while (share->data->must_eat != -1 && i < share->data->nb_max)
	{
		if (share->philo[i].meal_eated >= share->data->must_eat)
			counter++;
		i++;
	}
	if (counter == share->data->nb_max)
	{
		share->dead_status = true;
		share->shut_up = true;
		return (false);
	}
	return (true);
}

static bool	check_ttd(t_shared *share)
{
	int32_t	i;

	i = 0;
	while (i < share->data->nb_max)
	{
		if (get_mstime()
			- share->philo[i].since_meal >= share->data->time_to_die)
		{
			pthread_mutex_lock(&share->dead_lock);
			share->dead_status = true;
			pthread_mutex_unlock(&share->dead_lock);
			safe_print(&share->philo[i], "died", share->philo[i].number);
			pthread_mutex_lock(&share->shut_up_lock);
			share->shut_up = true;
			pthread_mutex_unlock(&share->shut_up_lock);
			return (false);
		}
		i++;
	}
	return (true);
}

void	*reaper(void *ptr_share)
{
	t_shared	*share;

	share = (t_shared *)ptr_share;
	usleep(1000);
	while (!share->dead_status)
	{
		if (!check_must_eat(share))
			break ;
		if (!check_ttd(share))
			break ;
		usleep(1000);
	}
	return (NULL);
}
