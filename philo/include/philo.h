/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagimeno <dagimeno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 13:50:56 by dagimeno          #+#    #+#             */
/*   Updated: 2025/02/11 19:40:31 by dagimeno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>
# include <pthread.h>

# define RS	"\033[0m"
# define R	"\033[31m"
# define G	"\033[32m"
# define Y	"\033[33m"
# define M	"\033[35m"
# define C	"\033[36m"

typedef pthread_mutex_t	t_mutex;

typedef struct s_table
{
	int			is_someone_dead;
	size_t		are_done;
	size_t		everyone_is_ready;
	size_t		num_of_philos;
	long		start;
	long		time_to_die;
	long		time_to_eat;
	long		time_to_sleep;
	long		time_to_think;
	t_mutex		*forks;
	t_mutex		*last_meal_mutex;
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
	long	last_meal;
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
int			destroy_every_mutex(t_table *table, int key);
void		destroy_mutex_array(t_mutex *mutex, size_t num_of_philos);
long		get_time(void);
t_philo		fill_params(t_table *table, t_mutex *forks, int i);
int			free_stuff(t_table *t, t_philo *ph, pthread_t *th);
size_t		ft_atol(const char *str);
void		*ft_calloc(size_t count, size_t size);
char		ft_isnumber(char *str);
t_mutex		*ft_start_mutex_array(t_table *table);
size_t		ft_strlen(const char *str);
int			ft_print_error(char *str);
int			initialize_mutex_and_threads(t_table *table, t_philo *philos);
t_philo		*initialize_philos(t_table *table);
void		*routine(void *arg);
int			safe_print(int behaviour, t_table *table, size_t id);
int			sleeping(t_philo *philosopher);
int			take_forks_and_eat(t_philo *philosopher);
void		unlock_forks(t_philo *philosopher);
long		wait_for_everyone_to_be_ready(t_table *table);

#endif