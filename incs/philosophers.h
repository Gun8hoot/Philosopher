/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nclavel <nclavel@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 18:25:14 by nclavel           #+#    #+#             */
/*   Updated: 2026/01/31 10:40:08 by nclavel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

// --- INCLUDES ---
# include "incs/prototype.h"
# include <limits.h>
# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

// --- ERROR MSG ---
# define EALLOC "\e[0;31m[!] Failed to allocate memory\e[0m"
# define ETHREAD "\e[0;31m[!] Failed to created every theads\e[0m"
# define EOOB "\e[0;31m[!] Number go out of bound (max 32bit s_int)\e[0m"
# define EALNUM "\e[0;31m[!] Non-number character detected\e[0m"
# define EARGNB "\e[0;31m[!] Not enought arguments\e[0m"
# define EMTX "\e[0;31m[!] Failed to initialize a mutex\e[0m"

// --- STRUCTURE ---

typedef struct s_data
{
	int32_t			time_to_die;
	int32_t			time_to_eat;
	int32_t			time_to_sleep;
	int32_t			must_eat;
	int32_t			nb_max;

}					t_data;

typedef struct s_philo
{
	// SHARED
	pthread_mutex_t	mtx_last_meal;
	pthread_mutex_t	mtx_meal_eated;
	pthread_mutex_t	*dead_lock;
	pthread_mutex_t	*shut_up_lock;
	pthread_mutex_t	*stdout_lock;
	pthread_mutex_t	*fork_r;
	pthread_mutex_t	*fork_l;

	int32_t			*time_to_die;
	int32_t			*time_to_eat;
	int32_t			*time_to_sleep;
	int32_t			*must_eat;
	int32_t			*nb_max;

	bool			*shut_up;
	bool			*dead_status;
	bool			isEating;

	// SELF
	pthread_t		id;
	pthread_t		reaper_id;
	int32_t			number;
	int				meal_eated;
	int32_t			since_meal;
	bool			ready;
	int32_t			start_time;
}					t_philo;

typedef struct s_shared
{
	t_philo			*philo;
	t_data			*data;
	pthread_mutex_t	*fork_arr;
	pthread_mutex_t	stdout_lock;
	pthread_mutex_t	shut_up_lock;
	pthread_mutex_t	dead_lock;

	pthread_t		id_reaper;
	int32_t			thread_created;
	bool			shut_up;
	bool			dead_status;
}					t_shared;

// --- PROTOTYPES ---
//   --- lib.c ---
long				ft_atol(char *number);
int					ft_atoi(const char *nptr);
size_t				ft_strlen(char *number);
bool				string_isdigit(char *number);
void				*ft_calloc(size_t nmemb, size_t size);

//   --- utils.c ---
int					mod_perror(char *error);
int32_t				get_mstime(void);
void				succes_exit(t_shared *shared);
void				failed_exit(t_shared *shared, int stopped_at);
void				safe_print(t_philo *philo, char *str, int32_t number);
void				better_usleep(t_philo *philo, int32_t time);

//   --- parsing.c ---
bool				parsing(int argc, char **argv, t_shared *shared);

//   --- threading.c ---
bool				check_die(t_philo *philo);
void				*philosophers(void *ptr_philo);

//   --- action.c ---
bool				philo_sleeping(t_philo *philo);
bool				philo_thinking(t_philo *philo);
bool				philo_eat(t_philo *philo);

//   --- reaper.c ---
void				*reaper(void *ptr_shared);

// --- structure.c ---
bool				init_shared(t_shared *share, int nb_max_philo, int argc,
						char **argv);
void				init_philo(t_shared *share, int iter);
bool				init_data(t_data **data, int argc, char **argv);

#endif
