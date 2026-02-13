/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nclavel <nclavel@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 10:23:29 by nclavel           #+#    #+#             */
/*   Updated: 2026/01/19 10:39:45 by nclavel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "incs/philosophers.h"

static bool	choose_fork(t_philo *philo)
{
	pthread_mutex_t *first;
	pthread_mutex_t *second;

	if (philo->fork_r > philo->fork_l)
	{
		first = philo->fork_l;
		second = philo->fork_r;
	}
	else
	{
		first = philo->fork_r;
		second = philo->fork_l;
	}
	pthread_mutex_lock(&*first);
	safe_print(philo, "has taken a fork", philo->number);
	if (check_die(philo))
	{
		pthread_mutex_unlock(&*first);
		return (false);
	}
	pthread_mutex_lock(&*second);
	safe_print(philo, "has taken a fork", philo->number);
	if (check_die(philo))
	{
		pthread_mutex_unlock(&*first);
		pthread_mutex_unlock(&*second);
		return (false);
	}
	return (true);
}

bool	philo_eat(t_philo *philo)
{
	if (!choose_fork(philo))
		return (false);
	safe_print(philo, "is eating", philo->number);
	better_usleep(philo, *philo->time_to_eat);
	pthread_mutex_unlock(&*philo->fork_r);
	pthread_mutex_unlock(&*philo->fork_l);
	pthread_mutex_lock(&philo->info);
	philo->since_meal = get_mstime();
	philo->meal_eated++;
	pthread_mutex_unlock(&philo->info);
	return (true);
}

bool	philo_sleeping(t_philo *philo)
{
	safe_print(philo, "is sleeping", philo->number);
	better_usleep(philo, *philo->time_to_sleep);
	return (true);
}

bool	philo_thinking(t_philo *philo)
{
	safe_print(philo, "is thinking", philo->number);
	better_usleep(philo, 500);
	return (true);
}
