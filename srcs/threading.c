/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threading.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nclavel <nclavel@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 20:16:41 by nclavel           #+#    #+#             */
/*   Updated: 2026/01/16 11:51:07 by nclavel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "incs/philosophers.h"

// https://nafuka11.github.io/philosophers-visualizer/

void	case_one(t_philo *philo)
{
	safe_print(philo, "died", philo->number);
	*philo->dead_status = true;
}

bool	check_die(t_philo *philo)
{
	if (*philo->dead_status)
		return (true);
	else if (philo->meal_eated == philo->must_eat)
	{
		pthread_mutex_lock(&*philo->dead_lock);
		*philo->dead_status = true;
		pthread_mutex_unlock(&*philo->dead_lock);
		return (true);
	}
	else if (get_mstime() - philo->since_meal >= philo->time_to_die)
	{
		pthread_mutex_lock(&*philo->dead_lock);
		*philo->shut_up = true;
		*philo->dead_status = true;
		safe_print(philo, "died", philo->number);
		printf("Take %ld ms\n", get_mstime() - philo->since_meal);
		pthread_mutex_unlock(&*philo->dead_lock);
		return (true);
	}
	return (false);
}

void	*philosophers(void *ptr_philo)
{
	t_philo	*philo;

	philo = (t_philo *)ptr_philo;
	philo->eat_status = true;
	if (philo->number & 1)
		usleep(1000);
	if (philo->nb_max == 1)
		case_one(philo);
	philo->since_meal = get_mstime();
	while (!check_die(philo))
	{
		if (philo->eat_status)
			philo_eat(philo);
		else if (philo->think_status)
			philo_thinking(philo);
		else if (philo->sleep_status)
			philo_sleeping(philo);
		usleep(100);
	}
	return (NULL);
}
