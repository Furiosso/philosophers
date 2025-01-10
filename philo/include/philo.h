/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagimeno <dagimeno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 13:50:56 by dagimeno          #+#    #+#             */
/*   Updated: 2025/01/10 21:36:50 by dagimeno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>
# include <pthread.h>

typedef struct s_table
{
	char	*is_someone_dead;
	size_t	number_of_philosophers;
	size_t	time_to_die;
	size_t	time_to_eat;
	size_t	time_to_sleep;
	size_t	number_of_times_each_philosopher_must_eat;
}	t_table;

typedef struct s_philos
{
	//pthread_t		*tphilos;
	//t_philo			*philosopher;
	int				id;
	pthread_t		*thread;
	long			start_time;
	long			last_meal;
	//pthread_mutex_t	*fmutex;
	//int				forks;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	char			is_locked;
	t_table			*table;
}	t_philos;

char		check_args(int argc, char **argv, t_table *table);
//void		*check_death(void *arg);
long		get_time(void);
t_philos	fill_params(char **argv, pthread_mutex_t *forks, pthread_t *thread, int i);
size_t			ft_atol(const char *str);
void		*ft_calloc(size_t count, size_t size);
char		ft_isnumber(char *str);
long		get_time(void);
t_philos  *initialize_philos(t_table *table);
//int			initialize_threads(char **argv, t_philos **params, pthread_mutex_t *forks);
//void		join_threads(t_philos *params, int number_of_philosophers);
void		lock_forks(pthread_mutex_t *left_fork, pthread_mutex_t *right_fork, int id);
//char		lock_forks(t_philos *philosopher);
void		*routine(void *arg);
void		unlock_forks(pthread_mutex_t *left_fork, pthread_mutex_t *right_fork);

#endif