
#include <../include/philo.h>

int	sleeping(t_philo *philosopher)
{
	long	timer;
	long	time_to_sleep;

	time_to_sleep = philosopher->time_to_sleep;
	timer = get_time();
	if (!timer)
		return (0);
	if (!safe_print(4, philosopher->table, philosopher->id))
		return (0);
	if (!timekeeper(time_to_sleep, philosopher->table))
		return (0);
	if (check_if_someone_is_dead(philosopher->table))
		return (0);
	return (1);
}

int	take_forks(t_mutex *firstfork, t_mutex *secondfork, t_philo *philo)
{
	pthread_mutex_lock(firstfork);
	if (check_if_someone_is_dead(philo->table))
	{
		pthread_mutex_unlock(firstfork);
		return (0);
	}
	if (!safe_print(2, philo->table, philo->id))
		return (0);
	pthread_mutex_lock(secondfork);
	if (check_if_someone_is_dead(philo->table))
	{
		unlock_forks(philo);
		return (0);
	}
	if (!safe_print(2, philo->table, philo->id))
		return (0);
	return (1);
}

int	eating(t_philo *philosopher)
{
	long	timer;
	long	time_to_eat;

	time_to_eat = philosopher->time_to_eat;
	timer = get_time();
	if (!timer)
		return (0);
	pthread_mutex_lock(philosopher->last_meal_mutex);
	philosopher->last_meal = timer;
	pthread_mutex_unlock(philosopher->last_meal_mutex);
	if (check_if_someone_is_dead(philosopher->table))
	{
		unlock_forks(philosopher);
		return (0);
	}
	if (!safe_print(3, philosopher->table, philosopher->id))
		return (0);
	usleep (time_to_eat * 1000);
	unlock_forks(philosopher);
	return (1);
}

int	take_forks_and_eat(t_philo *philosopher)
{
	t_mutex	*left_fork;
	t_mutex	*right_fork;

	left_fork = philosopher->left_fork;
	right_fork = philosopher->right_fork;
	if (philosopher->id % 2)
	{
		if (!take_forks(left_fork, right_fork, philosopher))
			return (0);
	}
	else
	{
		if (!take_forks(right_fork, left_fork, philosopher))
			return (0);
	}
	if (check_if_someone_is_dead(philosopher->table))
	{
		unlock_forks(philosopher);
		return (0);
	}
	if (!eating(philosopher))
		return (0);
	return (1);
}
