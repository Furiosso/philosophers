/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initializers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagimeno <dagimeno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 17:54:01 by dagimeno          #+#    #+#             */
/*   Updated: 2025/01/10 21:43:02 by dagimeno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	ft_start_mutex(t_mutex mutex, t_mutex *array, int key)
{
	if (pthread_mutex_init(&mutex, NULL))
	{
		while (key > -1)
			pthread_mutex_destroy(&array[key--]);
		free(array);
		return (ft_print_error("Could not initialize mutex\n"));
	}
	return (1);
}

static int	initialize_mutexes(t_table *table)
{
	if (pthread_mutex_init(&table->are_done_mutex, NULL))
	{
		ft_print_error("Could not initialize mutex\n");
		return (destroy_forks_and_last_meal_mutexes(table));
	}
	if (pthread_mutex_init(&table->is_someone_dead_mutex, NULL))
	{
		ft_print_error("Could not initialize mutex\n");
		pthread_mutex_destroy(&table->are_done_mutex);
		return (destroy_forks_and_last_meal_mutexes(table));
	}
	if (pthread_mutex_init(&table->start_time_mutex, NULL))
	{
		ft_print_error("Could not initialize mutex\n");
		pthread_mutex_destroy(&table->are_done_mutex);
		pthread_mutex_destroy(&table->is_someone_dead_mutex);
		return (destroy_forks_and_last_meal_mutexes(table));
	}
	return (1);
}

pthread_t	*init_threads(t_table *table, t_philo *philos, t_mutex *forks)
{
	int			i;
	pthread_t	*threads;

	threads = ft_calloc(table->num_of_philos, sizeof(pthread_t));
	if (!threads)
	{
		ft_print_error("Could not allocate memory\n");
		return (NULL);
	}
	i = 0;
	while ((size_t)i < table->num_of_philos)
	{
		philos[i] = fill_params(table, forks, i);
		if (pthread_create(&threads[i], NULL, &routine, &philos[i]))
		{
			cut_the_threads(table);
			while (--i > -1)
				pthread_join(threads[i], NULL);
			ft_print_error("Thread couldn't be created\n");
			free(threads);
			return (NULL);
		}
		i++;
	}
	return (threads);
}

int	initialize_mutex_and_threads(t_table *table, t_philo *philos)
{
	table->forks = ft_start_mutex_array(table);
	if (!table->forks)
		return (free_stuff(table, philos, NULL));
	table->last_meal_mutex = ft_start_mutex_array(table);
	if (!table->last_meal_mutex)
	{
		destroy_mutex_array(table->forks, table->num_of_philos);
		return (free_stuff(table, philos, NULL));
	}
	if (!initialize_mutexes(table))
		return (free_stuff(table, philos, NULL));
	table->threads = init_threads(table, philos, table->forks);
	if (!table->threads)
	{
		destroy_every_mutex(table);
		return (free_stuff(table, philos, NULL));
	}
	return (1);
}

t_philo	*initialize_philos(t_table *table)
{
	t_philo	*philos;
	size_t	i;

	philos = ft_calloc(table->num_of_philos, sizeof(t_philo));
	if (!philos)
	{
		ft_print_error("Could not allocate memory\n");
		return (NULL);
	}
	i = 0;
	while (i < table->num_of_philos)
	{
		philos[i].table = table;
		i++;
	}
	return (philos);
}
