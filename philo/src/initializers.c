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

static t_mutex	*initialize_mutexes(t_table *table)
{
	t_mutex	*forks;
	size_t	i;

	forks = ft_calloc(table->number_of_philosophers, sizeof(t_mutex));
	if (!forks)
		return (NULL);
	i = 0;
	while (i < table->number_of_philosophers)
	{
		if (!ft_start_mutex(forks[i], forks, i))
			return (NULL);
		i++;
	}
	i = table->number_of_philosophers - 1;
	if (!ft_start_mutex(table->are_done_mutex, forks, i))
		return (NULL);
	if (!ft_start_mutex(table->is_someone_dead_mutex, forks, i))//revisar que los mutex se destruyan si no estan inicializados
		return (NULL);
	if (!ft_start_mutex(table->everyone_is_ready_mutex, forks, i))
		return (NULL);
	return (forks);
}

pthread_t	*initialize_threads(t_table *table, t_philos *philos, t_mutex *forks)
{
	int			i;
	pthread_t	*threads;

	threads = ft_calloc(table->number_of_philosophers, sizeof(pthread_t));
	if (!threads)
		return (NULL);
	i = 0;
	while (i < (int)table->number_of_philosophers)
	{
		philos[i] = fill_params(table, forks, i);
		if (pthread_create(&threads[i], NULL, &routine, &philos[i]))
		{
			ft_print_error("Thread couldn't be created\n");
			while (--i > -1)
				pthread_detach(threads[i]);//revisar esto
			while (++i < (int)table->number_of_philosophers)
				pthread_mutex_destroy(&forks[i]);
			pthread_mutex_destroy(&table->are_done_mutex);
			pthread_mutex_destroy(&table->is_someone_dead_mutex);
			pthread_mutex_destroy(&table->everyone_is_ready_mutex);
			return (NULL);
		}
		i++;
	}
	//considerar si renta convertir la variable start_time en un miembro de table
	return (threads);
}

int	initialize_mutex_and_threads(t_table *table, t_philos *philos)
{
	table->forks = initialize_mutexes(table);
	if (!table->forks)
	{
		free_stuff(table, philos, NULL, NULL);
		return (0);
	}
	table->threads = initialize_threads(table, philos, table->forks);
	if (!table->threads)
	{
		free_stuff(table, philos, table->forks, NULL);
		return (0);
	}
	return (1);
}

t_philos	*initialize_philos(t_table *table)
{
	t_philos	*philos;
	size_t		i;

	philos = ft_calloc(table->number_of_philosophers, sizeof(t_philos));
	if (!philos)
		return (NULL);
	i  = 0;
	while (i < table->number_of_philosophers)
	{
		philos[i].table = table;
		i++;
	}
	return (philos);
}
