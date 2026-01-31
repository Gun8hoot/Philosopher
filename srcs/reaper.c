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

void	*reaper(void *ptr_shared)
{
	t_shared	*share;
	size_t		i;

	i = 0;
	share = (t_shared *)ptr_shared;
	usleep(5000);
	while (!share->dead_status)
	{
		i = 0;
		while (!share->dead_status && i < share->philo[0].nb_max)
		{
			pthread_mutex_lock(&share->philo[i].mtx_last_meal);
			if (share->philo[i].ready
				&& share->philo[i].meal_eated == share->philo[i].must_eat)
				share->dead_status = true;
			else if (share->philo[i].ready && get_mstime() - share->philo[i].since_meal > share->philo[i].time_to_die)
			{
				share->shut_up = true;
				share->dead_status = true;
				printf("%ld %ld died\n", get_mstime(), share->philo[i].number);
				safe_print(&share->philo[i], "died", share->philo[i].number);
//				printf("Take %ld ms\n", get_mstime()
//					- share->philo[i].since_meal);
			}
			pthread_mutex_unlock(&share->philo[i].mtx_last_meal);
			i++;
		}
	}
	return (NULL);
}
