/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nclavel <nclavel@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 00:53:06 by nclavel           #+#    #+#             */
/*   Updated: 2026/01/07 00:53:27 by nclavel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "incs/philosophers.h"

bool  init_philo(t_shared *shared)
{
	int	i;

	i = 0;
	printf("[DEBUG] nb_philo : %d\n", shared->philo[0].number_philosophers);
	if (pthread_mutex_init(&shared->stdout_lock, NULL))
		return (failed_exit(shared, 0), mod_perror(EMTX));
	if (pthread_mutex_init(&shared->dead_lock, NULL))
		return (failed_exit(shared, 0), mod_perror(EMTX));
	while (i < shared->philo[0].number_philosophers)
	{
		shared->philo[i].number = i + 1;
		if (shared->philo[i].number == 1)
		{
			shared->philo[i].fork_l = &shared->philo[shared->philo[i].number_philosophers - 1].fork_r;
			shared->philo[i].fork_r = &shared->philo[shared->philo[i].]
		}
		printf("[!] Create philosophers %d\n", i + 1);
		if (pthread_create(&shared->philo[i].id, NULL, &philosophers, &shared->philo[i]))
		{
			failed_exit(shared, i);
			return (mod_perror(ETHREAD));
		}
		i++;
	}
	
	return (true);
}

int main(int argc, char **argv)
{
	t_shared	shared;

	if (argc != 5 && argc != 6)
		return (mod_perror(EARGNB));
	if (!parsing(argc, argv, &shared))
		return (1);
	if (!init_philo(&shared))
		return (1);
	succes_exit(&shared);
	return (0);
}
