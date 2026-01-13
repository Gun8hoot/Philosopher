/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threading.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nclavel <nclavel@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 20:16:41 by nclavel           #+#    #+#             */
/*   Updated: 2026/01/13 08:32:02 by nclavel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "incs/philosophers.h"

void  action_philo(t_philo *philo, char type, size_t tmps)
{
	if (type == 'd' && !*philo->dead_status)
	{	
		pthread_mutex_lock(&*philo->dead_lock);
		*philo->dead_status = true;
		printf("%ld %ld died\n", tmps, philo->number);
		pthread_mutex_unlock(&*philo->dead_lock);
	}
	else if (type == 'e')
	{
		pthread_mutex_lock(&*philo->fork_r);
		pthread_mutex_lock(&philo->fork_l);
		printf("%ld %ld is eating\n", tmps, philo->number);
		usleep(philo->time_to_eat * 1000);
		philo->since_meal = get_mstime();
		philo->think_status = true;
		philo->eat_status = false;
		pthread_mutex_unlock(&*philo->fork_r);
		pthread_mutex_unlock(&philo->fork_l);
	}
	else if (type == 't')
	{
		printf("%ld %ld is thinking\n", tmps, philo->number);
		philo->sleep_status = true;
		philo->think_status = false;
	}
	else if (type == 's')
	{
		printf("%ld %ld is sleeping\n", tmps, philo->number);
		usleep(philo->time_to_sleep * 1000);
		philo->eat_status = true;
		philo->sleep_status = false;
	}
}

void  *philosophers(void *ptr_philo)
{
	t_philo	*philo;
	size_t	tmps;

	philo = (t_philo *)ptr_philo;
	philo->eat_status = true;
	while (!*philo->dead_status)
	{
		tmps = get_mstime();
		if (philo->since_meal != 0 && tmps - philo->since_meal >= philo->time_to_die)
			action_philo(philo, 'd', tmps);
		else if (philo->eat_status)
			action_philo(philo, 'e', tmps);
		else if (philo->think_status)
			action_philo(philo, 't', tmps);
		else if (philo->sleep_status)
			action_philo(philo, 's', tmps);
	}
	return (NULL);
}

