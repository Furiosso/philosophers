/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initializers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagimeno <dagimeno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 17:54:01 by dagimeno          #+#    #+#             */
/*   Updated: 2025/01/10 21:43:02 by dagimeno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

t_philos	*initialize_philos(t_table *table)
{
	t_philos	*philos;
	size_t		i;

	philos = ft_calloc(table->number_of_philosophers + 1, sizeof(t_philos));
	if (!philos)
		return (NULL);
	i  = 0;
	while (i < table->number_of_philosophers)
	{
		philos[i].table = table;
		i++;
	}
	return (philos);
}
