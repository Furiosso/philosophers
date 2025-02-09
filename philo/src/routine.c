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

	philosopher = (t_philos *)arg;
	cycles = philosopher->number_of_times_each_philosopher_must_eat;
	pthread_mutex_lock(&philosopher->table->everyone_is_ready_mutex);
	philosopher->table->everyone_is_ready++;
	pthread_mutex_unlock(&philosopher->table->everyone_is_ready_mutex);
	philosopher->start_time = wait_for_everyone_to_be_ready(philosopher->table);
	check_if_someone_is_dead(philosopher->table);
	pthread_mutex_lock(philosopher->last_meal_mutex);
	philosopher->last_meal = philosopher->start_time;
	pthread_mutex_unlock(philosopher->last_meal_mutex);
	printf("0 %zu is thinking\n", philosopher->id);
	if (philosopher->id % 2== 0)
	{
		if (!timekeeper(philosopher->time_to_start, 1, philosopher->table))
			return (NULL);
	}
	if (!cycles)
	{
		while (!check_if_someone_is_dead(philosopher->table))
		{
			if (!cycle(philosopher))
				return (NULL);
		}
		return (NULL);
	}
	while (cycles-- && !check_if_someone_is_dead(philosopher->table))
	{
		if (!cycle(philosopher))
			return (NULL);
	}
	//pthread_mutex_lock(philosopher->is_done_mutex);
	//philosopher->is_done = 1;
	//pthread_mutex_unlock(philosopher->is_done_mutex);
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
	size_t	start_time;

	time_to_eat = philosopher->time_to_eat;
	time_to_sleep = philosopher->time_to_sleep;
	start_time = philosopher->start_time;
	if (check_if_someone_is_dead(philosopher->table))
		return (0);
	if (!take_forks(philosopher))
		return (0);
	timer = get_time();
	if (!timer)
		return (0);
	pthread_mutex_lock(philosopher->last_meal_mutex);
	philosopher->last_meal = timer;
	//printf ("filosofo %zu last meal: %zu\n", philosopher->id, philosopher->last_meal - philosopher->start_time);
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
	if (check_if_someone_is_dead(philosopher->table))
		return (0);
	//philosopher->is_left_locked = 0;
	timer = get_time() - start_time;
	printf ("%ld %zu is sleeping\n", get_time() - start_time, philosopher->id);
	if (!timekeeper(time_to_sleep, 1, philosopher->table))
		return (0);
	if (check_if_someone_is_dead(philosopher->table))
		return (0);
	printf("%ld %zu is thinking\n", get_time() - start_time, philosopher->id);
	if (philosopher->number_of_philosophers % 2 == 1)
	{
		if (!timekeeper (philosopher->time_to_think, 1, philosopher->table))
			return (0);
	}
	return (1);
}

static int	take_forks(t_philos *philosopher)
{
	/*int		has_taken_a_fork[2];

	has_taken_a_fork[0] = 0;
	has_taken_a_fork[1] = 0;
	if (check_if_someone_is_dead(philosopher->table))
		return (0);
	while (!has_taken_a_fork[0] && !has_taken_a_fork[1])
	{
		pthread_mutex_lock(philosopher->left_fork_mutex);
		if (check_if_someone_is_dead(philosopher->table))
		{
			pthread_mutex_unlock(philosopher->left_fork_mutex);
			unlock_forks(philosopher);
			return (0);
		}
		if (!*philosopher->is_left_locked)
		{
			*philosopher->is_left_locked = 1;
			has_taken_a_fork[0] = 1;
		}
		pthread_mutex_unlock(philosopher->left_fork_mutex);
		if (check_if_someone_is_dead(philosopher->table))
		{
			unlock_forks(philosopher);
			return (0);
		}
		if (has_taken_a_fork[0])
			break ;
		pthread_mutex_lock(philosopher->right_fork_mutex);
		if (check_if_someone_is_dead(philosopher->table))
		{
			pthread_mutex_unlock(philosopher->right_fork_mutex);
			unlock_forks(philosopher);
			return (0);
		}
		if (!*philosopher->is_right_locked)
		{
			*philosopher->is_right_locked = 1;
			has_taken_a_fork[1] = 1;
		}
		pthread_mutex_unlock(philosopher->right_fork_mutex);
		if (check_if_someone_is_dead(philosopher->table))
		{
			unlock_forks(philosopher);
			return (0);
		}
	}
	if (has_taken_a_fork[0])
	{
		pthread_mutex_lock(philosopher->left_fork);
		if (check_if_someone_is_dead(philosopher->table))
		{
			unlock_forks(philosopher);
			return (0);
		}
		printf("%ld %zu has taken a fork\n", get_time() - philosopher->start_time, philosopher->id);
		pthread_mutex_lock(philosopher->right_fork);
		pthread_mutex_lock(philosopher->right_fork_mutex);
		*philosopher->is_right_locked = 1;
		pthread_mutex_unlock(philosopher->right_fork_mutex);
		if (check_if_someone_is_dead(philosopher->table))
		{
			unlock_forks(philosopher);
			return (0);
		}
		printf("%ld %zu has taken a fork\n", get_time() - philosopher->start_time, philosopher->id);
	}
	else
	{
		pthread_mutex_lock(philosopher->right_fork);
		if (check_if_someone_is_dead(philosopher->table))
		{
			unlock_forks(philosopher);
			return (0);
		}
		printf("%ld %zu has taken a fork\n", get_time() - philosopher->start_time, philosopher->id);
		pthread_mutex_lock(philosopher->left_fork);
		pthread_mutex_lock(philosopher->left_fork_mutex);
		*philosopher->is_left_locked = 1;
		pthread_mutex_unlock(philosopher->left_fork_mutex);
		if (check_if_someone_is_dead(philosopher->table))
		{
			unlock_forks(philosopher);
			return (0);
		}
		printf("%ld %zu has taken a fork\n", get_time() - philosopher->start_time, philosopher->id);
	}*/
	//if (philosopher->id == philosopher->number_of_philosophers)
	if (philosopher->id % 2 == 1)
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
		{
			pthread_mutex_unlock(philosopher->left_fork);
			return (0);
		}
		pthread_mutex_lock(philosopher->right_fork);
		if (check_if_someone_is_dead(philosopher->table))
		{
			pthread_mutex_unlock(philosopher->left_fork);
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
		{
			pthread_mutex_unlock(philosopher->right_fork);
			return (0);
		}
		pthread_mutex_lock(philosopher->left_fork);
		if (check_if_someone_is_dead(philosopher->table))
		{
			pthread_mutex_unlock(philosopher->left_fork);
			pthread_mutex_unlock(philosopher->right_fork);
			return (0);
		}
		philosopher->is_left_locked = 1;
		printf("%ld %zu has taken a fork\n", get_time() - philosopher->start_time, philosopher->id);
	}
	if (check_if_someone_is_dead(philosopher->table))
	{
		unlock_forks(philosopher);
		return (0);
	}
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
