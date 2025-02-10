
#include <../include/philo.h>

int	sleeping(t_philo *philosopher)
{
	long	timer;
	long	start_time;
	long	time_to_sleep;

	start_time = philosopher->start_time;
	time_to_sleep = philosopher->time_to_sleep;
	timer = get_time();
	if (!timer)
		return (0);
	printf ("%ld %zu is sleeping\n", timer - start_time, philosopher->id);
	if (!timekeeper(time_to_sleep, 1, philosopher->table))
		return (0);
	if (check_if_someone_is_dead(philosopher->table))
		return (0);
	return (1);
}

int	take_forks(t_mutex *firstfork, t_mutex *secondfork, t_philo *philo)
{
	long	start_time;
	size_t	id;

	id = philo->id;
	start_time = philo->start_time;
	pthread_mutex_lock(firstfork);
	if (check_if_someone_is_dead(philo->table))
	{
		pthread_mutex_unlock(firstfork);
		return (0);
	}
	printf("%ld %zu has taken a fork\n", get_time() - start_time, id);
	pthread_mutex_lock(secondfork);
	if (check_if_someone_is_dead(philo->table))
	{
		unlock_forks(philo);
		return (0);
	}
	printf("%ld %zu has taken a fork\n", get_time() - start_time, id);
	return (1);
}

int	eating(t_philo *philosopher)
{
	long	timer;
	long	start_time;
	long	time_to_eat;

	start_time = philosopher->start_time;
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
	printf ("%ld %zu is eating\n", timer - start_time, philosopher->id);
	if (!timekeeper(time_to_eat, 0, NULL))
		return (0);
	unlock_forks(philosopher);
	return (1);
}

int	take_forks_and_eat(t_philo *philosopher)
{
	t_mutex	*left_fork;
	t_mutex	*right_fork;

	left_fork = philosopher->left_fork;
	right_fork = philosopher->right_fork;
	if (!(philosopher->id % 2))
	{
		if (!take_forks(left_fork, right_fork, philosopher))
			return (0);
	}
	else
	{
		if (!take_forks(right_fork, left_fork, philosopher))
			return (0);
	}
	//if (check_if_someone_is_dead(philosopher->table))
	//{
	//	unlock_forks(philosopher);
	//	return (0);
	//}
	if (!eating(philosopher))
		return (0);
	return (1);
}
