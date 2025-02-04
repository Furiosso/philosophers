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

static void				join_threads(pthread_t *threads, t_mutex *forks, t_table *table);
static void	check_death(t_table *table, t_philos *philos/*, pthread_t *threads, t_mutex *forks*/);
//static void	detach_threads(t_table *table, t_philos *philos, t_mutex *forks);

int	main(int argc, char **argv)
{
	t_philos	*philos;
	t_table		*table;

	table = check_args(argc, argv);
	if (!table)
		return (1);
	philos = initialize_philos(table);
	if (!philos)
	{
		free(table);
		return (2);
	}
	if (!initialize_mutex_and_threads(table, philos))
		return (3);
	check_death(table, philos/*, threads, forks*/);
	join_threads(table->threads, table->forks, table);
	free_stuff(table, philos, table->forks, table->threads);
}

void	free_stuff(t_table *t, t_philos *ph, t_mutex *f, pthread_t *th)
{
	if (th)
		free(th);
	if (f)
		free(f);
	if (ph)
		free(ph);
	free(t);
}
/*
static void	*routine(void *arg)
{
	t_philos	*philosopher;

	philosopher = (t_philos *)arg;
	if (philosopher->id == philosopher->table->number_of_philosophers)
	{
		pthread_mutex_lock(philosopher->right_fork);
		printf("Philosopher %zu right fork address: %p\n", philosopher->id, philosopher->right_fork);
		pthread_mutex_lock(philosopher->left_fork);
		printf("Philosopher %zu left fork address: %p\n", philosopher->id, philosopher->left_fork);
	}
	else
	{
		pthread_mutex_lock(philosopher->left_fork);
		printf("Philosopher %zu left fork address: %p\n", philosopher->id, philosopher->left_fork);
		pthread_mutex_lock(philosopher->right_fork);
		printf("Philosopher %zu right fork address: %p\n", philosopher->id, philosopher->right_fork);
	}
	//pthread_mutex_lock(philosopher->left_fork);
	//printf("Philosopher %zu left fork address: %p\n", philosopher->id, philosopher->left_fork);
	//pthread_mutex_lock(philosopher->right_fork);
	//printf("Philosopher %zu right fork address: %p\n", philosopher->id, philosopher->right_fork);
	sleep(1);
	if (philosopher->id == philosopher->table->number_of_philosophers)
	{
		pthread_mutex_unlock(philosopher->left_fork);
		pthread_mutex_unlock(philosopher->right_fork);
	}
	else
	{
		pthread_mutex_unlock(philosopher->right_fork);
		pthread_mutex_unlock(philosopher->left_fork);
	}
	//pthread_mutex_unlock(philosopher->left_fork);
	//pthread_mutex_unlock(philosopher->right_fork);
	return (NULL);
}*/

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
	if (pthread_mutex_destroy(&table->is_someone_dead_mutex) != 0)
		return ;
}

static void	check_death(t_table *table, t_philos *philos/*, pthread_t *threads, t_mutex *forks*/)
{
	size_t	i;
	size_t	timer;
	//size_t	are_done;
	size_t	last_meal[4];

	i = 0;
	while (i < 4)
	{
		last_meal[i] = philos[i].start_time;
		i++;
	}
	//printf("table->are_done: %zu table->number_of_philophers: %zu\n", table->are_done, table->number_of_philosophers);
	//are_done = table->are_done;
	i = 0;
	while (!check_mutex(table->are_done_mutex, &table->are_done, table->number_of_philosophers) && !check_if_someone_is_dead(table))//revisar esto
	//while (1)
	{
		timer = get_time();
		if (last_meal[i] != philos[i].last_meal)
		{
			last_meal[i] = philos[i].last_meal;
			//printf("philosopher %zu last meal: %zu\n", philos[i].id, philos[i].last_meal);
			//printf("time to die: %zu\n", table->time_to_die);
		}
		//printf("philosopher %zu last meal: %zu\n", philos[i].id, philos[i].last_meal);
		//printf("philosopher.id: %zu\n", philos[i].id);
		//if (!(philos[i].is_done) && (table->time_to_die <= timer - philos[i].last_meal) || table->are_done == table->number_of_philosophers)
		if (table->time_to_die <= (timer - philos[i].last_meal))
		{
			//printf("timer - last meal: %zu\n", timer - philos[i].last_meal);
			//printf("timer - philos[%zu].last_meal: %zu\n", philos[i].id, timer - philos[i].last_meal);
			//if (table->time_to_die <= timer - philos[i].last_meal)
			//printf("%ld %zu died\n", timer - philos[i].start_time, philos[i].id);
			//detach_threads(table, philos, forks);
			//break ;
			pthread_mutex_lock(&table->is_someone_dead_mutex);
			table->is_someone_dead = 1;
			pthread_mutex_unlock(&table->is_someone_dead_mutex);
			printf("%ld %zu died\n", get_time() - philos[i].start_time, philos[i].id);
			break ;
		}
		{
			//printf("timer - philos[%zu].last_meal: %zu\n", philos[i].id, timer - philos[i].last_meal);
			//if (table->time_to_die <= timer - philos[i].last_meal)
			//printf("%ld %zu died\n", timer - philos[i].start_time, philos[i].id);
			//detach_threads(table, philos, forks);
			//break ;
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
	//printf("is_someone_dead: %d\n", table->is_someone_dead);
	//if (!table->is_someone_dead)
	//	join_threads(threads, forks, table);
}
/*
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
}*/