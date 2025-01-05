/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   params_management.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagimeno <dagimeno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 13:51:33 by dagimeno          #+#    #+#             */
/*   Updated: 2025/01/04 18:39:51 by dagimeno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

//t_philosophers	fill_params(char **argv, pthread_mutex_t *forks, int i);
t_philosophers	fill_params(char **argv, pthread_mutex_t *forks, pthread_t *thread, int i)
{
	t_philosophers	philosopher;
	int				loops;

	//philosophers = ft_calloc(1, sizeof(t_philosophers));
	//if (!philosophers)
	//	return (NULL);
	philosopher.number_of_philosophers = ft_atoi(argv[1]);
	philosopher.id = i + 1;
	philosopher.thread = thread;
	philosopher.is_locked = 0;
	philosopher.left_fork = &forks[i];
	if (philosopher.id == philosopher.number_of_philosophers)
		philosopher.right_fork = &forks[0];
	else
		philosopher.right_fork = &forks[i + 1];
	philosopher.time_to_die = ft_atoi(argv[2]);
	philosopher.time_to_eat = ft_atoi(argv[3]);
	philosopher.time_to_sleep = ft_atoi(argv[4]);
	if (argv[5])
	{
		loops = ft_atoi(argv[5]);
		philosopher.number_of_times_each_philosopher_must_eat = loops;
	}
	philosopher.start_time = get_time();
	return (philosopher);
}
