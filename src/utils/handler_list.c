/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler_list.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 12:51:07 by dacortes          #+#    #+#             */
/*   Updated: 2024/08/01 10:46:02 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	add_prev(t_basic_list **list)
{
	t_basic_list	*tmp;
	t_basic_list	*prev;

	tmp = *list;
	prev = NULL;
	while (tmp)
	{
		if (prev)
			tmp->prev = prev;
		prev = tmp;
		tmp = tmp->next;
	}
}

void	*get_last(t_basic_list *list)
{
	if (!list)
		return (NULL);
	while (list->next)
		list = list->next;
	return (list);
}

void	add_back(t_basic_list **list, t_basic_list *new)
{
	t_basic_list	*tmp;

	if (list)
	{
		if (!*list)
			*list = new;
		else
		{
			tmp = get_last(*list);
			tmp->next = new;
		}
	}
}
