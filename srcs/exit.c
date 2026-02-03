
#include "incs/philosophers.h"

void	succes_exit(t_shared *shared)
{
	size_t	i;

	i = 0;
	if (shared->philo[0].nb_max)
	{
		while (i < shared->philo[0].nb_max)
		{
			pthread_join(shared->philo[i].id, NULL);
			i++;
		}
	}
  pthread_join(shared->id_reaper, NULL);
	if (shared->philo)
		free(shared->philo);
  i = 0;
//  while (i < )
//    free(shared->fork_arr[i++]);
	pthread_mutex_destroy(&shared->stdout_lock);
	pthread_mutex_destroy(&shared->shut_up_lock);
	pthread_mutex_destroy(&shared->dead_lock);
}

void	failed_exit(t_shared *shared, int stopped_at)
{
	int	i;
	int	j;

	j = 0;
	if (stopped_at)
		i = stopped_at - 1;
	else
		i = shared->philo[0].nb_max;
	while (j < i)
	{
		pthread_join(shared->philo[j].id, NULL);
		j++;
	}
	if (shared->philo)
		free(shared->philo);
	j = 0;
	while (j < i)
	{
		pthread_mutex_destroy(&*shared->philo[j].fork_l);
		j++;
	}
}
