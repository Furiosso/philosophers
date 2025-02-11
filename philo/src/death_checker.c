
#include "../include/philo.h"

int	check_if_someone_is_dead(t_table *table)
{
	int	result;

	result = 0;
	pthread_mutex_lock(&table->is_someone_dead_mutex);
	if (table->is_someone_dead)
		result = 1;
	pthread_mutex_unlock(&table->is_someone_dead_mutex);
	return (result);
}

static int	check_if_someone_died(t_philo *philosopher, t_table *table)
{
	long	timer;
	int		result;

	result = 0;
	timer = get_time();
	if (!timer)
		return (-1);
	pthread_mutex_lock(philosopher->last_meal_mutex);
	if (table->time_to_die <= (timer - philosopher->last_meal))
		result = 1;
	pthread_mutex_unlock(philosopher->last_meal_mutex);
	return (result);
}

static int	check_if_philos_are_done(t_table *table)
{
	int	result;

	result = 0;
	pthread_mutex_lock(&table->are_done_mutex);
	if (table->are_done)
		result = 1;
	if (table->are_done == table->num_of_philos)
	{
		result = 2;
	}
	pthread_mutex_unlock(&table->are_done_mutex);
	return (result);
}

static void	finish_loop(t_philo *philo, t_table *table)
{
	pthread_mutex_lock(&table->is_someone_dead_mutex);
	table->is_someone_dead = 1;
	pthread_mutex_unlock(&table->is_someone_dead_mutex);
	safe_print(0, table, philo->id);
}

void	check_death(t_table *table, t_philo *philos)
{
	size_t	i;
	int		is_someone_dead;
	int		is_someone_done;

	i = 0;
	is_someone_dead = 0;
	is_someone_done = 0;
	wait_for_everyone_to_be_ready(table);
	usleep(table->time_to_die * 1000);
	while (1)
	{
		is_someone_dead = check_if_someone_died(&philos[i], table);
		is_someone_done = check_if_philos_are_done(table);
		if (is_someone_dead == -1 || is_someone_done == 2)
			return ;
		if (is_someone_dead && !is_someone_done)
		{
			finish_loop(&philos[i], table);
			return ;
		}
		i++;
		if (i == table->num_of_philos)
			i = 0;
	}
}
