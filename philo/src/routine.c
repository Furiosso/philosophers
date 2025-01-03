#include "../include/philo.h"

static int	cycle(t_philosophers *philosopher);

void	*routine(void *arg)
{
	t_philosophers	philosopher;
	struct timeval	last_meal;

	philosopher = *(t_philosophers *)arg;
	//printf("In the thread: %d\n", philosopher.id);
	gettimeofday(&last_meal, NULL);
	philosopher.last_meal = last_meal.tv_usec;
	printf("000000 %d is thinking\n", philosopher.id);
	if (!philosopher.number_of_times_each_philosopher_must_eat)
	{
		while (1)
			cycle(&philosopher);
	}
	while (philosopher.number_of_times_each_philosopher_must_eat--)
	{
		if (!cycle(&philosopher))
			return (NULL);
	}
	return (NULL);
}

static int	cycle(t_philosophers *philosopher)
{
	struct timeval	timer;

	lock_forks(philosopher->left_fork, philosopher->right_fork, philosopher->id);
	gettimeofday(&timer, NULL);
	if (timer.tv_usec - philosopher->last_meal > philosopher->time_to_die)
	{
		printf ("%ld %d died\n", timer.tv_usec * 1000, philosopher->id);
		unlock_forks(philosopher->left_fork, philosopher->right_fork);
		return (0);
	}
	philosopher->last_meal = timer.tv_usec;
	printf ("%ld %d is eating\n", timer.tv_usec * 1000, philosopher->id);
	usleep(philosopher->time_to_eat);
	unlock_forks(philosopher->left_fork, philosopher->right_fork);
	gettimeofday(&timer, NULL);
	printf ("%ld %d is sleeping\n", timer.tv_usec * 1000, philosopher->id);
	usleep(philosopher->time_to_sleep);
	gettimeofday(&timer, NULL);
	printf ("%ld %d is thinking\n", timer.tv_usec * 1000, philosopher->id);
	return (1);
}
