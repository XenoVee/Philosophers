/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   loop_conditions.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: rmaes <rmaes@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/09 18:18:48 by rmaes         #+#    #+#                 */
/*   Updated: 2023/05/19 15:02:04 by rmaes         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include <stdio.h>

int	all_finished(t_params *params)
{
	if (params->neat == 0)
		return (0);
	pthread_mutex_lock(&params->fin_mutex);
	if (params->finished == params->nphilo)
	{
		pthread_mutex_unlock(&params->fin_mutex);
		return (1);
	}
	pthread_mutex_unlock(&params->fin_mutex);
	return (0);
}

void	set_finished(t_args *args)
{
	pthread_mutex_lock(&args->params->fin_mutex);
	args->params->finished++;
	pthread_mutex_unlock(&args->params->fin_mutex);
}

int	all_alive(t_params *params)
{
	int	ret;

	ret = TRUE;
	pthread_mutex_lock(&params->dead_mutex);
	if (params->dead == TRUE)
		ret = FALSE;
	pthread_mutex_unlock(&params->dead_mutex);
	return (ret);
}
