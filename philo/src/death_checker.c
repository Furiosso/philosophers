
#include "../include/philo.h"

void	check_death(t_table *table, t_philos *philos)
{
	size_t	i;
	long	timer;
	long	start_time;
	int		is_someone_dead;
	int		is_someone_done;

	i = 0;
	is_someone_dead = 0;
	is_someone_done = 0;
	start_time = wait_for_everyone_to_be_ready(table);
	//printf("start time main: %ld\n", start_time);
	//printf("table start time: %ld\n", table->start_time);
	if (!timekeeper(table->time_to_die, 0, NULL))
		return ;
	while (1)
	{
		timer = get_time();
		pthread_mutex_lock(philos[i].last_meal_mutex);
		if (table->time_to_die <= (timer - philos[i].last_meal))
			is_someone_dead = 1;
		pthread_mutex_unlock(philos[i].last_meal_mutex);
		pthread_mutex_lock(&table->are_done_mutex);
		if (table->are_done)
			is_someone_done = 1;
		if (table->are_done == table->number_of_philosophers)
		{
			pthread_mutex_unlock(&table->are_done_mutex);
			break ;
		}
		pthread_mutex_unlock(&table->are_done_mutex);
		if (is_someone_dead && !is_someone_done)
		{
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