/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parsing.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: rmaes <rmaes@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/04 17:42:08 by rmaes         #+#    #+#                 */
/*   Updated: 2023/05/23 14:15:38 by rmaes         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include <stdlib.h>
#include <limits.h>
#include <stdio.h>
#include <unistd.h>

t_dllist	*make_table(int nphilos)
{
	int			i;
	t_dllist	*list;
	t_dlnode	*node;

	i = 0;
	list = cdl_listinit();
	while (i++ < nphilos)
		cdl_listaddback(list, cdl_nodenew(i));
	i = 0;
	node = list->head;
	return (list);
}

t_args	**setup_args(int nphilo, t_dllist *list, t_params *params)
{
	t_args		**args;
	int			i;
	t_dlnode	*node;

	i = 0;
	params->forks = list;
	args = malloc(sizeof(t_args *) * (nphilo + 1));
	args[nphilo] = NULL;
	node = cdl_listgetnode(list, i);
	while (i < nphilo)
	{
		args[i] = malloc(sizeof(t_args));
		args[i]->philo = i + 1;
		args[i]->fork = node;
		node = node->next;
		args[i]->params = params;
		i++;
	}
	write(1, "2\n", 2);
	return (args);
}

static int	setup_neat(t_params *params, int argc, char **argv)
{
	params->neat = 0;
	if (argc == 6)
	{
		params->neat = ft_atoi(argv[5]);
		if (params->neat == 0)
			return (0);
	}
	return (1);
}

int	parse_input(t_params *params, int argc, char **argv)
{
	int				i;

	i = 1;
	if (argc != 5 && argc != 6)
		return (eerror("Wrong number of arguments"));
	while (i < argc)
	{
		if (!isint(argv[i]))
			return (eerror("Invalid argument"));
		i++;
	}
	params->nphilo = ft_atoi(argv[1]);
	params->tdie = ft_atoi(argv[2]);
	params->teat = ft_atoi(argv[3]);
	params->tsleep = ft_atoi(argv[4]);
	params->dead = FALSE;
	pthread_mutex_init(&params->dead_mutex, NULL);
	if (setup_neat(params, argc, argv) == 0)
		return (eerror("Invalid argument"));
	params->finished = 0;
	pthread_mutex_init(&params->fin_mutex, NULL);
	pthread_mutex_init(&params->start_mutex, NULL);
	params->start_time = timestamp();
	return (0);
}
