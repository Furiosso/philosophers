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

static void	join_threads(pthread_t *threads, t_table *table);
static void	check_death(t_table *table, t_philos *philos/*, pthread_t *threads, t_mutex *forks*/);
//static void	detach_threads(t_table *table, t_philos *philos, t_mutex *forks);

static void	*one_philo_run(void *arg)
{
	size_t	time_to_die;

	time_to_die = *(size_t *)arg;
	printf("0 1 is thinking\n");
	printf("0 1 has taken a fork\n");
	usleep(time_to_die * 1000);
	printf("%zu 1 died\n", time_to_die);
	return (NULL);
}

static int	execute_one_philosopher(t_table *table)
{
	pthread_t	thread;
	size_t		time_to_die;

	time_to_die = table->time_to_die;
	free(table);
	if (pthread_create(&thread, NULL, &one_philo_run, &time_to_die))
	{
		ft_print_error("Could not create thread\n");
		return (2);
	}
	pthread_join(thread, NULL);
	return (0);
}

int	main(int argc, char **argv)
{
	t_philos	*philos;
	t_table		*table;

	table = check_args(argc, argv);
	if (!table)
		return (1);
	if (table->number_of_philosophers == 1)
		return (execute_one_philosopher(table));
	philos = initialize_philos(table);
	if (!philos)
	{
		free(table);
		return (3);
	}
	if (!initialize_mutex_and_threads(table, philos))
		return (4);
	check_death(table, philos/*, threads, forks*/);
	join_threads(table->threads, table);
	free_stuff(table, philos, table->threads);
}

int	free_stuff(t_table *t, t_philos *ph, pthread_t *th)
{
	/*int	i;

	i = 0;*/
	if (th)
		free(th);
	if (t->forks)
		free(t->forks);
	//if (t->is_fork_locked)
	//	free(t->is_fork_locked);
	//if (t->is_done)
	//	free(t->is_done);
	//if (t->is_done_mutex)
	//	free(t->is_done_mutex);
	if (t->last_meal_mutex)
		free(t->last_meal_mutex);
	//if (t->is_fork_locked_mutex)
	//	free(t->is_fork_locked_mutex);
	if (ph)
		free(ph);
	free(t);
	return (0);
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

static void	join_threads(pthread_t *threads, t_table *table)
{
	size_t	i;

	i = 0;
	while (i < table->number_of_philosophers)
		pthread_join(threads[i++], NULL);
	i = 0;
	destroy_every_mutex(table);
}

static void	check_death(t_table *table, t_philos *philos/*, pthread_t *threads, t_mutex *forks*/)
{
	size_t	i;
	size_t	timer;
	size_t	start_time;
	int		is_someone_dead;
	int		is_someone_done;

	i = 0;
	is_someone_dead = 0;
	is_someone_done = 0;
	start_time = wait_for_everyone_to_be_ready(table);
	usleep(table->time_to_die * 1000);
	while (1)
	{
		pthread_mutex_lock(&table->are_done_mutex);
		if (table->are_done)
			is_someone_done = 1;
		if (table->are_done == table->number_of_philosophers)
		{
			//printf("All philosophers are done\n");
			pthread_mutex_unlock(&table->are_done_mutex);
			break ;
		}
		pthread_mutex_unlock(&table->are_done_mutex);
		timer = get_time();
		pthread_mutex_lock(philos[i].last_meal_mutex);
		if (table->time_to_die <= (timer - philos[i].last_meal))
		{
			//printf("timer - philos.last_meal: %ld\n", timer - philos[i].last_meal);
			is_someone_dead = 1;
		}
		pthread_mutex_unlock(philos[i].last_meal_mutex);
		//pthread_mutex_lock(philos[i].is_done_mutex);
		//is_done = philos[i].is_done;
		//pthread_mutex_unlock(philos[i].is_done_mutex);
		if (timer && is_someone_dead && !is_someone_done)
		{
			//printf("%ld is done: %d\n", philos[i].id, philos[i].is_done);
			pthread_mutex_lock(&table->is_someone_dead_mutex);
			table->is_someone_dead = 1;
			pthread_mutex_unlock(&table->is_someone_dead_mutex);
			printf("%ld %zu died\n", get_time() - start_time, philos[i].id);
			break ;
		}
		i++;
		if (i == table->number_of_philosophers)
			i = 0;
	}
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