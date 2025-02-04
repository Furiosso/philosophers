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
	size_t		time_to_die;
	size_t		time_to_eat;
	size_t		time_to_sleep;
	int			time_to_think;
	t_mutex		*forks;
	t_mutex		are_done_mutex;
	t_mutex		is_someone_dead_mutex;
	t_mutex		everyone_is_ready_mutex;
	size_t		number_of_times_each_philosopher_must_eat;
	pthread_t	*threads;
}	t_table;

typedef struct s_philos
{
	//pthread_t		*tphilos;
	//t_philo			*philosopher;
	size_t			id;
	pthread_t		*thread;
	size_t			start_time;
	size_t			last_meal;
	//pthread_mutex_t	*fmutex;
	//int				forks;
	size_t			has_had_first_meal;
	t_mutex	*left_fork;
	t_mutex	*right_fork;
	char			is_left_locked;
	char			is_right_locked;
	char			is_done;
	t_table			*table;
	struct s_philos	*next;
}	t_philos;

t_table		*check_args(int argc, char **argv);
int			check_if_someone_is_dead(t_table *table);
int			check_mutex(t_mutex mutex, size_t *variable, size_t number_of_philosophers);
//void		*check_death(void *arg);
size_t		get_time(void);
t_philos	fill_params(t_table *table, t_mutex *forks, int i);
void		free_stuff(t_table *t, t_philos *ph, t_mutex *f, pthread_t *th);
size_t		ft_atol(const char *str);
void		*ft_calloc(size_t count, size_t size);
char		ft_isnumber(char *str);
int			ft_start_mutex(t_mutex mutex, t_mutex *forks, int key);
size_t		ft_strlen(const char *str);
void		ft_print_error(char *str);
int			initialize_mutex_and_threads(t_table *table, t_philos *philos);
t_philos	*initialize_philos(t_table *table);
pthread_t	*initialize_threads(t_table *table, t_philos *philos, t_mutex *forks);
//void		join_threads(t_philos *params, int number_of_philosophers);
//void		lock_forks(pthread_mutex_t *left_fork, pthread_mutex_t *right_fork, int id);
//char		lock_forks(t_philos *philosopher);
void		*routine(void *arg);
void		unlock_forks(t_philos *philosopher);

#endif