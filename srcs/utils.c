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

void  succes_exit(t_shared *shared)
{
	int	i;

	i = 0;
	if (shared->philo[0].number_philosophers)
	{
		while (i < shared->philo->number_philosophers)
		{
			pthread_join(shared->philo[i].id, NULL);
			i++;
		}
	}
	if (shared->philo)
		free(shared->philo);
}

void  failed_exit(t_shared *shared, int stopped_at)
{
	int	i;
	int j;

	j = 0;
	if (stopped_at)
		i = stopped_at - 1;
	else 
		i = shared->philo->number_philosophers;
	while (j < i)
	{
		pthread_join(shared->philo[j].id, NULL);
		j++;
	}
	if (shared->philo)
		free(shared->philo);
}
