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
	//int is_locked[2];

	//is_locked[1] = 0;
	//pthread_mutex_lock(philosopher->right_fork_mutex);
	if (philosopher->is_right_locked)
	//	is_locked[1] = 1;
	//pthread_mutex_unlock(philosopher->right_fork_mutex);
	//if (is_locked[1])
	{
		pthread_mutex_unlock(philosopher->right_fork);
		//pthread_mutex_lock(philosopher->right_fork_mutex);
		philosopher->is_right_locked = 0;
		//pthread_mutex_unlock(philosopher->right_fork_mutex);
	}
	//is_locked[0] = 0;
	//pthread_mutex_lock(philosopher->left_fork_mutex);
	if (philosopher->is_left_locked)
	//	is_locked[0] = 1;
	//pthread_mutex_unlock(philosopher->left_fork_mutex);
	//if (is_locked[0])
	{
		pthread_mutex_unlock(philosopher->left_fork);
		//pthread_mutex_lock(philosopher->left_fork_mutex);
		philosopher->is_left_locked = 0;
		//pthread_mutex_unlock(philosopher->left_fork_mutex);
	}
}

void	destroy_mutex_array(t_mutex *mutex, size_t number_of_philosophers)
{
	size_t	i;

	i = 0;
	while (i < number_of_philosophers)
	{
		pthread_mutex_destroy(&mutex[i]);
		i++;
	}
}

int	destroy_forks_and_last_meal_mutexes(t_table *table)
{
	destroy_mutex_array(table->forks, table->number_of_philosophers);
	destroy_mutex_array(table->last_meal_mutex, table->number_of_philosophers);
	return (0);
}

int	destroy_every_mutex(t_table *table)
{
	destroy_forks_and_last_meal_mutexes(table);
	//destroy_mutex_array(table->is_fork_locked_mutex, table->number_of_philosophers);
	//destroy_mutex_array(table->is_done_mutex, table->number_of_philosophers);
	pthread_mutex_destroy(&table->are_done_mutex);
	pthread_mutex_destroy(&table->is_someone_dead_mutex);
	pthread_mutex_destroy(&table->start_time_mutex);
	return (0);
}

t_mutex	*ft_start_mutex_array(t_table *table/*, t_mutex *mutex*/)
{
	t_mutex	*mutex;
	size_t	i;
	
	mutex = ft_calloc(table->number_of_philosophers, sizeof(t_mutex));
	if (!mutex)
	{
		ft_print_error("Could not allocate memory\n");
		return (NULL);
	}
	i = 0;
	while (i < table->number_of_philosophers)
	{
		if (!ft_start_mutex(mutex[i], mutex, i))
			return (NULL);
		i++;
	}
	return (mutex);
}
