/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cdl_listclear.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: rmaes <rmaes@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/13 18:03:54 by rmaes         #+#    #+#                 */
/*   Updated: 2022/12/15 16:22:05 by rmaes         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cdl_list.h"
#include <stdlib.h>

void	cdl_listclear(t_dllist *list)
{
	while (list->head)
		cdl_listdelnode(list, 0);
	free(list);
}
