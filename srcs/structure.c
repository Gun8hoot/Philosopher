/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structure.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nclavel <nclavel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/04 08:17:04 by nclavel           #+#    #+#             */
/*   Updated: 2026/03/18 11:39:24 by nclavel          ###   ########.fr       */
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

void	init_philo(t_shared *shared, int iter)
{
	memset(&shared->philo[iter], 0, sizeof(t_philo));
	pthread_mutex_init(&shared->philo[iter].info, NULL);
	shared->philo[iter].mtx_status_info = true;
	shared->philo[iter].data = &shared->data;
	shared->philo[iter].stdout_lock = &shared->stdout_lock;
	shared->philo[iter].dead_status = &shared->dead_status;
	shared->philo[iter].dead_lock = &shared->dead_lock;
	shared->philo[iter].shut_up_lock = &shared->shut_up_lock;
	shared->philo[iter].shut_up = &shared->shut_up;
	shared->philo[iter].nb_max = &shared->data->nb_max;
	shared->philo[iter].time_to_die = &shared->data->time_to_die;
	shared->philo[iter].time_to_eat = &shared->data->time_to_eat;
	shared->philo[iter].time_to_sleep = &shared->data->time_to_sleep;
	shared->philo[iter].must_eat = &shared->data->must_eat;
}

bool	init_shared(t_shared *shared, int nb_max_philo, int argc, char **argv)
{
	int	i;

	i = 0;
	if (!init_data(&shared->data, argc, argv))
		return (mod_perror(EALLOC), false);
	shared->philo = ft_calloc(nb_max_philo, sizeof(t_philo));
	if (!shared->philo)
		return (mod_perror(EALLOC), false);
	while (i < nb_max_philo)
	{
		init_philo(shared, i);
		i++;
	}
	return (true);
}
