/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagimeno <dagimeno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 13:52:21 by dagimeno          #+#    #+#             */
/*   Updated: 2025/02/11 18:17:39 by dagimeno         ###   ########.fr       */
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

	if (!take_forks_and_eat(philosopher))
		return (0);
	if (check_if_someone_is_dead(philosopher->table))
		return (0);
	if (!sleeping(philosopher))
		return (0);
	timer = get_time();
	if (!timer)
		return (0);
	if (!safe_print(1, philosopher->table, philosopher->id))
		return (0);
	if (philosopher->table->num_of_philos % 2)
	{
		if (!timekeeper (philosopher->time_to_think, philosopher->table))
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
	pthread_mutex_lock(philosopher->last_meal_mutex);
	philosopher->last_meal = wait_for_everyone_to_be_ready(philosopher->table);
	if (!philosopher->last_meal)
	{
		pthread_mutex_unlock(philosopher->last_meal_mutex);
		return (NULL);
	}
	pthread_mutex_unlock(philosopher->last_meal_mutex);
	check_if_someone_is_dead(philosopher->table);
	if (!safe_print(1, philosopher->table, philosopher->id))
		return (NULL);
	if (philosopher->id % 2 == 1)
		usleep(philosopher->time_to_start * 1000);
	while (!check_if_someone_is_dead(philosopher->table))
	{
		if (!cycle(philosopher))
			return (NULL);
	}
	return (NULL);
}

int	safe_print(int behaviour, t_table *table, size_t id)
{
	long	t;

	pthread_mutex_lock(&table->print_mutex);
	t = get_time();
	if (!t)
	{
		pthread_mutex_unlock(&table->print_mutex);
		return (0);
	}
	if (behaviour == 0)
		printf("%s%ld %zu died%s\n", R, t - table->start, id, RS);
	if (!check_if_someone_is_dead(table))
	{
		if (behaviour == 1)
			printf("%s%ld %zu is thinking%s\n", C, t - table->start, id, RS);
		if (behaviour == 2)
			printf("%s%ld %zu has taken a fork%s\n",
				M, t - table->start, id, RS);
		if (behaviour == 3)
			printf("%s%ld %zu is eating%s\n", G, t - table->start, id, RS);
		if (behaviour == 4)
			printf("%s%ld %zu is sleeping%s\n", Y, t - table->start, id, RS);
	}
	pthread_mutex_unlock(&table->print_mutex);
	return (1);
}
