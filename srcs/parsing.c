/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nclavel <nclavel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 20:16:37 by nclavel           #+#    #+#             */
/*   Updated: 2026/02/15 22:19:52 by nclavel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "incs/philosophers.h"

static bool	forks_attribution(t_shared *shared, int max)
{
	int	i;

	i = 0;
	shared->fork_arr = ft_calloc(max, sizeof(pthread_mutex_t));
	if (!shared->fork_arr)
		return (mod_perror(EALLOC), false);
	while (i < max)
	{
		pthread_mutex_init(&shared->fork_arr[i], NULL);
		if (i == max - 1)
		{
			shared->philo[i].fork_l = &shared->fork_arr[0];
			shared->philo[i].fork_r = &shared->fork_arr[i];
		}
		else
		{
			shared->philo[i].fork_l = &shared->fork_arr[i + 1];
			shared->philo[i].fork_r = &shared->fork_arr[i];
		}
		i++;
	}
	return (true);
}

static bool	check_number_philosophers(int i, char **argv)
{
	if (i == 1)
	{
		if (ft_atoi(argv[i]) == 0)
			return (mod_perror(EZERO), false);
	}
	return (true);
}

static bool	check_overflow(char *number)
{
	if (ft_strlen(number) > 10 || (ft_atol(number) < 0
			|| ft_atol(number) > INT_MAX))
		return (mod_perror(EOOB));
	return (0);
}

bool	parsing(int argc, char **argv, t_shared *shared)
{
	int	i;

	i = 0;
	memset(shared, 0, sizeof(t_shared));
	while (i < argc - 1)
	{
		if (string_isdigit(argv[i + 1]) || check_overflow(argv[i + 1]))
			return (false);
		if (!check_number_philosophers(i + 1, argv))
			return (false);
		i++;
	}
	if (!init_shared(shared, ft_atoi(argv[1]), argc, argv))
		return (false);
	if (!forks_attribution(shared, ft_atoi(argv[1])))
		return (false);
	return (true);
}
