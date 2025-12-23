/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threading.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nclavel <your@email.com>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 16:19:42 by nclavel           #+#    #+#             */
/*   Updated: 2025/12/23 16:40:09 by nclavel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "incs/philosophers.h"
/*
void  kill_philosophers(t_philo philo, int i)
{
	while (i >= 0)
	{
		
	}
}
*/
int	create_philosophers(t_philo philo)
{
	int	i;
	int	status;

	i = 0;
	status = 0;
	philo->thread_arr = malloc(sizeof(pthread_t) * philo->parameter[0]);
	if (!philo->thread_arr)
		return (mod_perror("[!] Failed to allocate memory !"));
	while (i < philo->parameter[0])
	{
		if (pthread_create(philo->thread_arr[i], NULL, NULL, NULL) != 0)
		{
			return (mod_perror("[!] Failed to create a philosopher"));
		}
		i++;
	}
	return (0);
}
