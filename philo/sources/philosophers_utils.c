/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philosophers_utils.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: rmaes <rmaes@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/02 16:21:04 by rmaes         #+#    #+#                 */
/*   Updated: 2023/04/17 13:25:45 by rmaes         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include <stdio.h>
#include <unistd.h>

unsigned long	timestamp(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

void	message(t_args *args, int message)
{
	if (!all_alive(args) || all_finished(args))
	{
		return ;
	}
	if (message == FORK)
		printf("%lu %i has taken a fork\n",
			timestamp() - args->params->start_time, args->philo);
	else if (message == EAT)
	{
		ft_usleep(1);
		printf("%lu %i is eating\n",
			timestamp() - args->params->start_time, args->philo);
	}
	else if (message == SLEEP)
		printf("%lu %i is sleeping\n",
			timestamp() - args->params->start_time, args->philo);
	else if (message == THINK)
		printf("%lu %i is thinking\n",
			timestamp() - args->params->start_time, args->philo);
}

void	ft_usleep(unsigned int t)
{
	unsigned long	start;

	start = timestamp();
	while (timestamp() - start < t)
		usleep(500);
}

int	eerror(char *msg)
{
	printf("Error\n%s\n", msg);
	return (1);
}
