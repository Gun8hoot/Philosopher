/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nclavel <nclavel@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 18:25:14 by nclavel           #+#    #+#             */
/*   Updated: 2026/01/16 08:36:38 by nclavel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H


// --- INCLUDES ---
# include <pthread.h>
# include <unistd.h>
# include <stdbool.h>
# include <limits.h>
# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <sys/time.h>


// --- ERROR MSG ---
# define EALLOC "\e[0;31m[!] Failed to allocate memory\e[0m"
# define ETHREAD "\e[0;31m[!] Failed to created every theads\e[0m"
# define EOOB "\e[0;31m[!] Number go out of bound (max 32bit s_int)\e[0m"
# define EALNUM "\e[0;31m[!] Non-number character detected\e[0m"
# define EARGNB "\e[0;31m[!] Not enought arguments\e[0m" 
# define EMTX "\e[0;31m[!] Failed to initialize a mutex\e[0m"


// --- STRUCTURE ---
typedef struct s_philo
{
	struct timeval		tmsp_since;
	pthread_mutex_t		*dead_lock;
	pthread_mutex_t		*stdout_lock;
	pthread_mutex_t		*fork_r;
	pthread_mutex_t		fork_l;
	pthread_t			id;
	int					nb_max;
	size_t				time_to_die;
	size_t				time_to_eat;
	size_t				time_to_sleep;
	size_t				must_eat;
	size_t				number;
	size_t				since_meal;
	size_t				meal_eated;
	bool				eat_status;
	bool				sleep_status;
	bool				think_status;
	bool				*shut_up;
	bool				*dead_status;
} t_philo;

typedef	struct	s_shared
{
	pthread_mutex_t		stdout_lock;
	pthread_mutex_t		dead_lock;
	bool				shut_up;
	bool				dead_status;

	t_philo				*philo;
} t_shared ;


// --- PROTOTYPES ---
bool	parsing(int argc, char **argv, t_shared *shared);
int		ft_atoi(const char *nptr);
int		ft_atol(char *number);
size_t	ft_strlen(char *number);
int		mod_perror(char *error);
void	succes_exit(t_shared *shared);
void	failed_exit(t_shared *shared, int stopped_at);
void	*philosophers(void *ptr_philo);
size_t	get_mstime(void);
void  safe_print(t_philo *philo, char *str, size_t number);

#endif
