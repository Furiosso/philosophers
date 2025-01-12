/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   params_management.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagimeno <dagimeno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 13:51:33 by dagimeno          #+#    #+#             */
/*   Updated: 2025/01/13 00:11:50 by dagimeno         ###   ########.fr       */
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
	philosopher.table = table;
	philosopher.start_time = get_time();
	philosopher.last_meal = philosopher.start_time;
	//philosopher.last_meal = 0;
	return (philosopher);
}
