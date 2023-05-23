/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   reaper.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: rmaes <rmaes@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/19 14:39:35 by rmaes         #+#    #+#                 */
/*   Updated: 2023/05/23 14:37:46 by rmaes         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include <stdio.h>

void	*reaperfunc(void *p)
{
	t_params	*params;
	t_dlnode	*node;

	params = p;
	node = params->forks->head;
	ft_usleep(params->tdie);
	while (all_alive(params) && !all_finished(params))
	{
		pthread_mutex_lock(&node->eatex);
		if (timestamp() - node->eat > params->tdie)
		{
			pthread_mutex_lock(&params->dead_mutex);
			params->dead = TRUE;
			printf("%lu %i has died\n",
				timestamp() - params->start_time, node->n);
			pthread_mutex_unlock(&params->dead_mutex);
		}
		pthread_mutex_unlock(&node->eatex);
		node = node->next;
	}
	return (NULL);
}
