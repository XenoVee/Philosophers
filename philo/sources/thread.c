/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   thread.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: rmaes <rmaes@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/26 12:51:22 by rmaes         #+#    #+#                 */
/*   Updated: 2023/05/26 12:53:28 by rmaes         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

int	grab_fork(t_args *args, t_dlnode *fork)
{
	if (args->params->nphilo != 1)
		pthread_mutex_lock(&fork->mutex);
	message(args, FORK);
	if (args->params->nphilo == 1)
	{
		ft_usleep(args->params->tdie);
		pthread_mutex_lock(&args->params->dead_mutex);
		args->params->dead = TRUE;
		pthread_mutex_unlock(&args->params->dead_mutex);
		return (1);
	}
	pthread_mutex_lock(&fork->next->mutex);
	message(args, FORK);
	return (0);
}

t_args	*thread_seteat(void *p, int mode)
{
	t_args			*args;

	args = p;
	if (mode == 0)
	{
		pthread_mutex_lock(&args->params->start_mutex);
		pthread_mutex_unlock(&args->params->start_mutex);
		thread_seteat(p, 1);
		if (args->philo % 2)
			usleep(ft_min(5000, args->params->teat * 1000 - 100));
		return (args);
	}
	else
	{
		pthread_mutex_lock(&args->fork->eatex);
		args->fork->eat = timestamp();
		pthread_mutex_unlock(&args->fork->eatex);
		return (NULL);
	}
}

void	*threadfunc(void *p)
{
	t_args			*args;
	unsigned int	eat;
	int				i;

	args = thread_seteat(p, 0);
	i = 0;
	eat = timestamp();
	while (all_alive(args->params) && !all_finished(args->params))
	{
		grab_fork(args, args->fork);
		message(args, EAT);
		i++;
		thread_seteat(p, 1);
		if ((unsigned int)i == args->params->neat)
			set_finished(args);
		ft_usleep(args->params->teat);
		pthread_mutex_unlock(&args->fork->mutex);
		pthread_mutex_unlock(&args->fork->next->mutex);
		message(args, SLEEP);
		ft_usleep(args->params->tsleep);
		message(args, THINK);
	}
	return (NULL);
}
