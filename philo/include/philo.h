/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagimeno <dagimeno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 13:50:56 by dagimeno          #+#    #+#             */
/*   Updated: 2025/01/16 22:10:11 by dagimeno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>
# include <pthread.h>

typedef pthread_mutex_t	t_mutex;

typedef struct s_table
{
	int			is_someone_dead;
	size_t		are_done;
	size_t		everyone_is_ready;
	size_t		number_of_philosophers;
	long		start_time;
	long		time_to_die;
	long		time_to_eat;
	long		time_to_sleep;
	int			*is_fork_locked;
	int			time_to_think;
	//int			*is_done;
	//t_mutex		*is_done_mutex;
	t_mutex		*forks;
	t_mutex		*last_meal_mutex;
	t_mutex		*is_fork_locked_mutex;
	t_mutex		are_done_mutex;
	t_mutex		is_someone_dead_mutex;
	t_mutex		start_time_mutex;
	size_t		number_of_times_each_philosopher_must_eat;
	pthread_t	*threads;
}	t_table;

typedef struct s_philos
{
	size_t	id;
	long	start_time;
	long	last_meal;
	size_t	number_of_philosophers;
	long	time_to_eat;
	long	time_to_sleep;
	long	time_to_think;
	size_t	time_to_start;
	size_t	number_of_times_each_philosopher_must_eat;
	t_mutex	*left_fork;
	t_mutex	*right_fork;
	//t_mutex	*left_fork_mutex;
	//t_mutex	*right_fork_mutex;
	t_mutex	*last_meal_mutex;
	//t_mutex *is_done_mutex;
	//int		*is_left_locked;
	//int		*is_right_locked;
	//int		is_done;
	int		is_left_locked;
	int		is_right_locked;
	t_table	*table;
}	t_philos;

t_table		*check_args(int argc, char **argv);
void		check_death(t_table *table, t_philos *philos);
int			check_if_someone_is_dead(t_table *table);
size_t		check_last_meal(size_t time_to_die, size_t timer, t_philos *philosopher);
int			check_mutex(t_mutex *mutex, size_t variable, size_t number_of_philosophers);
void		cut_the_threads(t_table *table);
int			destroy_every_mutex(t_table *table);
int			destroy_forks_and_last_meal_mutexes(t_table *table);
void		destroy_mutex_array(t_mutex *mutex, size_t number_of_philosophers);
long		get_time(void);
t_philos	fill_params(t_table *table, t_mutex *forks, int i);
int			free_stuff(t_table *t, t_philos *ph, pthread_t *th);
size_t		ft_atol(const char *str);
void		*ft_calloc(size_t count, size_t size);
char		ft_isnumber(char *str);
int			ft_start_mutex(t_mutex mutex, t_mutex *forks, int key);
t_mutex		*ft_start_mutex_array(t_table *table/*, t_mutex *forks*/);
size_t		ft_strlen(const char *str);
int			ft_print_error(char *str);
int			initialize_mutex_and_threads(t_table *table, t_philos *philos);
t_philos	*initialize_philos(t_table *table);
pthread_t	*initialize_threads(t_table *table, t_philos *philos, t_mutex *forks);
//void		join_threads(t_philos *params, int number_of_philosophers);
//void		lock_forks(pthread_mutex_t *left_fork, pthread_mutex_t *right_fork, int id);
//char		lock_forks(t_philos *philosopher);
void		*routine(void *arg);
int			timekeeper(long time, int has_to_check_death, t_table *table);
void		unlock_forks(t_philos *philosopher);
long 		wait_for_everyone_to_be_ready(t_table *table);

#endif