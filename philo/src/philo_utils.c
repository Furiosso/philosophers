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
			write (2, "Only positive numerical characters allowed\n", 43);
			return (2);
		}
	}
	return (0);
}

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

static int	ft_isnumber(char *str)
{
	int	i;

	i = 0;
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
