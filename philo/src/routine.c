/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagimeno <dagimeno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 13:52:21 by dagimeno          #+#    #+#             */
/*   Updated: 2025/01/13 15:07:02 by dagimeno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static int	cycle(t_philos *philosopher);
static void	think(t_philos *philosopher);

void	*routine(void *arg)
{
	t_philos	philosopher;
	size_t		cycles;
	//char			is_dead;
	//pthread_t		thread;
	//struct timeval	last_meal;

	philosopher = *(t_philos *)arg;
	cycles = philosopher.table->number_of_times_each_philosopher_must_eat;
	//printf("Thread address in the thread: %p\n", philosopher.thread);
	//printf("In the thread: %zu\n", philosopher.id);
	//philosopher.last_meal = get_time();
	philosopher.last_meal = philosopher.start_time;
	//if (pthread_create(&thread, NULL, &check_death, &philosopher))
	//gettimeofday(&last_meal, NULL);
	//printf("%ld last meal\n", last_meal.tv_usec);
	//philosopher.last_meal = last_meal.tv_usec / 1000;
	//printf("%ld %zu is thinking\n", philosopher.last_meal, philosopher.id);
	//is_dead = 0;
	if (!cycles)
	{
		while (1)
		{
			//is_dead = cycle(&philosopher);
			//if (pthread_create(&thread, NULL, &check_death, &philosopher) != 0)
			if (!cycle(&philosopher))
				return (NULL);
			//if (pthread_join(thread, NULL) != 0)
			//	return (0);
		}
		return (NULL);
	}
	while (cycles--)
	{
		//if (pthread_create(&thread, NULL, &check_death, &philosopher) != 0)
		//	return (0);
		if (!cycle(&philosopher))
			return (NULL);
		//if (!cycle(&philosopher))
			//return (NULL);
		//if (pthread_join(thread, NULL) != 0)
		//	return (0);
	}
	philosopher.table->are_done++;
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
	philosopher->table->are_done++;
	philosopher->id++;
	time_to_eat = philosopher->table->time_to_eat;
	time_to_sleep = philosopher->table->time_to_sleep;
	start_time = philosopher->start_time;
	think(philosopher);
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
	printf("%zu - %zu = %zu\n", timer, philosopher->last_meal, timer - philosopher->last_meal);
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
	return (1);
}

static void	think(t_philos *philosopher)
{
	size_t	timer;

	timer = get_time();
	//if (timer - philosopher->last_meal >= philosopher->time_to_die)
	//{
	//	printf("%ld %zu died\n", timer, philosopher->id);
	//	return (1);
	//}
	printf("%ld %zu is thinking\n", timer - philosopher->start_time, philosopher->id);
	//if (philosopher->number_of_philosophers == 1 ||
	//	(philosopher->time_to_eat * 2 >= philosopher->time_to_die && philosopher->number_of_philosophers % 2 == 1 && philosopher->id == philosopher->number_of_philosophers - 1))
	//{
	pthread_mutex_lock(philosopher->left_fork);
	//philosopher->is_locked = 1;
	//timer = get_time() - philosopher->start_time;
	philosopher->is_left_locked = 1;
	printf("%ld %zu has taken a fork\n", get_time() - philosopher->start_time, philosopher->id);
	//gettimeofday(&fork_time, NULL);
	//printf("%ld %zu has taken a fork\n", timer, philosopher->id);
	//printf("Fork: %p\n", (void *)left_fork);
	//if (lock_forks(philosopher))
		//return (1);
	pthread_mutex_lock(philosopher->right_fork);
	//timer = get_time() - philosopher->start_time;
	philosopher->is_right_locked = 1;
	printf("%ld %zu has taken a fork\n", get_time() - philosopher->start_time, philosopher->id);
	//gettimeofday(&fork_time, NULL);
	//fork_time = get_time();
	//printf("%ld %zu has taken a fork\n", timer, philosopher->id);
	//printf("Fork: %p\n", (void *)right_for);
	//return (0);
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