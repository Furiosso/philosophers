/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagimeno <dagimeno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 13:52:01 by dagimeno          #+#    #+#             */
/*   Updated: 2025/01/10 21:41:36 by dagimeno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

//static pthread_mutex_t	*initialize_mutex(int number_of_forks);
//static pthread_t		*initialize_threads(char **argv, t_philos *philos, pthread_mutex_t *forks);
static void	free_stuff(t_table *table, t_philos *params, pthread_mutex_t *forks, pthread_t *threads);
//static void				join_threads(pthread_t *threads, pthread_mutex_t *forks, int number_of_threads);

int	main(int argc, char **argv)
{
	t_philos	*philos;
	t_table		*table;
	//pthread_t		*threads;
	//pthread_mutex_t	*forks;

	table = (t_table *)ft_calloc(1, sizeof(t_table));
	if (!table)
		return (2);
	if (!check_args(argc, argv, table))
	{
		free(table);
		return (3);
	}
	philos = initialize_philos(table);
	if (!philos)
	{
		free_stuff(table, philos, NULL, NULL);
		return (4);
	}
	free_stuff(table, philos, NULL, NULL);
	/*
	forks = initialize_mutex(ft_atoi(argv[1]));
	if (!forks)
	{
		free_stuff(table, philos, NULL, NULL);
		return (4);
	}
	threads = initialize_threads(argv, philos, forks);
	if (!threads)
	{
		free_stuff(table, philos, forks, NULL);
		return (4);
	}
	join_threads(threads, forks, ft_atoi(argv[1]));
	free_stuff(table, philos, forks, threads);*/
}

static void	free_stuff(t_table *table, t_philos *philos, pthread_mutex_t *forks, pthread_t *threads)
{
	//int	i;
	if (threads)
		free(threads);
	if (forks)
		free(forks);
	//i = 0;
	//while (params[i])
	//	free(params[i]);
	free(table);
	free(philos);
}
/*
static pthread_mutex_t	*initialize_mutex(int number_of_forks)
{
	pthread_mutex_t	*forks;
	int				i;

	forks = ft_calloc(number_of_forks, sizeof(pthread_mutex_t));
	if (!forks)
		return (NULL);
	i = 0;
	while (i < number_of_forks)
	{
		if (pthread_mutex_init(&forks[i], NULL) != 0)
		{
			free(forks);
			return (NULL);
		}
		i++;
	}
	return (forks);
}

pthread_t	*initialize_threads(char **argv, t_philos *philos, pthread_mutex_t *forks)
{
	int			i;
	pthread_t	*threads;

	threads = ft_calloc(ft_atoi(argv[1]), sizeof(pthread_t));
	if (!threads)
		return (0);
	i = 0;
	while (i < ft_atoi(argv[1]))
	{
		philos[i] = fill_params(argv, forks, &threads[i], i);
		//printf("Thread address before created: %p\n", &threads[i]);
		//printf("Before creating thread: %d\n", philos[i].id);
		if (philos[i].id % 2 == 0)
			usleep(500);
		if (pthread_create(&threads[i], NULL, &routine, &philos[i]) != 0)
			return (NULL);
		//printf("Thread address after created: %p\n", &threads[i]);
		i++;
	}
	return (threads);
}

void	join_threads(pthread_t *threads, pthread_mutex_t *forks, int number_of_threads)
{
	int	i;

	i = 0;
	while (i < number_of_threads)
	{
		if (pthread_join(threads[i++], NULL) != 0)
			break ;
	}
	i = 0;
	while (i < number_of_threads)
	{
		if (pthread_mutex_destroy(&forks[i++]) != 0)
			return ;
	}
}*/
