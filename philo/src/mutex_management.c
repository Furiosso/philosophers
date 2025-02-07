/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex_management.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagimeno <dagimeno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 13:51:21 by dagimeno          #+#    #+#             */
/*   Updated: 2025/01/12 19:18:07 by dagimeno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"
/*
void		lock_forks(t_mutex *left_fork, t_mutex *right_fork, int id)
{
	long	fork_time;

	pthread_mutex_lock(left_fork);
	fork_time = get_time();
	//gettimeofday(&fork_time, NULL);
	printf("%ld %d has taken a fork\n", fork_time, id);
	//printf("Fork: %p\n", (void *)left_fork);
	pthread_mutex_lock(right_fork);
	//gettimeofday(&fork_time, NULL);
	fork_time = get_time();
	printf("%ld %d has taken a fork\n", fork_time, id);
	//printf("Fork: %p\n", (void *)right_fork);
}
*/

int	check_if_someone_is_dead(t_table *table)
{
	int result;

	result = 0;
	pthread_mutex_lock(&table->is_someone_dead_mutex);
	if (table->is_someone_dead)
		result = 1;
	pthread_mutex_unlock(&table->is_someone_dead_mutex);
	return (result);
}

int	check_mutex(t_mutex *mutex, size_t variable, size_t number_of_philosophers)
{
	int result;

	result = 0;
	pthread_mutex_lock(mutex);
	if (variable == number_of_philosophers)
		result = 1;
	pthread_mutex_unlock(mutex);
	return (result);
}

/*void	lock_mutex(t_mutex *mutex)
{
	pthread_mutex_lock(mutex);
	philosopher->table->everyone_is_ready++;
	pthread_mutex_unlock(mutex);
}*/

void	unlock_forks(t_philos *philosopher)
{
	if (philosopher->is_left_locked)
	{
		pthread_mutex_unlock(philosopher->left_fork);
		philosopher->is_left_locked = 0;
	}
	if (philosopher->is_right_locked)
	{
		pthread_mutex_unlock(philosopher->right_fork);
		philosopher->is_right_locked = 0;
	}
}
