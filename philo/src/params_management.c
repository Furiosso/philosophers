#include "../include/philo.h"

t_philosophers	fill_params(char **argv, pthread_mutex_t *forks, int i)
{
	t_philosophers	philosopher;

	//philosophers = ft_calloc(1, sizeof(t_philosophers));
	//if (!philosophers)
	//	return (NULL);
	philosopher.number_of_philosophers = ft_atoi(argv[1]);
	philosopher.id = i + 1;
	philosopher.left_fork = &forks[i];
	if (philosopher.id == philosopher.number_of_philosophers)
		philosopher.right_fork = &forks[0];
	else
		philosopher.right_fork = &forks[i + 1];
	philosopher.time_to_die = ft_atoi(argv[2]) * 1000;
	philosopher.time_to_eat = ft_atoi(argv[3]) * 1000;
	philosopher.time_to_sleep = ft_atoi(argv[4]) * 1000;
	if (argv[5])
		philosopher.number_of_times_each_philosopher_must_eat = ft_atoi(argv[5]);
	return (philosopher);
}
