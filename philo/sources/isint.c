/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   isint.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: rmaes <rmaes@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/13 14:42:41 by rmaes         #+#    #+#                 */
/*   Updated: 2023/04/18 14:22:18 by rmaes         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include <limits.h>

int	ft_digitcount(long int n)
{
	int	i;

	i = 0;
	while (n != 0 || i == 0)
	{
		n = n / 10;
		i++;
	}
	return (i);
}

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	else
		return (0);
}	

int	max_check(const char *str)
{
	int	i;
	int	ret;

	i = 0;
	ret = 1;
	while (ft_isdigit(str[i]))
		i++;
	if (i > 10)
		return (-1);
	else if (i == 10)
	{
		if (ft_strcmp(str, "4294967295") < 0)
			return (-1);
	}
	return (ret);
}

unsigned int	ft_strlen( char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	isint(char *str)
{
	int	i;

	i = 0;
	if (ft_strlen(str) == 0 || ft_atoi(str) == 0)
		return (0);
	if (str[i] == '-')
		return (0);
	if (str[i] == '+')
		i++;
	while (str[i])
	{
		if (ft_isdigit(str[i]) == 0)
			return (0);
		i++;
	}
	if (max_check(str) == -1)
		return (0);
	return (1);
}
