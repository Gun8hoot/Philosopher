/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nclavel <nclavel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 10:23:29 by nclavel           #+#    #+#             */
/*   Updated: 2026/02/17 08:07:10 by nclavel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "incs/philosophers.h"

static bool	choose_fork(t_philo *philo, pthread_mutex_t **first,
		pthread_mutex_t **second)
{
	if (*first > *second)
	{
		*first = philo->fork_r;
		*second = philo->fork_l;
	}
	else
	{
		*first = philo->fork_l;
		*second = philo->fork_r;
	}
	pthread_mutex_lock(*first);
	safe_print(philo, "has taken a fork", philo->number);
	if (check_die(philo))
		return (pthread_mutex_unlock(*first), false);
	pthread_mutex_lock(*second);
	safe_print(philo, "has taken a fork", philo->number);
	if (check_die(philo))
	{
		pthread_mutex_unlock(*first);
		pthread_mutex_unlock(*second);
		return (false);
	}
	return (true);
}

bool	philo_eat(t_philo *philo)
{
	pthread_mutex_t	*first;
	pthread_mutex_t	*second;

	if (!choose_fork(philo, &first, &second))
		return (false);
	safe_print(philo, "is eating", philo->number);
	better_usleep(philo, *philo->time_to_eat);
	pthread_mutex_unlock(&*philo->fork_l);
	pthread_mutex_unlock(&*philo->fork_r);
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
	better_usleep(philo, 1);
	return (true);
}
