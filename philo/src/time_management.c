/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_management.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagimeno <dagimeno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 20:33:16 by dagimeno          #+#    #+#             */
/*   Updated: 2025/01/13 00:20:56 by dagimeno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

long	get_time(void)
{
	struct timeval	timer;

	if (gettimeofday(&timer, NULL) < 0)
		return (-1);
	return (timer.tv_sec * 1000 + timer.tv_usec / 1000);
}
/*
long	calculate_time_since_last_meal(philosopher)
{
	
}

void	*check_death(void *arg)
{
	long			timer;
	t_philos	philosopher;

	philosopher = *(t_philos *)arg;
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
}*/

size_t wait_for_everyone_to_be_ready(t_table *table)
{
	t_mutex *mutex;
	size_t number_of_philosophers;
	size_t start_time;
	int everyone_is_ready;

	mutex = &table->everyone_is_ready_mutex;
	number_of_philosophers = table->number_of_philosophers;
	everyone_is_ready = 0;
	while (1) {
		pthread_mutex_lock(mutex);
		if (table->everyone_is_ready == number_of_philosophers)
			everyone_is_ready = 1;
		pthread_mutex_unlock(mutex);
		if (everyone_is_ready)
			break;
	}
	start_time = get_time();
	if (!start_time)
		return (0);
	return (start_time);
}

size_t	check_last_meal(size_t time_to_die, size_t timer, t_philos *philosopher)
{
	int		result;

	result = 0;
	pthread_mutex_lock(philosopher->last_meal_mutex);
	if (time_to_die <= (timer - philosopher->last_meal))
		result = 1;
	pthread_mutex_unlock(philosopher->last_meal_mutex);
	return (result);
}
