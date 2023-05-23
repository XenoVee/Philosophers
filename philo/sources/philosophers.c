/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philosophers.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: rmaes <rmaes@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/13 16:25:51 by rmaes         #+#    #+#                 */
/*   Updated: 2023/05/23 14:59:16 by rmaes         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <limits.h>
#include <stdlib.h>

int	grab_fork(t_args *args, t_dlnode *fork)
{
	if (args->params->nphilo != 1)
		pthread_mutex_lock(&fork->mutex);
	message(args, FORK);
	if (args->params->nphilo == 1)
	{
		ft_usleep(args->params->tdie);
		printf("%lu %i has died\n",
			timestamp() - 1 - args->params->start_time, args->philo);
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

// void	leaks(void)
// {
// 	system("leaks -q philo");
	// atexit(leaks);
// }

static void	finish(pthread_t *thread, t_dllist *forks,
	t_args **args, int k)
{
	unsigned int	i;
	t_params		*params;

	params = args[0]->params;
	pthread_mutex_unlock(&params->start_mutex);
	i = 0;
	while (i < (unsigned int)k)
	{
		pthread_join(thread[i], NULL);
		free(args[i]);
		i++;
	}
	free (thread);
	cdl_listclear(forks);
	free (args);
}

int	main(int argc, char **argv)
{
	unsigned int	i;
	pthread_t		*thread;
	t_dllist		*forks;
	t_args			**args;
	t_params		params;

	if (parse_input(&params, argc, argv))
		return (1);
	i = 0;
	forks = make_table(params.nphilo);
	args = setup_args(params.nphilo, forks, &params);
	thread = malloc((params.nphilo) * sizeof(pthread_t *));
	pthread_mutex_lock(&params.start_mutex);
	while (i < params.nphilo)
	{
		if (pthread_create(&thread[i], NULL, &threadfunc, (void *)args[i]) != 0
			&& params.dead == 0)
		{
			params.dead = 1;
			eerror("thread creation failed");
		}
		i++;
	}
	pthread_create(&thread[i], NULL, &reaperfunc, &params);
	finish(thread, forks, args, i);
}
