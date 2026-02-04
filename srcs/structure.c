/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structure.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nclavel <nclavel@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/04 08:17:04 by nclavel           #+#    #+#             */
/*   Updated: 2026/02/04 08:19:13 by nclavel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "incs/philosophers.h"

bool	init_data(t_data **data, int argc, char **argv)
{
	*data = ft_calloc(1, sizeof(t_data));
	if (!*data)
		return (false);
	(*data)->nb_max = ft_atoi(argv[1]);
	(*data)->time_to_die = ft_atoi(argv[2]);
	(*data)->time_to_eat = ft_atoi(argv[3]);
	(*data)->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		(*data)->must_eat = ft_atoi(argv[5]);
	else
		(*data)->must_eat = -1;
	return (true);
}

void	init_philo(t_shared *share, int iter)
{
	memset(&share->philo[iter], 0, sizeof(t_philo));
	share->philo[iter].stdout_lock = &share->stdout_lock;
	share->philo[iter].dead_status = &share->dead_status;
	share->philo[iter].dead_lock = &share->dead_lock;
	share->philo[iter].shut_up_lock = &share->shut_up_lock;
	share->philo[iter].shut_up = &share->shut_up;
	share->philo[iter].nb_max = &share->data->nb_max;
	share->philo[iter].time_to_die = &share->data->time_to_die;
	share->philo[iter].time_to_eat = &share->data->time_to_eat;
	share->philo[iter].time_to_sleep = &share->data->time_to_sleep;
	share->philo[iter].must_eat = &share->data->must_eat;
}

bool	init_shared(t_shared *share, int nb_max_philo, int argc, char **argv)
{
	int	i;

	i = 0;
	if (!init_data(&share->data, argc, argv))
		return (false);
	share->philo = ft_calloc(nb_max_philo, sizeof(t_philo));
	if (!share->philo)
		return (mod_perror(EALLOC));
	while (i < nb_max_philo)
	{
		init_philo(share, i);
		i++;
	}
	return (true);
}
