/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philosophers_utils.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: rmaes <rmaes@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/02 16:21:04 by rmaes         #+#    #+#                 */
/*   Updated: 2023/04/18 14:35:59 by rmaes         ########   odam.nl         */
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

static int	check_message(t_args *args)
{
	pthread_mutex_lock(&args->params->dead_mutex);
	if (args->params->dead == TRUE)
	{
		pthread_mutex_unlock(&args->params->dead_mutex);
		return (1);
	}
	pthread_mutex_lock(&args->params->fin_mutex);
	if (args->params->finished == args->params->nphilo)
	{
		pthread_mutex_unlock(&args->params->dead_mutex);
		pthread_mutex_unlock(&args->params->fin_mutex);
		return (1);
	}
	return (0);
}

void	message(t_args *args, int message)
{
	if (check_message(args) == 1)
		return ;
	if (message == FORK)
		printf("%lu %i has taken a fork\n",
			timestamp() - args->params->start_time, args->philo);
	else if (message == EAT)
		printf("%lu %i is eating\n",
			timestamp() - args->params->start_time, args->philo);
	else if (message == SLEEP)
		printf("%lu %i is sleeping\n",
			timestamp() - args->params->start_time, args->philo);
	else if (message == THINK)
		printf("%lu %i is thinking\n",
			timestamp() - args->params->start_time, args->philo);
	pthread_mutex_unlock(&args->params->fin_mutex);
	pthread_mutex_unlock(&args->params->dead_mutex);
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
