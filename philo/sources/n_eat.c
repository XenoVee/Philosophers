/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   n_eat.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: rmaes <rmaes@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/09 18:18:48 by rmaes         #+#    #+#                 */
/*   Updated: 2023/04/09 18:19:06 by rmaes         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

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
