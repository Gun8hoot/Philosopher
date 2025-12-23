

#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H

# include <unistd.h>
# include <stdbool.h>
# include <limits.h>
# include <stdio.h>
# include <string.h>

typedef struct s_philo
{
	int parameter[5];	
	int exclude;
	int	nb_fork;
} t_philo;

bool	parsing(int argc, char **argv, t_philo *philo);
int		ft_atoi(char *number);
int		ft_atol(char *number);
size_t	ft_strlen(char *number);
int		mod_perror(char *error);
//	int nb_philosophers;
//	int time_to_die;
//	int time_to_eat;
//	int time_to_sleep;
//	int must_eat;

#endif
