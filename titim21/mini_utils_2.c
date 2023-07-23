/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_utils_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fouaouri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 17:34:28 by fouaouri          #+#    #+#             */
/*   Updated: 2023/07/16 02:31:01 by fouaouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strlen(char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t			i;
	unsigned char	*str1;
	unsigned char	*str2;

	i = 0;
	if (!s1 || !s2)
		return (0);
	str1 = (unsigned char *)s1;
	str2 = (unsigned char *)s2;
	while ((str1[i] || str2[i]))
	{
		if (str1[i] != str2[i])
			return (str1[i] - str2[i]);
		i++;
	}
	return (0);
}

t_list	*ft_lstnew(char **file_name, char **commandes, char **type)
{
	t_list	*new_node;

	new_node = (t_list *)malloc(sizeof(t_list));
	if (new_node == NULL)
		return (NULL);
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

char	*ft_strcpy(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i])
	{
		s2[i] = s1[i];
		i++;
	}
	return (s2);
}
