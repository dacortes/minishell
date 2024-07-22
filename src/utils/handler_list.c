/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler_list.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 12:51:07 by dacortes          #+#    #+#             */
/*   Updated: 2024/07/21 10:19:05 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static const void *(*g_data_type[])(void *list) =\
{(void *)cast_token, (void *)cast_env};

t_token	*cast_token(void *list)
{
	list = (t_token *)list;
	while (((t_token *)list) && ((t_token *)list)->next)
	{
		if (((t_token *)list)->next)
			list = ((t_token *)list)->next;
	}
	return (list);
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

void	*get_last(void *list, data_type size)
{
	if (!list)
		return (NULL);
	list = (void *)g_data_type[size](list);
	return (list);
}

void	add_back(void **list, void *new, data_type size)
{
	void	*tmp;

	if (list)
	{
		if (!*list)
			*list = new;
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
