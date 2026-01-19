/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nclavel <nclavel@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 10:23:29 by nclavel           #+#    #+#             */
/*   Updated: 2026/01/19 10:23:45 by nclavel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "incs/philosophers.h"

bool	choose_fork(t_philo *philo)
{
	if (check_die(philo))
		return (false);
	if ((philo->number & 1) == 0)
		pthread_mutex_lock(&*philo->fork_r);
	else
		pthread_mutex_lock(&philo->fork_l);
	if (check_die(philo))
	{
		if ((philo->number & 1) == 0)
			pthread_mutex_unlock(&*philo->fork_r);
		else
			pthread_mutex_unlock(&philo->fork_l);
		return (false);
	}
	safe_print(philo, "has taken a fork", philo->number);
	if ((philo->number & 1) == 0)
		pthread_mutex_lock(&philo->fork_l);
	else
		pthread_mutex_lock(&*philo->fork_r);
	if (check_die(philo))
	{
		pthread_mutex_unlock(&*philo->fork_r);
		return (pthread_mutex_unlock(&philo->fork_l), false);
	}
	return (safe_print(philo, "has taken a fork", philo->number), true);
}

void	philo_eat(t_philo *philo)
{
	if (!choose_fork(philo))
		return ;
	safe_print(philo, "is eating", philo->number);
	usleep(philo->time_to_eat * 1000);
	philo->since_meal = get_mstime();
	philo->think_status = true;
	philo->eat_status = false;
	philo->meal_eated++;
	pthread_mutex_unlock(&*philo->fork_r);
	pthread_mutex_unlock(&philo->fork_l);
	return ;
}

void	philo_sleeping(t_philo *philo)
{
	safe_print(philo, "is sleeping", philo->number);
	usleep(philo->time_to_sleep * 1000);
	philo->eat_status = true;
	philo->sleep_status = false;
}

void	philo_thinking(t_philo *philo)
{
	safe_print(philo, "is thinking", philo->number);
	usleep(1000);
	philo->sleep_status = true;
	philo->think_status = false;
}
