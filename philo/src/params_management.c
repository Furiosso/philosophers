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
	philosopher.left_fork = &forks[i];
	//philosopher.left_fork_mutex = &table->is_fork_locked_mutex[i];
	//philosopher.is_left_locked = &table->is_fork_locked[i];
	philosopher.right_fork = &forks[i + 1];
	//philosopher.right_fork_mutex = &table->is_fork_locked_mutex[i + 1];
	//philosopher.is_right_locked = &table->is_fork_locked[i + 1];
	if (philosopher.id == table->number_of_philosophers)
	{
		philosopher.right_fork = &forks[0];
		//philosopher.right_fork_mutex = &table->is_fork_locked_mutex[0];
		//philosopher.is_right_locked = &table->is_fork_locked[0];
	}
	//philosopher.is_done_mutex = &table->are_done_mutex;
	philosopher.last_meal_mutex = &table->last_meal_mutex[i];
	philosopher.number_of_philosophers = table->number_of_philosophers;
	philosopher.time_to_eat = table->time_to_eat;
	philosopher.time_to_sleep = table->time_to_sleep;
	philosopher.time_to_think = table->time_to_think;
	if (philosopher.time_to_think == 0)
		philosopher.time_to_think = philosopher.time_to_eat;
	philosopher.table = table;
	philosopher.time_to_start = philosopher.table->time_to_die;
	if (philosopher.time_to_eat < philosopher.table->time_to_die)
		philosopher.time_to_start = philosopher.time_to_eat;
	philosopher.number_of_times_each_philosopher_must_eat = table->number_of_times_each_philosopher_must_eat;
	return (philosopher);
}

void	cut_the_threads(t_table *table)
{
	pthread_mutex_lock(&table->is_someone_dead_mutex);
	table->is_someone_dead = 1;
	pthread_mutex_unlock(&table->is_someone_dead_mutex);
	pthread_mutex_lock(&table->start_time_mutex);
	table->everyone_is_ready = table->number_of_philosophers;
	pthread_mutex_unlock(&table->start_time_mutex);
}
