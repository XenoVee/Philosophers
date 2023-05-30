/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philosophers.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: rmaes <rmaes@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/13 16:25:51 by rmaes         #+#    #+#                 */
/*   Updated: 2023/05/30 16:36:09 by rmaes         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include <stdlib.h>

static void	finish(pthread_t *thread, t_dllist *forks,
	t_args **args, unsigned int k)
{
	unsigned int	i;
	t_params		*params;

	params = args[0]->params;
	pthread_mutex_unlock(&params->start_mutex);
	i = 0;
	while (i < k + 1)
	{
		pthread_join(thread[i], NULL);
		i++;
	}
	i = 0;
	while (args[i])
	{
		free(args[i]);
		i++;
	}
	pthread_mutex_destroy(&params->fin_mutex);
	pthread_mutex_destroy(&params->start_mutex);
	pthread_mutex_destroy(&params->dead_mutex);
	free (thread);
	cdl_listclear(forks);
	free (args);
}

static void	free_args(t_args **args, int f)
{
	int	i;

	i = 0;
	while (i <= f)
	{
		free (args[i]);
		i++;
	}
	free (args);
}

static void	mainlen(t_args **args, pthread_t *thread)
{
	unsigned int	i;

	i = 0;
	pthread_mutex_lock(&args[0]->params->start_mutex);
	while (i < args[0]->params->nphilo && args[0]->params->dead == 0)
	{
		if (pthread_create(&thread[i], NULL, &threadfunc, (void *)args[i]) != 0
			&& args[0]->params->dead == 0)
		{
			args[0]->params->dead = 1;
			eerror("thread creation failed");
		}
		i++;
	}
	pthread_create(&thread[i], NULL, &reaperfunc, args[0]->params);
	finish(thread, args[0]->params->forks, args, i);
}

void	leaks(void)
{
	system("leaks -q philo");
}

int	main(int argc, char **argv)
{
	pthread_t		*thread;
	t_dllist		*forks;
	t_args			**args;
	t_params		params;

	atexit(leaks);
	if (parse_input(&params, argc, argv))
		return (1);
	forks = make_table(params.nphilo);
	if (forks == NULL)
		return (1);
	args = setup_args(params.nphilo, forks, &params);
	if (args == NULL)
	{
		cdl_listclear(forks);
		return (1);
	}
	thread = malloc((params.nphilo + 1) * sizeof(pthread_t *));
	if (thread == NULL)
	{
		cdl_listclear(forks);
		free_args(args, params.nphilo);
		return (1);
	}
	mainlen(args, thread);
}
