/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagimeno <dagimeno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 20:34:08 by dagimeno          #+#    #+#             */
/*   Updated: 2025/01/08 20:34:15 by dagimeno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*ptr;
	size_t	i;

	if (((double) count > (double)((size_t) 0xffffffffffffffff) / size) ||
			(((double) size > (double)((size_t) 0xffffffffffffffff) / count)))
		return (NULL);
	i = 0;
	ptr = malloc(count * size);
	if (!ptr)
		return (NULL);
	while (i < count * size)
		*((unsigned char *)ptr + i++) = 0;
	return ((void *)ptr);
}

int	ft_atoi(const char *str)
{
	int		num;
	char	odd;

	num = 0;
	odd = 0;
	while (*str == 32 || (*str > 8 && *str < 14))
		str++;
	if (*str == 45 || *str == 43)
	{
		if (*str == 45)
			odd = 1;
		str++;
	}
	while (*str > 47 && *str < 58)
	{
		num = num * 10 + *str - 48;
		str++;
	}
	if (odd)
		num = -num;
	return (num);
}

int	ft_isdigit(int c)
{
	if (c < 48 || c > 57)
		return (0);
	return (1);
}
