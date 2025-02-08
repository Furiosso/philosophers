/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   params_management.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagimeno <dagimeno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 13:51:33 by dagimeno          #+#    #+#             */
/*   Updated: 2025/01/16 22:11:36 by dagimeno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

t_philos	fill_params(t_table *table, t_mutex *forks, int i)
{
	t_philos	philosopher;

	philosopher.id = i + 1;
	//philosopher.thread = thread;
	philosopher.left_fork = &forks[i];
	if (philosopher.id == table->number_of_philosophers)
		philosopher.right_fork = &forks[0];
	else
		philosopher.right_fork = &forks[i + 1];
	philosopher.last_meal_mutex = &table->last_meal_mutex[i];
	philosopher.number_of_philosophers = table->number_of_philosophers;
	philosopher.time_to_eat = table->time_to_eat;
	philosopher.time_to_sleep = table->time_to_sleep;
	philosopher.time_to_think = table->time_to_think;
	philosopher.number_of_times_each_philosopher_must_eat = table->number_of_times_each_philosopher_must_eat;
	philosopher.is_left_locked = 0;
	philosopher.is_right_locked = 0;
	philosopher.has_had_first_meal = 0;
	philosopher.table = table;
	philosopher.is_done = 0;
	return (philosopher);
}

void	cut_the_threads(t_table *table)
{
	pthread_mutex_lock(&table->is_someone_dead_mutex);
	table->is_someone_dead = 1;
	pthread_mutex_unlock(&table->is_someone_dead_mutex);
	pthread_mutex_lock(&table->everyone_is_ready_mutex);
	table->everyone_is_ready = table->number_of_philosophers;
	pthread_mutex_unlock(&table->everyone_is_ready_mutex);
}
