/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_and_param_management.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagimeno <dagimeno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 18:21:11 by dagimeno          #+#    #+#             */
/*   Updated: 2025/02/11 18:21:14 by dagimeno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

t_philo	fill_params(t_table *table, t_mutex *forks, int i)
{
	t_philo	philosopher;

	philosopher.id = i + 1;
	philosopher.right_fork = &forks[i];
	philosopher.left_fork = &forks[i + 1];
	if (philosopher.id == table->num_of_philos)
		philosopher.left_fork = &forks[0];
	philosopher.last_meal_mutex = &table->last_meal_mutex[i];
	philosopher.time_to_eat = table->time_to_eat;
	philosopher.time_to_sleep = table->time_to_sleep;
	philosopher.time_to_think = table->time_to_think;
	if (table->time_to_think < 0)
		philosopher.time_to_think = 0;
	philosopher.table = table;
	philosopher.time_to_start = table->time_to_die / 2;
	if (philosopher.time_to_eat < philosopher.table->time_to_die)
		philosopher.time_to_start = philosopher.time_to_eat / 2;
	philosopher.num_of_cycles = table->num_of_cycles;
	return (philosopher);
}

int	ft_print_error(char *str)
{
	write(2, "Error:\n", 7);
	write(2, str, ft_strlen(str));
	return (0);
}

static t_table	*ft_print_error_and_free(char *str, t_table *table)
{
	ft_print_error(str);
	free(table);
	return (NULL);
}

static t_table	*fill_table(char **argv)
{
	t_table	*table;

	table = ft_calloc(1, sizeof(t_table));
	if (!table)
	{
		ft_print_error("Could not allocate memory\n");
		return (NULL);
	}
	table->num_of_philos = ft_atol(argv[1]);
	table->time_to_die = ft_atol(argv[2]);
	table->time_to_eat = ft_atol(argv[3]);
	table->time_to_sleep = ft_atol(argv[4]);
	if (!table->num_of_philos || !table->time_to_die
		|| !table->time_to_eat || !table->time_to_sleep)
		return (ft_print_error_and_free("Invalid value found\n", table));
	if (argv[5])
	{
		table->num_of_cycles = ft_atol(argv[5]);
		if (!table->num_of_cycles)
			return (ft_print_error_and_free("Invalid value found\n", table));
	}
	table->time_to_think = table->time_to_eat * 2 - table->time_to_sleep;
	return (table);
}

t_table	*check_args(int argc, char **argv)
{
	int		i;

	if (argc > 6 || argc < 5)
	{
		write (2, "Error:\nPlease check the format\n", 31);
		return (NULL);
	}
	i = 0;
	while (argv[++i])
	{
		if (!ft_isnumber(argv[i]))
			return (NULL);
	}
	return (fill_table(argv));
}
