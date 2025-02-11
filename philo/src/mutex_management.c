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
	int	result;

	result = 0;
	pthread_mutex_lock(&table->is_someone_dead_mutex);
	if (table->is_someone_dead)
		result = 1;
	pthread_mutex_unlock(&table->is_someone_dead_mutex);
	return (result);
}

void	unlock_forks(t_philo *philosopher)
{
	if (philosopher->id % 2)
	{
		pthread_mutex_unlock(philosopher->right_fork);
		pthread_mutex_unlock(philosopher->left_fork);
	}
	else
	{
		pthread_mutex_unlock(philosopher->left_fork);
		pthread_mutex_unlock(philosopher->right_fork);
	}
}

void	destroy_mutex_array(t_mutex *mutex, size_t num_of_philos)
{
	size_t	i;

	i = 0;
	while (i < num_of_philos)
	{
		pthread_mutex_destroy(&mutex[i]);
		i++;
	}
}

int	destroy_forks_and_last_meal_mutexes(t_table *table)
{
	destroy_mutex_array(table->forks, table->num_of_philos);
	destroy_mutex_array(table->last_meal_mutex, table->num_of_philos);
	return (0);
}

int	destroy_every_mutex(t_table *table, int key)
{
	if (key > 0)
		destroy_forks_and_last_meal_mutexes(table);
	if (key > 1)
		pthread_mutex_destroy(&table->are_done_mutex);
	if (key > 2)
		pthread_mutex_destroy(&table->is_someone_dead_mutex);
	if (key > 3)
		pthread_mutex_destroy(&table->start_time_mutex);
	if (key > 4)
		pthread_mutex_destroy(&table->print_mutex);
	return (0);
}

t_mutex	*ft_start_mutex_array(t_table *table)
{
	t_mutex	*mutex;
	size_t	i;

	mutex = ft_calloc(table->num_of_philos, sizeof(t_mutex));
	if (!mutex)
	{
		ft_print_error("Could not allocate memory\n");
		return (NULL);
	}
	i = 0;
	while (i < table->num_of_philos)
	{
		if (!ft_start_mutex(&mutex[i], mutex, i))
			return (NULL);
		i++;
	}
	return (mutex);
}
