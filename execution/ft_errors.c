/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_errors.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fouaouri <fouaouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/20 15:46:21 by melhadou          #+#    #+#             */
/*   Updated: 2023/09/17 18:17:00 by melhadou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

int	ft_error(int err_id, char *file_name)
{
	if (err_id == FILE_NOT_EXIST)
	{
		ft_dprintf(2, "minishell: %s: No such file or directory\n", file_name);
		return (err_id);
	}
	if (err_id == PERSMISSION_DENIED)
	{
		ft_dprintf(2, "minishell: %s: Permission denied\n", file_name);
		return (err_id);
	}
	return (SUCCESS);
}
