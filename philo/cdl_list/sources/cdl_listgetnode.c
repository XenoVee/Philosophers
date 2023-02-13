/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cdl_listgetnode.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: rmaes <rmaes@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/13 17:05:22 by rmaes         #+#    #+#                 */
/*   Updated: 2022/12/15 16:22:16 by rmaes         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cdl_list.h"

// retuns a pointer to the N'th node of LIST (head is node 0).
// Because it is a circular list,
// it will loop around would N be greater than listlen
t_dlnode	*cdl_listgetnode(t_dllist *list, int n)
{
	t_dlnode	*index;

	if (list->head == NULL)
		return (NULL);
	index = list->head;
	while (n)
	{
		index = index->next;
		n--;
	}
	return (index);
}
