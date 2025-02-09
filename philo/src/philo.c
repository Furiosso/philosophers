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

static void	*one_philo_run(void *arg)
{
	size_t	time_to_die;

	time_to_die = *(size_t *)arg;
	printf("0 1 is thinking\n");
	printf("0 1 has taken a fork\n");
	if (!timekeeper(time_to_die, 0, NULL))
		return (NULL);
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
	t_philo	*philos;
	t_table	*table;

	table = check_args(argc, argv);
	if (!table)
		return (1);
	if (table->num_of_philos == 1)
		return (execute_one_philosopher(table));
	philos = initialize_philos(table);
	if (!philos)
	{
		free(table);
		return (3);
	}
	if (!initialize_mutex_and_threads(table, philos))
		return (4);
	check_death(table, philos);
	join_threads(table->threads, table);
	free_stuff(table, philos, table->threads);
}

int	free_stuff(t_table *t, t_philo *ph, pthread_t *th)
{
	if (th)
		free(th);
	if (t->forks)
		free(t->forks);
	if (t->last_meal_mutex)
		free(t->last_meal_mutex);
	if (ph)
		free(ph);
	free(t);
	return (0);
}

static void	join_threads(pthread_t *threads, t_table *table)
{
	size_t	i;

	i = 0;
	while (i < table->num_of_philos)
		pthread_join(threads[i++], NULL);
	i = 0;
	destroy_every_mutex(table);
}
