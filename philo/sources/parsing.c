/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parsing.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: rmaes <rmaes@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/04 17:42:08 by rmaes         #+#    #+#                 */
/*   Updated: 2023/04/09 18:32:51 by rmaes         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include <stdlib.h>

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	else
		return (0);
}	

int	isint(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i])
	{
		if (ft_isdigit(str[i]) == 0)
			return (0);
		i++;
	}
	return (1);
}

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
	t_args	**args;
	int		i;

	i = 0;
	args = malloc(sizeof(t_args *) * (nphilo + 1));
	args[nphilo] = NULL;
	while (i < nphilo)
	{
		args[i] = malloc(sizeof(t_args));
		args[i]->philo = i + 1;
		args[i]->fork = cdl_listgetnode(list, i);
		args[i]->params = params;
		i++;
	}
	return (args);
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
			return (eerror("Noninteger argument"));
		i++;
	}
	params->nphilo = ft_atoi(argv[1]);
	params->tdie = ft_atoi(argv[2]);
	params->teat = ft_atoi(argv[3]);
	params->tsleep = ft_atoi(argv[4]);
	params->dead = FALSE;
	pthread_mutex_init(&params->dead_mutex, NULL);
	params->neat = 0;
	if (argc == 6)
		params->neat = ft_atoi(argv[5]);
	params->finished = 0;
	pthread_mutex_init(&params->fin_mutex, NULL);
	params->start_time = timestamp();
	return (0);
}
