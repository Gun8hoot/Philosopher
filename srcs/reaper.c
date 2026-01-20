/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nclavel <nclavel@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 10:59:21 by nclavel           #+#    #+#             */
/*   Updated: 2026/01/19 11:12:48 by nclavel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "incs/philosophers.h"

bool  do_action(t_shared *share, size_t nb)
{
	if (share->philo[nb].is_eating
		|| share->philo[nb].is_sleeping
		|| share->philo[nb].is_thinking)
			return (true);
	return (false);
}

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
		while (!share->dead_status && i < share->data.nb_max)
		{
			if (share->philo[i].meal_eated == share->data.must_eat)
				share->dead_status = true;
			else if (!do_action(share, i) && get_mstime()
				- share->philo[i].since_meal >= share->data.time_to_die)
			{
				share->shut_up = true;
				share->dead_status = true;
				printf("%ld %ld died\n", get_mstime(), share->philo[i].number);
				safe_print(&share->philo[i], "died", share->philo[i].number);
				printf("Take %ld ms\n", get_mstime()
					- share->philo[i].since_meal);
			}
			i++;
		}
	}
	return (NULL);
}
