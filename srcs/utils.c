/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nclavel <nclavel@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 20:16:58 by nclavel           #+#    #+#             */
/*   Updated: 2026/01/07 01:31:06 by nclavel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "incs/philosophers.h"

int	mod_perror(char *error)
{
	int	i;

	i = 0;
	while (error[i])
	{
		write(2, &error[i], 1);
		i++;
	}
	write(2, "\n", 1);
	return (1);
}

size_t	get_mstime(void)
{
	struct timeval	time;
	size_t			ms;

	gettimeofday(&time, NULL);
	ms = (size_t)(time.tv_sec * 1000 + time.tv_usec / 1000);
	return (ms);
}

/*
bool  better_usleep(t_philo *philo)
{
  while ()
}
*/

void	safe_print(t_philo *philo, char *str, size_t number)
{
	pthread_mutex_lock(&*philo->stdout_lock);
	if (*philo->shut_up)
	{
		pthread_mutex_unlock(&*philo->stdout_lock);
		return ;
	}
	printf("%ld %ld %s\n", get_mstime() - philo->start_time, number, str);
	pthread_mutex_unlock(&*philo->stdout_lock);
}
