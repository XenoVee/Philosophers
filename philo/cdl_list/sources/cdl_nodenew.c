/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cdl_nodenew.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: rmaes <rmaes@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/13 16:15:18 by rmaes         #+#    #+#                 */
/*   Updated: 2023/05/26 15:37:54 by rmaes         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cdl_list.h"
#include <stdlib.h>
#include <pthread.h>
#include <stdio.h>

// creates and allocates a new t_dlnode, using the given content
// the prev and next pointers are set to NULL
t_dlnode	*cdl_nodenew(int n)
{
	t_dlnode		*node;

	node = malloc(sizeof(t_dlnode));
	if (node == NULL)
		return (NULL);
	node->prev = NULL;
	node->next = NULL;
	pthread_mutex_init(&node->mutex, NULL);
	pthread_mutex_init(&node->eatex, NULL);
	node->eat = 0;
	node->n = n;
	return (node);
}
