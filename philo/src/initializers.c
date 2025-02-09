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
	//size_t	nof;

	//nof = table->number_of_philosophers;
	if (pthread_mutex_init(&table->are_done_mutex, NULL))
	{
		ft_print_error("Could not initialize mutex\n");
		//destroy_mutex_array(table->is_fork_locked_mutex, nof);
		//destroy_mutex_array(table->is_done_mutex, nof);
		return (destroy_forks_and_last_meal_mutexes(table));
	}
	if (pthread_mutex_init(&table->is_someone_dead_mutex, NULL))
	{
		ft_print_error("Could not initialize mutex\n");
		pthread_mutex_destroy(&table->are_done_mutex);
		//destroy_mutex_array(table->is_fork_locked_mutex, nof);
		//destroy_mutex_array(table->is_done_mutex, nof);
		return (destroy_forks_and_last_meal_mutexes(table));
	}
	if (pthread_mutex_init(&table->everyone_is_ready_mutex, NULL))
	{
		ft_print_error("Could not initialize mutex\n");
		pthread_mutex_destroy(&table->are_done_mutex);
		pthread_mutex_destroy(&table->is_someone_dead_mutex);
		//destroy_mutex_array(table->is_fork_locked_mutex, nof);
		//destroy_mutex_array(table->is_done_mutex, nof);
		return (destroy_forks_and_last_meal_mutexes(table));
	}
	return (1);
}

pthread_t	*initialize_threads(t_table *table, t_philos *philos, t_mutex *forks)
{
	int		i;
	pthread_t	*threads;

	threads = ft_calloc(table->number_of_philosophers, sizeof(pthread_t));
	if (!threads)
	{
		ft_print_error("Could not allocate memory\n");
		return (NULL);
	}
	i = 0;
	while ((size_t)i < table->number_of_philosophers)
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

int	initialize_mutex_and_threads(t_table *table, t_philos *philos)
{
	table->forks = ft_start_mutex_array(table);
	//table->is_fork_locked = ft_calloc(table->number_of_philosophers, sizeof(size_t));
	//table->is_done = ft_calloc(table->number_of_philosophers, sizeof(t_mutex));
	if (!table->forks /*|| !table->is_fork_locked !table->is_done*/)
		return (free_stuff(table, philos, NULL));
	table->last_meal_mutex = ft_start_mutex_array(table);
	if (!table->last_meal_mutex)
	{
		destroy_mutex_array(table->forks, table->number_of_philosophers);
		return (free_stuff(table, philos, NULL));
	}
	/*table->is_fork_locked_mutex = ft_start_mutex_array(table);
	if (!table->is_fork_locked_mutex)
	{
		destroy_forks_and_last_meal_mutexes(table);
		return (free_stuff(table, philos, NULL));
	}
	table->is_done_mutex = ft_start_mutex_array(table);
	if (!table->is_done_mutex)
	{
		destroy_forks_and_last_meal_mutexes(table);
		return (free_stuff(table, philos, NULL));
	}*/
	if (!initialize_mutexes(table))
		return (free_stuff(table, philos, NULL));
	table->threads = initialize_threads(table, philos, table->forks);
	if (!table->threads)
	{
		destroy_every_mutex(table);
		return (free_stuff(table, philos, NULL));
	}
	return (1);
}

t_philos	*initialize_philos(t_table *table)
{
	t_philos	*philos;
	size_t		i;

	philos = ft_calloc(table->number_of_philosophers, sizeof(t_philos));
	if (!philos)
	{
		ft_print_error("Could not allocate memory\n");
		return (NULL);
	}
	i  = 0;
	while (i < table->number_of_philosophers)
	{
		philos[i].table = table;
		i++;
	}
	return (philos);
}
