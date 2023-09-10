/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_utils_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fouaouri <fouaouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 17:34:28 by fouaouri          #+#    #+#             */
/*   Updated: 2023/09/10 18:42:23 by fouaouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	find_count(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
			return (1);
		i++;
	}
	return (0);
}

void	lst_quote(char **file_name, char **commandes, char **type)
{
	int	i;

	i = 0;
	while (commandes[i])
	{
		if (find_count(commandes[i]))
			commandes[i] = ft_clean_d_quotes1(commandes[i]);
		i++;
	}
	i = 0;
	while (file_name[i])
	{
		if (find_count(file_name[i]))
			file_name[i] = ft_clean_d_quotes1(file_name[i]);
		i++;
	}
	i = 0;
	while (type[i])
	{
		if (find_count(type[i]))
			type[i] = ft_clean_d_quotes1(type[i]);
		i++;
	}
}

t_list	*ft_lstnew(char **file_name, char **commandes, char **type)
{
	t_list	*new_node;

	new_node = (t_list *)my_malloc(sizeof(t_list));
	if (new_node == NULL)
		return (NULL);
	lst_quote(file_name, commandes, type);
	new_node->file_name = file_name;
	new_node->commandes = commandes;
	new_node->type = type;
	new_node->next = NULL;
	return (new_node);
}

void	ft_lst_add_back(t_list **head, char **file_name,
	char **commandes, char **type)
{
	t_list	*node;
	t_list	*l;

	node = ft_lstnew(file_name, commandes, type);
	if (*head == NULL)
	{
		*head = node;
		return ;
	}
	l = *head;
	while (l->next != NULL)
	{
		l = l->next;
	}
	l->next = node;
}

int	check_special_char1(char *str)
{
	int	i;

	i = 0;
	if (str)
	{
		while (str[i])
		{
			if (str[i] == '|' || str[i] == '>' || str[i] == '<')
				return (1);
			i++;
		}
	}
	return (0);
}
