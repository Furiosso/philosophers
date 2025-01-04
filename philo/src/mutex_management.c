/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex_management.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagimeno <dagimeno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 13:51:21 by dagimeno          #+#    #+#             */
/*   Updated: 2025/01/04 21:32:28 by dagimeno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void		lock_forks(pthread_mutex_t *left_fork, pthread_mutex_t *right_fork, int id)
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

void		unlock_forks(pthread_mutex_t *left_fork, pthread_mutex_t *right_fork)
{
	pthread_mutex_unlock(left_fork);
	pthread_mutex_unlock(right_fork);
}
