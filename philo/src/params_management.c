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

t_philo	fill_params(t_table *table, t_mutex *forks, int i)
{
	t_philo	philosopher;

	philosopher.id = i + 1;
	philosopher.left_fork = &forks[i];
	philosopher.right_fork = &forks[i + 1];
	if (philosopher.id == table->num_of_philos)
	{
		philosopher.right_fork = &forks[0];
	}
	philosopher.last_meal_mutex = &table->last_meal_mutex[i];
	philosopher.num_of_philos = table->num_of_philos;
	philosopher.time_to_eat = table->time_to_eat;
	philosopher.time_to_sleep = table->time_to_sleep;
	philosopher.time_to_think = table->time_to_think;//revisar time to think
	if (philosopher.time_to_think < 1)
		philosopher.time_to_think = philosopher.time_to_eat;
	philosopher.table = table;
	philosopher.time_to_start = philosopher.table->time_to_die;//y time to start
	if (philosopher.time_to_eat < philosopher.table->time_to_die)
		philosopher.time_to_start = philosopher.time_to_eat;
	philosopher.num_of_cycles = table->num_of_cycles;
	return (philosopher);
}

void	cut_the_threads(t_table *table)
{
	pthread_mutex_lock(&table->is_someone_dead_mutex);
	table->is_someone_dead = 1;
	pthread_mutex_unlock(&table->is_someone_dead_mutex);
	pthread_mutex_lock(&table->start_time_mutex);
	table->everyone_is_ready = table->num_of_philos;
	pthread_mutex_unlock(&table->start_time_mutex);
}
