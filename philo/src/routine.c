/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagimeno <dagimeno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 13:52:21 by dagimeno          #+#    #+#             */
/*   Updated: 2025/01/30 13:28:29 by dagimeno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static int	cycle(t_philos *philosopher);
static int	take_forks(t_philos *philosopher);
int	check_if_someone_is_dead(t_table *table);

void	*routine(void *arg)
{
	t_philos	*philosopher;
	size_t		cycles;
	//char			is_dead;
	//pthread_t		thread;
	//struct timeval	last_meal;

	philosopher = (t_philos *)arg;
	cycles = philosopher->table->number_of_times_each_philosopher_must_eat;
	//printf("Thread address in the thread: %p\n", philosopher.thread);
	//printf("In the thread: %zu\n", philosopher.id);
	//philosopher.last_meal = get_time();
	philosopher->last_meal = philosopher->start_time;
	//if (pthread_create(&thread, NULL, &check_death, &philosopher))
	//gettimeofday(&last_meal, NULL);
	//printf("%ld last meal\n", last_meal.tv_usec);
	//philosopher.last_meal = last_meal.tv_usec / 1000;
	//printf("%ld %zu is thinking\n", philosopher.last_meal, philosopher.id);
	printf("0 %zu is thinking\n", philosopher->id);
	if (philosopher->id % 2 == 0 && philosopher->table->time_to_think > 0)
		usleep(philosopher->table->time_to_eat * 1000);
	//is_dead = 0;
	if (!cycles)
	{
		while (!check_if_someone_is_dead(philosopher->table))
		{
			//is_dead = cycle(&philosopher);
			//if (pthread_create(&thread, NULL, &check_death, &philosopher) != 0)
			if (!cycle(philosopher))
				return (NULL);
			//if (pthread_join(thread, NULL) != 0)
			//	return (0);
		}
		return (NULL);
	}
	while (cycles-- && check_if_someone_is_dead(philosopher->table))
	{
		//if (pthread_create(&thread, NULL, &check_death, &philosopher) != 0)
		//	return (0);
		if (!cycle(philosopher))
			return (NULL);
		//if (!cycle(&philosopher))
			//return (NULL);
		//if (pthread_join(thread, NULL) != 0)
		//	return (0);
		//printf("perdona\n");
	}
	philosopher->is_done = 1;
	pthread_mutex_lock(&philosopher->table->are_done_mutex);
	philosopher->table->are_done++;
	pthread_mutex_unlock(&philosopher->table->are_done_mutex);
	return (NULL);
}

static int	cycle(t_philos *philosopher)
{
	size_t	timer;
	size_t	time_to_eat;
	size_t	time_to_sleep;
	//size_t	time_to_die;
	size_t	start_time;

	//time_to_die = philosopher->table->time_to_die;
	//philosopher->table->are_done++;
	time_to_eat = philosopher->table->time_to_eat;
	time_to_sleep = philosopher->table->time_to_sleep;
	start_time = philosopher->start_time;
	if (check_if_someone_is_dead(philosopher->table))
		return (0);
	if (!take_forks(philosopher))
		return (0);
	//lock_forks(philosopher->left_fork, philosopher->right_fork, philosopher->id);
	/*gettimeofday(&timer, NULL);
	if (timer / 1000 - philosopher->last_meal > philosopher->table->time_to_die)
	{
		printf ("%ld %zu died\n", timer / 1000, philosopher->id);
		unlock_forks(philosopher->left_fork, philosopher->right_fork);
		return (0);
	}*/
	timer = get_time();
	philosopher->last_meal = timer;
	//printf("Inside cycle> %zu last meal: %zu\n", philosopher->id, philosopher->last_meal);
	//printf("%zu - %zu = %zu\n", timer, philosopher->last_meal, timer - philosopher->last_meal);
	if (check_if_someone_is_dead(philosopher->table))
		return (0);
	printf ("%ld %zu is eating\n", timer - start_time, philosopher->id);
	/*if (time_to_eat >= time_to_die)
	{
		unlock_forks(philosopher->left_fork, philosopher->right_fork);
		usleep(time_to_die * 1000);
		printf("%ld %zu died\n", get_time() - philosopher->start_time, philosopher->id);
		return (0);
	}*/
	//printf("last meal in cycle: %ld\n", philosopher->last_meal);
	//printf("%ld timer\n", timer.tv_usec);
	usleep(time_to_eat * 1000);
	unlock_forks(philosopher);
	if (check_if_someone_is_dead(philosopher->table))
		return (0);
	//philosopher->is_left_locked = 0;
	timer = get_time() - philosopher->start_time;
	printf ("%ld %zu is sleeping\n", get_time() - start_time, philosopher->id);
	/*if (time_to_eat + time_to_sleep >= time_to_die)
	{
		usleep((time_to_die - time_to_eat) * 1000);
		printf("%ld %zu died\n", get_time() - philosopher->start_time, philosopher->id);
		return (0);
	}*/
	//gettimeofday(&timer, NULL);
	//printf("%ld timer\n", timer.tv_usec);
	usleep(time_to_sleep * 1000);
	//timer = get_time();
	//gettimeofday(&timer, NULL);
