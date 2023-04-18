/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   loop_conditions.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: rmaes <rmaes@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/09 18:18:48 by rmaes         #+#    #+#                 */
/*   Updated: 2023/04/18 14:07:52 by rmaes         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include <stdio.h>

int	all_finished(t_args *args)
{
	if (args->params->neat == 0)
		return (0);
	pthread_mutex_lock(&args->params->fin_mutex);
	if (args->params->finished == args->params->nphilo)
	{
		pthread_mutex_unlock(&args->params->fin_mutex);
		return (1);
	}
	pthread_mutex_unlock(&args->params->fin_mutex);
	return (0);
}

void	set_finished(t_args *args)
{
	pthread_mutex_lock(&args->params->fin_mutex);
	args->params->finished++;
	pthread_mutex_unlock(&args->params->fin_mutex);
}

int	all_alive(t_args *args)
{
	int	ret;

	ret = TRUE;
	pthread_mutex_lock(&args->params->dead_mutex);
	if (args->params->dead == TRUE)
		ret = FALSE;
	pthread_mutex_unlock(&args->params->dead_mutex);
	return (ret);
}

int	check_dead(t_args *args, unsigned int eat)
{
	unsigned int	t;

	t = timestamp();
	pthread_mutex_lock(&args->params->dead_mutex);
	if (t - eat > args->params->tdie && args->params->dead == FALSE)
	{
		args->params->dead = TRUE;
		ft_usleep(1);
		printf("%lu %i has died\n",
			timestamp() - args->params->start_time, args->philo);
		pthread_mutex_unlock(&args->params->dead_mutex);
		return (TRUE);
	}
	pthread_mutex_unlock(&args->params->dead_mutex);
	return (FALSE);
}
