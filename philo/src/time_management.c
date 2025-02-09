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

int	timekeeper(long time, int has_to_check_death, t_table *table)
{
	long	start_time;
	long	timer;

	start_time = get_time();
	if (start_time < 0)
		return (0);
	timer = get_time();
	if (timer < 0)
		return (0);
	while (timer - start_time < time)
	{
		if (has_to_check_death && check_if_someone_is_dead(table))
				return (0);
		timer = get_time();
		if (timer < 0)
			return (0);
	}
	return (1);
}


long	get_time(void)
{
	struct timeval	timer;

	if (gettimeofday(&timer, NULL) < 0)
	{
		ft_print_error("Could not get time\n");
		return (0);
	}
	return (timer.tv_sec * 1000 + timer.tv_usec / 1000);
}

long wait_for_everyone_to_be_ready(t_table *table)
{
	size_t	number_of_philosophers;

	number_of_philosophers = table->number_of_philosophers;
	while (1)
	{
		pthread_mutex_lock(&table->start_time_mutex);
		if (table->everyone_is_ready == number_of_philosophers)
		{
			pthread_mutex_unlock(&table->start_time_mutex);
			break ;
		}
		pthread_mutex_unlock(&table->start_time_mutex);
	}
	pthread_mutex_lock(&table->start_time_mutex);
	if (!table->start_time)
	{
	table->start_time = get_time();
		if (!table->start_time)
		{
			pthread_mutex_unlock(&table->start_time_mutex);
			return (0);
		}
	}
	pthread_mutex_unlock(&table->start_time_mutex);
	return (table->start_time);
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
