/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagimeno <dagimeno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 13:50:56 by dagimeno          #+#    #+#             */
/*   Updated: 2025/01/04 21:30:38 by dagimeno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>
# include <pthread.h>

/*typedef struct s_philo
{
	int		id;
	int		lives;
	long	last_meal;
}	t_philo;*/

typedef struct s_philosophers
{
	//pthread_t		*tphilos;
	//t_philo			*philosopher;
	int				id;
	long			last_meal;
	//pthread_mutex_t	*fmutex;
	//int				forks;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	int				number_of_philosophers;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				number_of_times_each_philosopher_must_eat;
}	t_philosophers;

int			check_args(int argc, char **argv);
t_philosophers	fill_params(char **argv, pthread_mutex_t *forks, int i);
int			ft_atoi(const char *str);
void		*ft_calloc(size_t count, size_t size);
int			ft_isdigit(int c);
long		get_time(void);
//int			initialize_threads(char **argv, t_philosophers **params, pthread_mutex_t *forks);
//void		join_threads(t_philosophers *params, int number_of_philosophers);
void		lock_forks(pthread_mutex_t *left_fork, pthread_mutex_t *right_fork, int id);
void		*routine(void *arg);
void		unlock_forks(pthread_mutex_t *left_fork, pthread_mutex_t *right_fork);

#endif