//	printf("%ld timer\n", timer.tv_usec);
	//printf ("%ld %zu is thinking\n", timer, philosopher->id);
	//if (time_to_eat > time_to_sleep)
	//{
	//	printf("%ld %zu is thinking\n", get_time() - philosopher->start_time, philosopher->id);
	//	usleep(time_to_die - (time_to_eat + time_to_sleep));
	//	printf("%ld %zu died\n", get_time() - philosopher->start_time, philosopher->id);
	//		return (0);
	//}
	//printf ("timer when cycle ends: %zu\n", get_time() - start_time);
	if (check_if_someone_is_dead(philosopher->table))
		return (0);
	printf("%ld %zu is thinking\n", get_time() - philosopher->start_time, philosopher->id);
	if (philosopher->table->time_to_think > 0 && philosopher->table->number_of_philosophers % 2 == 1)
		usleep (philosopher->table->time_to_think * 1000);
	return (1);
}

static int	take_forks(t_philos *philosopher)
{
	//size_t	timer;

	if (check_if_someone_is_dead(philosopher->table))
		return (0);
	//timer = get_time();
	//if (timer - philosopher->last_meal >= philosopher->time_to_die)
	//{
	//	printf("%ld %zu died\n", timer, philosopher->id);
	//	return (1);
	//}
	//if (philosopher->number_of_philosophers == 1 ||
	//	(philosopher->time_to_eat * 2 >= philosopher->time_to_die && philosopher->number_of_philosophers % 2 == 1 && philosopher->id == philosopher->number_of_philosophers - 1))
	//{
	//philosopher->has_had_first_meal = 1;
	if (philosopher->id != philosopher->table->number_of_philosophers)
	{
		if (check_if_someone_is_dead(philosopher->table))
			return (0);
		pthread_mutex_lock(philosopher->left_fork);
		if (check_if_someone_is_dead(philosopher->table))
		{
			pthread_mutex_unlock(philosopher->left_fork);
			return (0);
		}
		philosopher->is_left_locked = 1;
		printf("%ld %zu has taken a fork\n", get_time() - philosopher->start_time, philosopher->id);
		if (check_if_someone_is_dead(philosopher->table))
			return (0);
		pthread_mutex_lock(philosopher->right_fork);
		if (check_if_someone_is_dead(philosopher->table))
		{
			pthread_mutex_unlock(philosopher->right_fork);
			return (0);
		}
		philosopher->is_right_locked = 1;
		printf("%ld %zu has taken a fork\n", get_time() - philosopher->start_time, philosopher->id);
	}
	else
	{
		if (check_if_someone_is_dead(philosopher->table))
			return (0);
		pthread_mutex_lock(philosopher->right_fork);
		if (check_if_someone_is_dead(philosopher->table))
		{
			pthread_mutex_unlock(philosopher->right_fork);
			return (0);
		}
		philosopher->is_right_locked = 1;
		printf("%ld %zu has taken a fork\n", get_time() - philosopher->start_time, philosopher->id);
		if (check_if_someone_is_dead(philosopher->table))
			return (0);
		pthread_mutex_lock(philosopher->left_fork);
		if (check_if_someone_is_dead(philosopher->table))
		{
			pthread_mutex_unlock(philosopher->left_fork);
			return (0);
		}
		philosopher->is_left_locked = 1;
		printf("%ld %zu has taken a fork\n", get_time() - philosopher->start_time, philosopher->id);
	}
	if (check_if_someone_is_dead(philosopher->table))
		return (0);
	//pthread_mutex_lock(philosopher->left_fork);
	//philosopher->is_locked = 1;
	//timer = get_time() - philosopher->start_time;
	//philosopher->is_left_locked = 1;
	//printf("%ld %zu has taken a fork\n", get_time() - philosopher->start_time, philosopher->id);
	//gettimeofday(&fork_time, NULL);
	//printf("%ld %zu has taken a fork\n", timer, philosopher->id);
	//printf("Fork: %p\n", (void *)left_fork);
	//if (lock_forks(philosopher))
		//return (1);
	//pthread_mutex_lock(philosopher->right_fork);
	//timer = get_time() - philosopher->start_time;
	//philosopher->is_right_locked = 1;
	//printf("%ld %zu has taken a fork\n", get_time() - philosopher->start_time, philosopher->id);
	//gettimeofday(&fork_time, NULL);
	//fork_time = get_time();
	//printf("%ld %zu has taken a fork\n", timer, philosopher->id);
	//printf("Fork: %p\n", (void *)right_for);
	//return (0);
	return (1);
}

/*char	is_dead(t_philos *philosopher)
{
	if (timer >= time_to_die)
		return (1);
	return (0);
}*/

/*char	lock_forks(t_philos *philosopher)
{
	//long	timer;
	
	while (pthread_mutex_lock(philosopher->left_fork) != 0)
	{
		printf("Hola\n");
	}
	while (pthread_mutex_lock(philosopher->right_fork) != 0)
	{
		printf("Adiós\n");
	}
	return (0);
}*/

int	check_if_someone_is_dead(t_table *table)
{
	pthread_mutex_lock(&table->is_someone_dead_mutex);
	if (table->is_someone_dead)
	{
		pthread_mutex_unlock(&table->is_someone_dead_mutex);
		return (1);
	}
	pthread_mutex_unlock(&table->is_someone_dead_mutex);
	return (0);
}
