/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nclavel <nclavel@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 20:16:37 by nclavel           #+#    #+#             */
/*   Updated: 2026/01/16 08:41:41 by nclavel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "incs/philosophers.h"

static bool	forks_attribution(t_shared *share, int max)
{
	int	i;

	i = 0;
	share->fork_arr = calloc(max, sizeof(pthread_mutex_t));
	if (!share->fork_arr)
		return (false);
	while (i < max)
		pthread_mutex_init(&share->fork_arr[i++], NULL);
	i = 0;
	while (i < max)
	{
		if (i == 0)
		{
			share->philo[i].fork_r = &share->fork_arr[0];
			share->philo[i].fork_l = &share->fork_arr[max - 1];
		}
		else
		{
			share->philo[i].fork_r = &share->fork_arr[i];
			share->philo[i].fork_l = &share->fork_arr[i - 1];
		}
		i++;
	}
	return (true);
}

static bool	check_overflow(char *number)
{
	if (ft_strlen(number) > 10 || (ft_atol(number) < 0
			|| ft_atol(number) > INT_MAX))
		return (mod_perror("[!] Number go out of bound (max 32bit sint) !\n"));
	return (0);
}

bool	parsing(int argc, char **argv, t_shared *shared)
{
	int	i;

	i = 0;
	memset(shared, 0, sizeof(t_shared));
	if (argc != 5 && argc != 6)
		return (false);
	while (i < argc - 1)
	{
		if (string_isdigit(argv[i + 1]) || check_overflow(argv[i + 1]))
			return (false);
		i++;
	}
	if (!init_shared(shared, ft_atoi(argv[1]), argc, argv))
		return (false);
	if (!forks_attribution(shared, ft_atoi(argv[1])))
		return (false);
	return (true);
}
