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

# define RSET		"\033[0m"
# define RED		"\033[31m"
# define GREEN		"\033[32m"
# define YELLOW		"\033[33m"
# define MAGENTA	"\033[35m"
# define CYAN		"\033[36m"

typedef pthread_mutex_t	t_mutex;

typedef struct s_table
{
	int			is_someone_dead;
	size_t		are_done;
	size_t		everyone_is_ready;
	size_t		num_of_philos;
	long		start_time;
	long		time_to_die;
	long		time_to_eat;
	long		time_to_sleep;
	int			*is_fork_locked;
	long		time_to_think;
	t_mutex		*forks;
	t_mutex		*last_meal_mutex;
	t_mutex		*is_fork_locked_mutex;
	t_mutex		print_mutex;
	t_mutex		are_done_mutex;
	t_mutex		is_someone_dead_mutex;
	t_mutex		start_time_mutex;
	size_t		num_of_cycles;
	pthread_t	*threads;
}	t_table;

typedef struct s_philo
{
	size_t	id;
	long	start_time;
	long	last_meal;
	size_t	num_of_philos;
	long	time_to_eat;
	long	time_to_sleep;
	long	time_to_think;
	size_t	time_to_start;
	size_t	num_of_cycles;
	t_mutex	*left_fork;
	t_mutex	*right_fork;
	t_mutex	*last_meal_mutex;
	t_table	*table;
}	t_philo;

t_table		*check_args(int argc, char **argv);
void		check_death(t_table *table, t_philo *philos);
int			check_if_someone_is_dead(t_table *table);
void		cut_the_threads(t_table *table);
int			destroy_every_mutex(t_table *table, int key);
int			destroy_forks_and_last_meal_mutexes(t_table *table);
void		destroy_mutex_array(t_mutex *mutex, size_t num_of_philos);
int			eating(t_philo *philosopher);
long		get_time(void);
t_philo		fill_params(t_table *table, t_mutex *forks, int i);
int			free_stuff(t_table *t, t_philo *ph, pthread_t *th);
size_t		ft_atol(const char *str);
void		*ft_calloc(size_t count, size_t size);
char		ft_isnumber(char *str);
int			ft_start_mutex(t_mutex *mutex, t_mutex *forks, int key);
t_mutex		*ft_start_mutex_array(t_table *table);
size_t		ft_strlen(const char *str);
int			ft_print_error(char *str);
int			initialize_mutex_and_threads(t_table *table, t_philo *philos);
t_philo		*initialize_philos(t_table *table);
pthread_t	*init_threads(t_table *table, t_philo *philos, t_mutex *forks);
void		*routine(void *arg);
int			safe_print(int behaviour, t_table *table, size_t id);
int			sleeping(t_philo *philosopher);
int			take_forks(t_mutex *firstfork, t_mutex *secondfork, t_philo *philo);
int			take_forks_and_eat(t_philo *philosopher);
int			timekeeper(long time, t_table *table);
void		unlock_forks(t_philo *philosopher);
long		wait_for_everyone_to_be_ready(t_table *table);

#endif