/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagimeno <dagimeno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 13:52:21 by dagimeno          #+#    #+#             */
/*   Updated: 2025/01/04 20:30:10 by dagimeno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static int	cycle(t_philosophers *philosopher);
static char	think(t_philosophers *philosopher);

void	*routine(void *arg)
{
	t_philosophers	philosopher;
	char			is_dead;
	//pthread_t		thread;
	//struct timeval	last_meal;

	philosopher = *(t_philosophers *)arg;
	//printf("Thread address in the thread: %p\n", philosopher.thread);
	//printf("In the thread: %d\n", philosopher.id);
	//philosopher.last_meal = get_time();
	philosopher.last_meal = philosopher.start_time;
	//if (pthread_create(&thread, NULL, &check_death, &philosopher))
	//gettimeofday(&last_meal, NULL);
	//printf("%ld last meal\n", last_meal.tv_usec);
	//philosopher.last_meal = last_meal.tv_usec / 1000;
	//printf("%ld %d is thinking\n", philosopher.last_meal, philosopher.id);
	is_dead = 0;
	if (!philosopher.number_of_times_each_philosopher_must_eat)
	{
		while (!is_dead)
		{
			is_dead = cycle(&philosopher);
			//if (pthread_create(&thread, NULL, &check_death, &philosopher) != 0)
			//	return (0);
			//if (pthread_join(thread, NULL) != 0)
			//	return (0);
		}
		return (NULL);
	}
	while (philosopher.number_of_times_each_philosopher_must_eat-- && !is_dead)
	{
		//if (pthread_create(&thread, NULL, &check_death, &philosopher) != 0)
		//	return (0);
		is_dead = cycle(&philosopher);
		//if (!cycle(&philosopher))
			//return (NULL);
		//if (pthread_join(thread, NULL) != 0)
		//	return (0);
	}
	return (NULL);
}

static int	cycle(t_philosophers *philosopher)
{
	long	timer;
	//pthread_t		thread;

	if (think(philosopher))
		return (1);
	//lock_forks(philosopher->left_fork, philosopher->right_fork, philosopher->id);
	timer = get_time();
	/*gettimeofday(&timer, NULL);
	if (timer.tv_usec / 1000 - philosopher->last_meal > philosopher->time_to_die)
	{
		printf ("%ld %d died\n", timer.tv_usec / 1000, philosopher->id);
		unlock_forks(philosopher->left_fork, philosopher->right_fork);
		return (0);
	}*/
	philosopher->last_meal = timer;
	printf ("%ld %d is eating\n", timer - philosopher->start_time, philosopher->id);
	if (philosopher->time_to_eat >= philosopher->time_to_die)
	{
		usleep(philosopher->time_to_die * 1000);
		printf("%ld %d died\n", get_time() - philosopher->start_time, philosopher->id);
		return (1);
	}
	//printf("last meal in cycle: %ld\n", philosopher->last_meal);
	//printf("%ld timer\n", timer.tv_usec);
	usleep(philosopher->time_to_eat * 1000);
	unlock_forks(philosopher->left_fork, philosopher->right_fork);
	philosopher->is_locked = 0;
	timer = get_time() - philosopher->start_time;
	printf ("%ld %d is sleeping\n", timer, philosopher->id);
	if (philosopher->time_to_eat + philosopher->time_to_sleep >= philosopher->time_to_die)
	{
		usleep((philosopher->time_to_die - philosopher->time_to_eat) * 1000);
		printf("%ld %d died\n", get_time() - philosopher->start_time, philosopher->id);
		return (1);
	}
	//gettimeofday(&timer, NULL);
	//printf("%ld timer\n", timer.tv_usec);
	usleep(philosopher->time_to_sleep * 1000);
	//timer = get_time();
	//gettimeofday(&timer, NULL);
//	printf("%ld timer\n", timer.tv_usec);
	//printf ("%ld %d is thinking\n", timer, philosopher->id);
	return (0);
}

static char	think(t_philosophers *philosopher)
{
	long	timer;

	timer = get_time();
	//if (timer - philosopher->last_meal >= philosopher->time_to_die)
	//{
	//	printf("%ld %d died\n", timer, philosopher->id);
	//	return (1);
	//}
	printf("%ld %d is thinking\n", timer - philosopher->start_time, philosopher->id);
	if (philosopher->number_of_philosophers == 1 ||
		(philosopher->time_to_eat * 2 >= philosopher->time_to_die && philosopher->number_of_philosophers % 2 == 1 && philosopher->id == philosopher->number_of_philosophers - 1))
	{
		if (philosopher->number_of_philosophers == 1)
			printf("%ld %d has taken a fork\n", get_time() - philosopher->start_time, philosopher->id);
		usleep(philosopher->time_to_die * 1000);
		printf("%ld %d died\n", get_time() - philosopher->start_time, philosopher->id);
		return (1);
	}
	pthread_mutex_lock(philosopher->left_fork);
	//philosopher->is_locked = 1;
	//timer = get_time() - philosopher->start_time;
	printf("%ld %d has taken a fork\n", get_time() - philosopher->start_time, philosopher->id);
	//gettimeofday(&fork_time, NULL);
	//printf("%ld %d has taken a fork\n", timer, philosopher->id);
	//printf("Fork: %p\n", (void *)left_fork);
	//if (lock_forks(philosopher))
		//return (1);
	pthread_mutex_lock(philosopher->right_fork);
	//timer = get_time() - philosopher->start_time;
	printf("%ld %d has taken a fork\n", get_time() - philosopher->start_time, philosopher->id);
	//gettimeofday(&fork_time, NULL);
	//fork_time = get_time();
	//printf("%ld %d has taken a fork\n", timer, philosopher->id);
	//printf("Fork: %p\n", (void *)right_fork);
	return (0);
}

/*char	is_dead(t_philosophers *philosopher)
{
	if (timer >= time_to_die)
		return (1);
	return (0);
}*/

/*char	lock_forks(t_philosophers *philosopher)
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