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

void	*reaper(void *ptr_philo)
{
	t_philo	*philo;

	philo = (t_philo *)ptr_philo;
	while (!*philo->dead_status)
	{
		pthread_mutex_lock(&philo->mtx_last_meal);
		if (philo->meal_eated == philo->must_eat)
			*philo->dead_status = true;
		else if (get_mstime() - philo->since_meal > philo->time_to_die)
		{
			pthread_mutex_lock(&*philo->dead_lock);
			*philo->dead_status = true;
			pthread_mutex_unlock(&*philo->dead_lock);
			safe_print(philo, "died", philo->number);
			*philo->shut_up = true;
			printf("Take %ld ms\n", get_mstime()
				- philo->since_meal);
		}
		pthread_mutex_unlock(&philo->mtx_last_meal);
	}
	return (NULL);
}
