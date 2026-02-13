
#include "incs/philosophers.h"
/*
void  free_struct(t_shared *share)
{
	int i;
	
	if (share->data)
		free(share->data);
	if (share->philo)
	{
		i = 0;
		while ()
		{
			if (share->philo[i].mtx_last_meal)
				pthread_mutex_destroy(share->philo[i].mtx_last_meal);
			if (share->philo[i].mtx_meal_eated)
				pthread_mutex_destroy(share->philo[i].mtx_meal_eated);
			free(share->philo[i]);
			i++;
		}
	}
	if (share)
	{
		if (share->fork_arr)
			free(share->fork_arr);
	}
}
*/
void	succes_exit(t_shared *shared)
{
	int32_t	i;

	i = 0;
	if (shared->data->nb_max)
	{
		while (i < shared->data->nb_max)
		{
			pthread_join(shared->philo[i].id, NULL);
			i++;
		}
	}
	pthread_join(shared->id_reaper, NULL);
	if (shared->philo)
		free(shared->philo);
	while (i < shared->data->nb_max)
		pthread_mutex_destroy(&shared->fork_arr[i++]);
	if (shared->data)
		free(shared->data);
	if (shared->fork_arr)
		free(shared->fork_arr);
	pthread_mutex_destroy(&shared->stdout_lock);
	pthread_mutex_destroy(&shared->shut_up_lock);
	pthread_mutex_destroy(&shared->dead_lock);
}

void	failed_exit(t_shared *shared, int stopped_at)
{
	int32_t	i;
	int32_t	j;

	j = 0;
	if (stopped_at)
		i = stopped_at - 1;
	else
		i = shared->data->nb_max;
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
