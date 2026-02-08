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

int32_t	get_mstime(void)
{
	struct timeval	time;
	int32_t			ms;

	gettimeofday(&time, NULL);
	ms = (int32_t)(time.tv_sec * 1000 + time.tv_usec / 1000);
	return (ms);
}

void	better_usleep(t_philo *philo, int32_t time)
{
	int32_t	start_time;
	int32_t	elapsed;

	start_time = get_mstime();
	while (1)
	{
		if (check_die(philo))
			break ;
		elapsed = get_mstime() - start_time;
		if (elapsed >= time)
			break ;
		usleep(3000);
	}
}

void	safe_print(t_philo *philo, char *str, int32_t number)
{
	pthread_mutex_lock(&*philo->stdout_lock);
	if (*philo->shut_up)
	{
		pthread_mutex_unlock(&*philo->stdout_lock);
		return ;
	}
	printf("%d %d %s\n", get_mstime() - philo->start_time, number, str);
	pthread_mutex_unlock(&*philo->stdout_lock);
}
