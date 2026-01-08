/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threading.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nclavel <nclavel@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 20:16:41 by nclavel           #+#    #+#             */
/*   Updated: 2026/01/07 02:54:07 by nclavel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "incs/philosophers.h"

//usleep(philo->time_to_sleep * 1000)

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
		printf("%ld %ld is eating\n", tmps, philo->number);
		usleep(philo->time_to_eat * 1000);
		philo->since_meal = get_mstime();
	}
	else if (type == 't')
		printf("%ld %ld is thinking\n", tmps, philo->number);
	else if (type == 's')
	{
		printf("%ld %ld is sleeping\n", tmps, philo->number);
		usleep(philo->time_to_sleep * 1000);
	}
}

void  check_philosopher(t_philo *philo)
{
	size_t	tmps;

	tmps = get_mstime();
	if (tmps - philo->since_meal >= philo->time_to_die)
	{
		printf("[DEBUG] thread %ld dead ope = %ld >= %ld\n", philo->number, philo->since_meal - tmps, philo->time_to_die);
		action_philo(philo, 'd', tmps);
	}
	else if (philo->must_eat == philo->meal_eated)
		action_philo(philo, 'e', tmps);

}

void  *philosophers(void *ptr_philo)
{
	t_philo	*philo;

	philo = (t_philo *)ptr_philo;
	while (!*philo->dead_status)
	{
		check_philosopher(philo);
		if (philo->number == 10)
		{
			pthread_mutex_lock(&*philo->dead_lock);
			*philo->dead_status = 1;
			pthread_mutex_unlock(&*philo->dead_lock);
		}
	}
	return (NULL);
}

