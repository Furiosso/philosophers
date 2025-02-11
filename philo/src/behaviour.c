/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   behaviour.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagimeno <dagimeno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 18:20:56 by dagimeno          #+#    #+#             */
/*   Updated: 2025/02/11 21:47:35 by dagimeno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <../include/philo.h>

int	sleeping(t_philo *philosopher)
{
	long	timer;

	timer = get_time();
	if (!timer)
		return (0);
	if (!safe_print(4, philosopher->table, philosopher->id))
		return (0);
	if (!timekeeper(philosopher->time_to_sleep, philosopher->table))
		return (0);
	if (check_if_someone_is_dead(philosopher->table))
		return (0);
	return (1);
}

static int	take_forks(t_mutex *firstfork, t_mutex *secondfork, t_philo *philo)
{
	pthread_mutex_lock(firstfork);
	if (check_if_someone_is_dead(philo->table))
	{
		pthread_mutex_unlock(firstfork);
		return (0);
	}
	if (!safe_print(2, philo->table, philo->id))
	{
		pthread_mutex_unlock(firstfork);
		return (0);
	}
	pthread_mutex_lock(secondfork);
	if (check_if_someone_is_dead(philo->table))
	{
		unlock_forks(philo);
		return (0);
	}
	if (!safe_print(2, philo->table, philo->id))
	{
		pthread_mutex_unlock(firstfork);
		return (0);
	}
	return (1);
}

static int	eating(t_philo *philosopher)
{
	long	timer;

	timer = get_time();
	if (!timer)
		return (0);
	pthread_mutex_lock(philosopher->last_meal_mutex);
	philosopher->last_meal = timer;
	pthread_mutex_unlock(philosopher->last_meal_mutex);
	if (check_if_someone_is_dead(philosopher->table))
	{
		unlock_forks(philosopher);
		return (0);
	}
	if (!safe_print(3, philosopher->table, philosopher->id))
	{
		unlock_forks(philosopher);
		return (0);
	}
	if (!timekeeper(philosopher->time_to_eat, philosopher->table))
	{
		unlock_forks(philosopher);
		return (0);
	}
	unlock_forks(philosopher);
	return (1);
}

int	take_forks_and_eat(t_philo *philosopher)
{
	t_mutex	*left_fork;
	t_mutex	*right_fork;

	left_fork = philosopher->left_fork;
	right_fork = philosopher->right_fork;
	if (philosopher->id % 2)
	{
		if (!take_forks(left_fork, right_fork, philosopher))
			return (0);
	}
	else
	{
		if (!take_forks(right_fork, left_fork, philosopher))
			return (0);
	}
	if (check_if_someone_is_dead(philosopher->table))
	{
		unlock_forks(philosopher);
		return (0);
	}
	if (!eating(philosopher))
		return (0);
	return (1);
}
