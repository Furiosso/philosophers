/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagimeno <dagimeno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 13:51:50 by dagimeno          #+#    #+#             */
/*   Updated: 2025/01/04 13:51:55 by dagimeno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static int	ft_isnumber(char *str);

int	check_args(int argc, char **argv)
{
	int	i;

	if (argc > 6 || argc < 5)
	{
		write (2, "Error:\nPlease check the format\n", 31);
		return (1);
	}
	i = 0;
	while (argv[++i])
	{
		if (!ft_isnumber(argv[i]))
		{
			write (2, "Error:\n", 7);
			write (2, "Only positive numbers allowed\n", 30);
			return (2);
		}
	}
	return (0);
}

static int	ft_isnumber(char *str)
{
	int		i;

	i = 0;
	while (str[i] == ' ')
		i++;
	if (str[i] == '+')
	{
		i++;
		if (!str[i])
			return (0);
	}
	while (str[i])
	{
		if (!ft_isdigit(str[i++]))
			return (0);
	}
	return (1);
}
