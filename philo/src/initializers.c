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
	if (!ft_start_mutex(table->is_someone_dead_mutex, forks, i))
		return (NULL);
	return (forks);
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
