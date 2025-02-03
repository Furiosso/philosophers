/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagimeno <dagimeno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 20:34:08 by dagimeno          #+#    #+#             */
/*   Updated: 2025/01/12 18:23:23 by dagimeno         ###   ########.fr       */
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

size_t	ft_atol(const char *str)
{
	unsigned long long	num;
	char				len;

	while (*str == 32 || (*str > 8 && *str < 14))
		str++;
	if (*str == 43)
		str++;
	num = 0;
	len = 0;
	while (*str > 47 && *str < 58)
	{
		if (++len > 10)
			return (0);
		num = num * 10 + *str - 48;
		str++;
	}
	if (num > 0xffffffff)
		return (0);
	return ((size_t)num);
}

int	ft_isdigit(int c)
{
	if (c < 48 || c > 57)
		return (0);
	return (1);
}

char	ft_isnumber(char *str)
{
	int		i;

	i = 0;
	while (str[i] == ' ' || (*str > 8 && *str < 14))
		i++;
	if (str[i] == '+')
		i++;
	if (!ft_isdigit(str[i]))
	{
		ft_print_error("Only numbers allowed\n");
		return (0);
	}
	return (1);
}

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}