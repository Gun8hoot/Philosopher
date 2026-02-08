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
	if (check_die(philo))
		return (false);
	if (philo->number & 1)
		pthread_mutex_lock(&*philo->fork_l);
	else 
		pthread_mutex_lock(&*philo->fork_r);
	safe_print(philo, "has taken a fork", philo->number);
	if (philo->number & 1)
		pthread_mutex_lock(&*philo->fork_r);
	else 
		pthread_mutex_lock(&*philo->fork_l);
	return (safe_print(philo, "has taken a fork", philo->number), true);
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
	return (true);
}
