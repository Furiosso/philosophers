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

size_t	get_time(void)
{
	struct timeval	timer;

	gettimeofday(&timer, NULL);
	return (timer.tv_sec * 1000 + timer.tv_usec / 1000);
}
/*
long	calculate_time_since_last_meal(philosopher)
{
	
}

void	*check_death(void *arg)
{
	long			timer;
	t_philos	philosopher;

	philosopher = *(t_philos *)arg;
	while (1)
	{
		
		//printf("%d: last meal in death check: %ld\n", philosopher.id, get_time() - philosopher.last_meal);
		timer = get_time() - philosopher.last_meal;
		if (timer >= philosopher.time_to_die)
		{
			printf("%ld %d died\n", timer, philosopher.id);
			if (philosopher.is_locked)
				pthread_mutex_unlock(philosopher.left_fork);
			pthread_detach(*philosopher.thread);
			break ;
		}
	}
	return (NULL);
}*/