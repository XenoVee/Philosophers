/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philosophers.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: rmaes <rmaes@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/13 16:25:51 by rmaes         #+#    #+#                 */
/*   Updated: 2023/04/17 13:40:33 by rmaes         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

#include <stdlib.h>

int	grab_fork(t_args *args, t_dlnode *fork, unsigned int eat)
{
	if (args->params->nphilo != 1)
		pthread_mutex_lock(&fork->mutex);
	check_dead(args, eat);
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
	check_dead(args, eat);
	message(args, FORK);
	return (0);
}

t_args	*thread_setup(void *p)
{
	t_args			*args;

	args = p;
	pthread_mutex_lock(&args->params->start_mutex);
	pthread_mutex_unlock(&args->params->start_mutex);
	return (args);
}

void	*threadfunc(void *p)
{
	t_args			*args;
	unsigned int	eat;
	int				i;

	args = thread_setup(p);
	i = 0;
	eat = timestamp();
	if (args->philo % 2)
		usleep(ft_min(5000, args->params->teat * 1000 - 100));
	while (all_alive(args) && !all_finished(args))
	{
		grab_fork(args, args->fork, eat);
		message(args, EAT);
		i++;
		eat = timestamp();
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
// 	atexit(leaks);
// }

static void	finish(pthread_t *thread, t_dllist *forks,
	t_args **args, t_params *params)
{
	unsigned int	i;

	pthread_mutex_unlock(&params->start_mutex);
	i = 0;
	while (i < params->nphilo)
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
	finish(thread, forks, args, &params);
}
