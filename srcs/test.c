/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nclavel <nclavel@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 02:28:51 by nclavel           #+#    #+#             */
/*   Updated: 2026/01/07 02:29:45 by nclavel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "incs/philosophers.h"

size_t	get_mstime(void)
{
	struct timeval	time;
	size_t			ms;

	gettimeofday(&time, NULL);
	ms = (size_t)(time.tv_sec * 1000 + time.tv_usec / 1000);
	return (ms);
}

int	main(int argc, char **argv)
{
	size_t	t1, t2;
	t_philo	philo;

	philo.time_to_die = 1000;
	philo.since_meal = get_mstime();
	usleep(400 * 1000);
	printf("%ld <=> %ld\n", get_mstime() - philo.since_meal, philo.time_to_die);
//	printf("t1 = %ld\nt2 = %ld\nope = %ld\n", t1, t2, t2 - t1);
}
