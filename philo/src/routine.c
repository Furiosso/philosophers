/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagimeno <dagimeno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 13:52:21 by dagimeno          #+#    #+#             */
/*   Updated: 2025/01/04 20:30:10 by dagimeno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static int	cycle(t_philosophers *philosopher);
long	get_time(void);

void	*routine(void *arg)
{
	t_philosophers	philosopher;
	//struct timeval	last_meal;

	philosopher = *(t_philosophers *)arg;
	//printf("In the thread: %d\n", philosopher.id);
	philosopher.last_meal = get_time();
	//gettimeofday(&last_meal, NULL);
	//printf("%ld last meal\n", last_meal.tv_usec);
	//philosopher.last_meal = last_meal.tv_usec / 1000;
	printf("%ld %d is thinking\n", philosopher.last_meal, philosopher.id);
	if (!philosopher.number_of_times_each_philosopher_must_eat)
	{
		while (1)
			cycle(&philosopher);
	}
	while (philosopher.number_of_times_each_philosopher_must_eat--)
	{
		if (!cycle(&philosopher))
			return (NULL);
	}
	return (NULL);
}

static int	cycle(t_philosophers *philosopher)
{
	long	timer;

	lock_forks(philosopher->left_fork, philosopher->right_fork, philosopher->id);
	timer = get_time();
	/*gettimeofday(&timer, NULL);
	if (timer.tv_usec / 1000 - philosopher->last_meal > philosopher->time_to_die)
	{
		printf ("%ld %d died\n", timer.tv_usec / 1000, philosopher->id);
		unlock_forks(philosopher->left_fork, philosopher->right_fork);
		return (0);
	}*/
	philosopher->last_meal = timer;
	//printf("%ld timer\n", timer.tv_usec);
	printf ("%ld %d is eating\n", timer, philosopher->id);
	usleep(philosopher->time_to_eat * 1000);
	unlock_forks(philosopher->left_fork, philosopher->right_fork);
	timer = get_time();
	//gettimeofday(&timer, NULL);
	//printf("%ld timer\n", timer.tv_usec);
	printf ("%ld %d is sleeping\n", timer, philosopher->id);
	usleep(philosopher->time_to_sleep * 1000);
	timer = get_time();
	//gettimeofday(&timer, NULL);
//	printf("%ld timer\n", timer.tv_usec);
	printf ("%ld %d is thinking\n", timer, philosopher->id);
	return (1);
}

long	get_time(void)
{
	struct timeval	timer;

	gettimeofday(&timer, NULL);
	return (timer.tv_sec * 1000 + timer.tv_usec / 1000);
}
