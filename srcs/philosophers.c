#include "incs/philosophers.h"

int main(int argc, char **argv)
{
	t_philo philo;
  
	if (argc != 5 && argc != 6)
		return (1);
	if(parsing(argc, argv, &philo))
		return (mod_perror("[!] Not enought arguments !"));
	return (0);
}
