/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_check_management.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagimeno <dagimeno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 13:51:50 by dagimeno          #+#    #+#             */
/*   Updated: 2025/01/10 21:34:09 by dagimeno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

char	fill_table(t_table *table, char **argv);

char	check_args(int argc, char **argv, t_table *table)
{
	int	i;

	if (argc > 6 || argc < 5)
	{
		write (2, "Error:\nPlease check the format\n", 31);
		return (0);
	}
	i = 0;
	while (argv[++i])
	{
		if (!ft_isnumber(argv[i]))
		{
			write (2, "Error:\n", 7);
			write (2, "Only positive numbers allowed\n", 30);
			return (0);
		}
	}
	if (fill_table(table, argv) == 0)
	{
		write(2, "Error\n", 7);
		write (2, "Invalid value found\n", 20);
		return (0);
	}
	return (1);
}

char	fill_table(t_table *table, char **argv)
{
	table->number_of_philosophers = ft_atol(argv[1]);
	table->time_to_die = ft_atol(argv[2]);
	table->time_to_eat = ft_atol(argv[3]);
	table->time_to_sleep = ft_atol(argv[4]);
	if (!table->number_of_philosophers || !table->time_to_die
		|| !table->time_to_eat || !table->time_to_sleep)
		return (0);
	if (argv[5])
	{
		table->number_of_times_each_philosopher_must_eat = ft_atol(argv[5]);
		if (!table->number_of_times_each_philosopher_must_eat)
			return (0);
	}
	return (1);
}
