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

bool  check_die(t_philo *philo)
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
	else if (philo->since_meal && get_mstime() - philo->since_meal >= philo->time_to_die)
	{
		pthread_mutex_lock(&*philo->dead_lock);
		*philo->dead_status = true;	
		safe_print(philo, "died", philo->number);
		*philo->shut_up = true;
		printf("Take %ld ms\n", get_mstime() - philo->since_meal);
		pthread_mutex_unlock(&*philo->dead_lock);
		return (true);
	}
	return (false);
}

bool  choose_fork(t_philo *philo)
{
	int mod;

	mod = philo->number % 2;
	if (check_die(philo))
		return (false);
	if (!mod)
		pthread_mutex_lock(&*philo->fork_r);
	else 
		pthread_mutex_lock(&philo->fork_l);
	if (check_die(philo))
	{
		if (!mod)
			pthread_mutex_unlock(&*philo->fork_r);
		else 
			pthread_mutex_unlock(&philo->fork_l);
		return (false);
	}
	safe_print(philo, "has taken a fork", philo->number);
	if (!mod)
		pthread_mutex_lock(&philo->fork_l);
	else 
		pthread_mutex_lock(&*philo->fork_r);
	if (check_die(philo))
	{
		pthread_mutex_unlock(&*philo->fork_r);
		pthread_mutex_unlock(&philo->fork_l);
		return (false);
	}
	safe_print(philo, "has taken a fork", philo->number);
	return (true);
}

void  philo_eat(t_philo *philo)
{
	if (!choose_fork(philo))
		return ;
	philo->since_meal = get_mstime();
	safe_print(philo, "is eating", philo->number);
	usleep(philo->time_to_eat * 1000);
	philo->think_status = true;
	philo->eat_status = false;
	philo->meal_eated++;
	pthread_mutex_unlock(&*philo->fork_r);
	pthread_mutex_unlock(&philo->fork_l);
	return ;
}

void  philo_sleeping(t_philo *philo)
{
	if (check_die(philo))
		return ;
	safe_print(philo, "is sleeping", philo->number);
	usleep(philo->time_to_sleep * 1000);
	philo->eat_status = true;
	philo->sleep_status = false;
}

void  philo_thinking(t_philo *philo)
{
	if (check_die(philo))
		return ;
	safe_print(philo, "is thinking", philo->number);
	philo->sleep_status = true;
	philo->think_status = false;
}

void  *philosophers(void *ptr_philo)
{
	t_philo	*philo;

	philo = (t_philo *)ptr_philo;
	philo->eat_status = true;
	while (!check_die(philo))
	{
		if (philo->eat_status)
			philo_eat(philo);
		else if (philo->think_status)
			philo_thinking(philo);
		else if (philo->sleep_status)
			philo_sleeping(philo);
//		usleep(100);
	}
	return (NULL);
}

