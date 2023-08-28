/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melhadou <melhadou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 15:53:42 by melhadou          #+#    #+#             */
/*   Updated: 2023/08/28 15:55:11 by melhadou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

void	free_list(t_list **node)
{
	t_list *temp;

	while (*node != NULL) {
		temp = (*node);
		free((*node)->commandes);
		free((*node)->type);
		free((*node)->file_name);
		(*node) = (*node)->next;
		free(temp);
	}
}
