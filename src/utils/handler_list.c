/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler_list.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 12:51:07 by dacortes          #+#    #+#             */
/*   Updated: 2024/08/08 11:46:27 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	add_prev(t_basic **list, int flag)
{
	t_basic	*tmp;
	t_basic	*prev;

	tmp = *list;
	prev = NULL;
	(void)flag;
	while (tmp)
	{
		if (prev)
			tmp->prev = prev;
		if (flag && prev && tmp->data.token->type & EXPAN
			&& prev->data.token->type == R_HER)
			tmp->data.token->type = ARG;
		prev = tmp;
		tmp = tmp->next;
	}

}

void	*get_last(t_basic *list)
{
	if (!list)
		return (NULL);
	while (list->next)
		list = list->next;
	return (list);
}

void	add_back(t_basic **list, t_basic *new)
{
	t_basic	*tmp;

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
