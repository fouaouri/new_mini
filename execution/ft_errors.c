/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_errors.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fouaouri <fouaouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/20 15:46:21 by melhadou          #+#    #+#             */
/*   Updated: 2023/09/07 15:52:34 by fouaouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

int	ft_error(int err_id, char *file_name)
{
	if (err_id == FILE_NOT_EXIST)
	{
		printf("minishell: %s: No such file or directory\n", file_name);
		return (err_id);
	}
	if (err_id == PERSMISSION_DENIED)
	{
		printf("minishell: %s: Permission denied\n", file_name);
		return (err_id);
	}
	return (SUCCESS);
}
