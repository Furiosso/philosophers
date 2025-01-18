/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagimeno <dagimeno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 13:52:01 by dagimeno          #+#    #+#             */
/*   Updated: 2025/01/16 22:12:00 by dagimeno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static t_mutex	*initialize_mutex(int number_of_forks, t_mutex *are_done_mutex);
static pthread_t		*initialize_threads(t_table *table, t_philos *philos, t_mutex *forks);
static void	free_stuff(t_table *table, t_philos *params, t_mutex *forks, pthread_t *threads);
static void				join_threads(pthread_t *threads, t_mutex *forks, t_table *table);
static void	check_death(t_table *table, t_philos *philos, pthread_t *threads, t_mutex *forks);
static void	detach_threads(t_table *table, t_philos *philos, t_mutex *forks);

int	main(int argc, char **argv)
{
	t_philos	*philos;
	t_table		*table;
	pthread_t	*threads;
	t_mutex		*forks;

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
		free(table);
		return (4);
	}
	forks = initialize_mutex(table->number_of_philosophers, &table->are_done_mutex);
	if (!forks)
	{
		free_stuff(table, philos, NULL, NULL);
		return (4);
	}
	threads = initialize_threads(table, philos, forks);
	if (!threads)
	{
		free_stuff(table, philos, forks, NULL);
		return (4);
	}
	check_death(table, philos, threads, forks);
	free_stuff(table, philos, forks, threads);
	pthread_exit(0);
}

static void	free_stuff(t_table *table, t_philos *philos, t_mutex *forks, pthread_t *threads)
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

static t_mutex	*initialize_mutex(int number_of_forks, t_mutex *are_done_mutex)
{
	t_mutex	*forks;
	int		i;

	forks = ft_calloc(number_of_forks, sizeof(t_mutex));
	if (!forks)
		return (NULL);
	i = 0;
	while (i < number_of_forks)
	{
		if (pthread_mutex_init(&forks[i], NULL) != 0)
		{
			while (i >= 0)
				pthread_mutex_destroy(&forks[i--]);
			free(forks);
			return (NULL);
		}
		i++;
	}
	if (pthread_mutex_init(are_done_mutex, NULL) != 0)
	{
		while (i >= 0)
			pthread_mutex_destroy(&forks[i--]);
		free(forks);
		return (NULL);
	}
	return (forks);
}

pthread_t	*initialize_threads(t_table *table, t_philos *philos, t_mutex *forks)
{
	size_t		i;
	pthread_t	*threads;

	threads = ft_calloc(table->number_of_philosophers, sizeof(pthread_t));
	if (!threads)
		return (0);
	table->threads = threads;
	i = 0;
	while (i < table->number_of_philosophers)
	{
		philos[i] = fill_params(table, forks, i);
		//printf("Thread address before created: %p\n", &threads[i]);
		//printf("Before creating thread: %d\n", philos[i].id);
		if (philos[i].id % 2 == 0)
			usleep(500);
		if (pthread_create(&threads[i], NULL, &routine, &philos[i]) != 0)
		{
			while (i > 0)
				pthread_detach(threads[i--]);
			pthread_detach(threads[i]);
			i = 0;
			while (i < table->number_of_philosophers)
			{
				if (pthread_mutex_destroy(&forks[i++]) != 0)
					return (NULL);
			}
			if (pthread_mutex_destroy(&table->are_done_mutex) != 0)
				return (NULL);
			return (NULL);
		}
		//printf("Thread address after created: %p\n", &threads[i]);
		i++;
	}
	return (threads);
}

static void	join_threads(pthread_t *threads, t_mutex *forks, t_table *table)
{
	size_t	i;

	i = 0;
	while (i < table->number_of_philosophers)
	{
		if (pthread_join(threads[i++], NULL) != 0)
			break ;
	}
	i = 0;
	while (i < table->number_of_philosophers)
	{
		if (pthread_mutex_destroy(&forks[i++]) != 0)
			return ;
	}
	if (pthread_mutex_destroy(&table->are_done_mutex) != 0)
		return ;
}

 static void	check_death(t_table *table, t_philos *philos, pthread_t *threads, t_mutex *forks)
{
	size_t	i;
	size_t	timer;
	//size_t	are_done;
	//size_t	last_meal[4];

	i = 0;
	/*while (i < 4)
	{
		last_meal[i] = philos[i].start_time;
		i++;
	}
	printf("table->are_done: %zu table->number_of_philophers: %zu\n", table->are_done, table->number_of_philosophers);*/
	//are_done = table->are_done;
	while (table->are_done < table->number_of_philosophers)
	//while (1)
	{
		timer = get_time();
		/*if (last_meal[i] != philos[i].last_meal)
		{
			last_meal[i] = philos[i].last_meal;
			printf("philosopher %zu last meal: %zu\n", philos[i].id, philos[i].last_meal);
			printf("time to die: %zu\n", table->time_to_die);
		}*/
		//printf("philosopher %zu last meal: %zu\n", philos[i].id, philos[i].last_meal);
		//printf("philosopher.id: %zu\n", philos[i].id);
		if (!(philos[i].is_done) && (table->time_to_die <= timer - philos[i].last_meal) /*|| table->are_done == table->number_of_philosophers*/)
		{
			//printf("timer - philos[%zu].last_meal: %zu\n", philos[i].id, timer - philos[i].last_meal);
			//if (table->time_to_die <= timer - philos[i].last_meal)
			printf("%ld %zu died\n", timer - philos[i].start_time, philos[i].id);
			detach_threads(table, philos, forks);
			break ;
		}
		i++;
		if (i == table->number_of_philosophers)
			i = 0;
		//printf("table->are_done: %zu\n", table->are_done);
		//printf("timer when bucle ends: %zu\n", get_time() - philos[i - 1].start_time);
		/*if (are_done != table->are_done)
		{
			are_done = table->are_done;
			printf("table->are_done: %zu\n", table->are_done);
		}*/
	}
	printf("is_someone_dead: %d\n", table->is_someone_dead);
	if (!table->is_someone_dead)
		join_threads(threads, forks, table);
}

static void	detach_threads(t_table *table, t_philos *philos, t_mutex *forks)
{
	size_t	i;

	i = 0;
	philos->table->is_someone_dead = 1;
	while (i < table->number_of_philosophers)
	{
		//printf("left fork: %d | right fork: %d\n", philos[i].is_left_locked, philos[i].is_right_locked);
		//if (philos[i].is_left_locked)
		//	pthread_mutex_unlock(philos[i].left_fork);
		//if (philos[i].is_right_locked)
		//	pthread_mutex_unlock(philos[i].right_fork);
		pthread_detach(table->threads[i++]);
	}
	i = 0;
	while (i < table->number_of_philosophers)
	{
		if (pthread_mutex_destroy(&forks[i++]) != 0)
			return ;
	}
	if (pthread_mutex_destroy(&table->are_done_mutex) != 0)
		return ;
}