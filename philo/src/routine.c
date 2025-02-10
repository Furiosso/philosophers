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

static int	check_cycles(t_philo *philosopher)
{
	if (philosopher->num_of_cycles)
	{
		philosopher->num_of_cycles--;
		if (!philosopher->num_of_cycles)
		{
			pthread_mutex_lock(&philosopher->table->are_done_mutex);
			philosopher->table->are_done++;
			pthread_mutex_unlock(&philosopher->table->are_done_mutex);
			return (1);
		}
	}
	return (0);
}

static int	cycle(t_philo *philosopher)
{
	long	timer;
	size_t	start_time;

	start_time = philosopher->start_time;
	if (!take_forks_and_eat(philosopher))
		return (0);
	if (check_if_someone_is_dead(philosopher->table))
		return (0);
	if (!sleeping(philosopher))
		return (0);
	timer = get_time();
	if (!timer)
		return (0);
	printf("%ld %zu is thinking\n", timer - start_time, philosopher->id);
	if ((philosopher->num_of_philos % 2) == 1 && (philosopher->id % 2 == 1))
	{
		if (!timekeeper (philosopher->time_to_think * 0.45, 1, philosopher->table))
			return (0);
	}
	if (check_cycles(philosopher))
		return (0);
	return (1);
}

void	*routine(void *arg)
{
	t_philo	*philosopher;

	philosopher = (t_philo *)arg;
	pthread_mutex_lock(&philosopher->table->start_time_mutex);
	philosopher->table->everyone_is_ready++;
	pthread_mutex_unlock(&philosopher->table->start_time_mutex);
	philosopher->start_time = wait_for_everyone_to_be_ready(philosopher->table);
	if (!philosopher->start_time)
		return (NULL);
	//check_if_someone_is_dead(philosopher->table);
	pthread_mutex_lock(philosopher->last_meal_mutex);
	philosopher->last_meal = philosopher->start_time;
	pthread_mutex_unlock(philosopher->last_meal_mutex);
	printf("0 %zu is thinking\n", philosopher->id);
	if (philosopher->id % 2 == 1)
	{
		if (!timekeeper(philosopher->time_to_start, 1, philosopher->table))
			return (NULL);
	}
	while (!check_if_someone_is_dead(philosopher->table))
	{
		if (!cycle(philosopher))
			return (NULL);
	}
	return (NULL);
}
