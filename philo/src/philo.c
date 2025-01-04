/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagimeno <dagimeno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 13:52:01 by dagimeno          #+#    #+#             */
/*   Updated: 2025/01/04 18:14:47 by dagimeno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static pthread_mutex_t	*initialize_mutex(int number_of_forks);
static pthread_t		*initialize_threads(char **argv, t_philosophers *philosophers, pthread_mutex_t *forks);
static void				free_stuff(t_philosophers *params, pthread_mutex_t *forks, pthread_t *threads);
static void				join_threads(pthread_t *threads, pthread_mutex_t *forks, int number_of_threads);

int	main(int argc, char **argv)
{
	t_philosophers	*philosophers;
	pthread_t		*threads;
	pthread_mutex_t	*forks;

	if (check_args(argc, argv) > 0)
		return (1);
	philosophers = ft_calloc(ft_atoi(argv[1]) + 1, sizeof(t_philosophers));
	//params = fill_params(argv);
	if (!philosophers)
		return (2);
	forks = initialize_mutex(ft_atoi(argv[1]));
	if (!forks)
	{
		free(philosophers);
		return (4);
	}
	threads = initialize_threads(argv, philosophers, forks);
	if (!threads)
	{
		free_stuff(philosophers, forks, NULL);
		return (4);
	}
	join_threads(threads, forks, ft_atoi(argv[1]));
	free_stuff(philosophers, forks, threads);
}

static void	free_stuff(t_philosophers *philosophers, pthread_mutex_t *forks, pthread_t *threads)
{
	//int	i;
	if (threads)
		free(threads);
	free(forks);
	//i = 0;
	//while (params[i])
	//	free(params[i]);
	free(philosophers);
}

static pthread_mutex_t	*initialize_mutex(int number_of_forks)
{
	pthread_mutex_t	*forks;
	int				i;

	forks = ft_calloc(number_of_forks, sizeof(pthread_mutex_t));
	if (!forks)
		return (NULL);
	i = 0;
	while (i < number_of_forks)
	{
		if (pthread_mutex_init(&forks[i], NULL) != 0)
		{
			free(forks);
			return (NULL);
		}
		i++;
	}
	return (forks);
}

pthread_t	*initialize_threads(char **argv, t_philosophers *philosophers, pthread_mutex_t *forks)
{
	int			i;
	pthread_t	*threads;

	threads = ft_calloc(ft_atoi(argv[1]), sizeof(pthread_t));
	if (!threads)
		return (0);
	i = 0;
	while (i < ft_atoi(argv[1]))
	{
		philosophers[i] = fill_params(argv, forks, i);
		//printf("Before creating thread: %d\n", philosophers[i].id);
		if (pthread_create(&threads[i], NULL, &routine, &philosophers[i]) != 0)
			return (NULL);
		i++;
	}
	return (threads);
}

void	join_threads(pthread_t *threads, pthread_mutex_t *forks, int number_of_threads)
{
	int	i;

	i = 0;
	while (i < number_of_threads)
	{
		if (pthread_join(threads[i++], NULL) != 0)
			break ;
	}
	i = 0;
	while (i < number_of_threads)
	{
		if (pthread_mutex_destroy(&forks[i++]) != 0)
			return ;
	}
}
