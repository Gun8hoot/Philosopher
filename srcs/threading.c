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
	usleep(*philo->time_to_die * 1000);
	safe_print(philo, "died", philo->number);
	*philo->dead_status = true;
}

bool	check_die(t_philo *philo)
{
	pthread_mutex_lock(&*philo->dead_lock);
	if (*philo->dead_status)
		return (pthread_mutex_unlock(&*philo->dead_lock), true);
	return (pthread_mutex_unlock(&*philo->dead_lock), false);
}

void	*philosophers(void *ptr_philo)
{
	t_philo	*philo;

	philo = (t_philo *)ptr_philo;
	if (philo->number % 2)
		better_usleep(philo, 1000);
	if (*philo->nb_max == 1)
		case_one(philo);
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
