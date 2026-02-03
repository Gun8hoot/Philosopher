/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reaper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nclavel <nclavel@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 10:59:21 by nclavel           #+#    #+#             */
/*   Updated: 2026/01/31 10:40:13 by nclavel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "incs/philosophers.h"

static bool  check_must_eat(t_shared *share)
{
  size_t i;
  size_t counter;

  i = 0;
  counter = 0;
  while (share->philo[i].must_eat != -1 && i < share->philo[0].nb_max)
  {
    if (share->philo[i].meal_eated >= share->philo[i].must_eat)
    {  
      printf("%d >= %d\n", share->philo[i].meal_eated, share->philo[i].must_eat);
      counter++;
    }
    i++;
  }
  if (counter == share->philo[0].nb_max)
  {
    
    printf("enter heer\n");
    share->dead_status = true;
    share->shut_up = true;
    return (false);
  }
  return (true);
}

void	*reaper(void *ptr_share)
{
	t_shared	*share;
  size_t i = 0;

	share = (t_shared *)ptr_share;
  usleep(1000);
	while (!share->dead_status)
	{
    i = 0;
    if (!check_must_eat(share))
      break ;
    while (i < share->philo[0].nb_max)
    {
      if (get_mstime() - share->philo[i].since_meal > share->philo[i].time_to_die)
      {
        pthread_mutex_lock(&share->shut_up_lock);
        share->shut_up = true;
        pthread_mutex_unlock(&share->shut_up_lock);
        pthread_mutex_lock(&share->dead_lock);
        share->dead_status = true;
        pthread_mutex_unlock(&share->dead_lock);
        safe_print(&share->philo[i], "died", share->philo[i].number);
        break ;
      }
      i++;
    }
    usleep(100);
	}
	return (NULL);
}
