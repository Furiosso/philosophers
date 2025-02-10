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
