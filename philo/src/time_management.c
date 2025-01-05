#include "../include/philo.h"

long	get_time(void)
{
	struct timeval	timer;

	gettimeofday(&timer, NULL);
	return (timer.tv_sec * 1000 + timer.tv_usec / 1000);
}

/*long	calculate_time_since_last_meal(philosopher)
{
	
}*/

void	*check_death(void *arg)
{
	long			timer;
	t_philosophers	philosopher;

	philosopher = *(t_philosophers *)arg;
	while (1)
	{
		
		//printf("%d: last meal in death check: %ld\n", philosopher.id, get_time() - philosopher.last_meal);
		timer = get_time() - philosopher.last_meal;
		if (timer >= philosopher.time_to_die)
		{
			printf("%ld %d died\n", timer, philosopher.id);
			if (philosopher.is_locked)
				pthread_mutex_unlock(philosopher.left_fork);
			pthread_detach(*philosopher.thread);
			break ;
		}
	}
	return (NULL);
}