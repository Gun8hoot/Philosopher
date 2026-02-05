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

static void	case_one(t_philo *philo)
{
	safe_print(philo, "has taken a fork", philo->number);
	safe_print(philo, "has taken a fork", philo->number);
	safe_print(philo, "is eating", philo->number);
	usleep(*philo->time_to_eat * 1000);
	philo_thinking(philo);
	philo_sleeping(philo);
	safe_print(philo, "died", philo->number);
	*philo->shut_up = true;
	*philo->dead_status = true;
}

bool	check_die(t_philo *philo)
{
	pthread_mutex_lock(&*philo->dead_lock);
	if (*philo->dead_status)
		return (pthread_mutex_unlock(&*philo->dead_lock), true);
	pthread_mutex_unlock(&*philo->dead_lock);
	return (false);
}

void	*philosophers(void *ptr_philo)
{
	t_philo	*philo;

	philo = (t_philo *)ptr_philo;
	if (philo->number & 1)
		usleep(400);
	if (*philo->nb_max == 1)
		case_one(philo);
	philo->since_meal = get_mstime();
	while (!check_die(philo))
	{
		if (!philo_eat(philo))
			break ;
		if (!philo_thinking(philo))
			break ;
		if (!philo_sleeping(philo))
			break ;
	}
	printf("Thread %d go out\n", philo->number);
	return (NULL);
}
