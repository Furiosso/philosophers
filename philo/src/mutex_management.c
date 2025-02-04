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

int	ft_start_mutex(t_mutex mutex, t_mutex *forks, int key)
{
	if (pthread_mutex_init(&mutex, NULL))
	{
		ft_print_error("Could not initialize mutex\n");
		while (key > -1)
			pthread_mutex_destroy(&forks[key--]);
		free(forks);
		return (0);
	}
	return (1);
}

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
