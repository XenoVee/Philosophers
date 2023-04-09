/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philosophers.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: rmaes <rmaes@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/13 16:25:51 by rmaes         #+#    #+#                 */
/*   Updated: 2023/04/09 15:22:19 by rmaes         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>

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
	if (t - eat > args->params->tdie)
	{
		pthread_mutex_lock(&args->params->dead_mutex);
		args->params->dead = TRUE;
		pthread_mutex_unlock(&args->params->dead_mutex);
		ft_usleep(1);
		printf("%lu %i has died\n",
			timestamp() - 1 - args->params->start_time, args->philo);
		return (TRUE);
	}
	else
		return (FALSE);
}

void	*threadfunc(void *p)
{
	t_args			*args;
	unsigned int	eat;

	args = p;
	eat = timestamp();
	if (args->philo % 2)
		usleep(5000);
	while (all_alive(args))
	{
		pthread_mutex_lock(&args->fork->mutex);
		check_dead(args, eat);
		message(args, FORK);
		pthread_mutex_lock(&args->fork->next->mutex);
		check_dead(args, eat);
		message(args, FORK);
		message(args, EAT);
		eat = timestamp();
		ft_usleep(args->params->teat);
		pthread_mutex_unlock(&args->fork->mutex);
		pthread_mutex_unlock(&args->fork->next->mutex);
		message(args, SLEEP);
		ft_usleep(args->params->tsleep);
		message(args, THINK);
	}
	return (NULL);
}

int	main(int argc, char **argv)
{
	unsigned int	i;
	pthread_t		thread;
	t_dllist		*forks;
	t_args			**args;
	t_params		params;

	if (parse_input(&params, argc, argv))
		return (1);
	i = 0;
	forks = make_table(params.nphilo);
	cdl_listgetnode(forks, i);
	args = setup_args(params.nphilo, forks, &params);
	while (i < params.nphilo)
	{
		pthread_create(&thread, NULL, &threadfunc, (void *)args[i]);
		i++;
	}
	pthread_join(thread, NULL);
}
