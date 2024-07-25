/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler_list.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 12:51:07 by dacortes          #+#    #+#             */
/*   Updated: 2024/07/25 20:16:24 by frankgar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static const void *(*g_data_type[])(void *list) =\
{(void *)cast_token, (void *)cast_env};

void	add_prev(void **list)
{
	t_token	*tmp;
	t_token	*prev;

	tmp = (t_token *)*list;
	prev = NULL;
	while (tmp)
	{
		if (prev)
			tmp->prev = prev;
		prev = tmp;
		tmp = tmp->next;
	}
}

t_token	*cast_token(void *list)
{
	t_token	*tmp_list;

	tmp_list = (t_token *)list;
	while (tmp_list && tmp_list->next)
	{
		if (tmp_list->next)
			tmp_list = tmp_list->next;
	}
	return (tmp_list);
}

t_env	*cast_env(void *list)
{
	list = (t_env *)list;
	while (((t_env *)list) && ((t_env *)list)->next)
	{
		if (((t_env *)list)->next)
			list = ((t_env *)list)->next;
	}
	return (list);
}

void	*get_last(void *list, t_data_type size)
{
	if (!list)
		return (NULL);
	list = (void *)g_data_type[size](list);
	return (list);
}

void	add_back(void **list, void *new, t_data_type size)
{
	void	*tmp;

	if (list)
	{
		if (!*list)
		{
			*list = new;
			if (size  == T_TOKEN)
				((t_token *)(*list))->prev = NULL;
		}
		else
		{
			tmp = get_last(*list, size);
			if (size == T_ENV)
				((t_env *)tmp)->next = (t_env *)new;
			else if (size == T_TOKEN)
				((t_token *)tmp)->next = (t_token *)new;
		}
	}
}
