/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler_list.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacortes <dacortes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 12:51:07 by dacortes          #+#    #+#             */
/*   Updated: 2024/07/10 11:05:12 by dacortes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <minishell.h>

void	*get_last(void *list, size_t size)
{
	if (!list)
		return (NULL);
	if (size == sizeof(t_env))
	{
		list = (t_env *)list;
        while (((t_env *)list) && ((t_env *)list)->next)
		{
			if (((t_env *)list)->next)
            	list = ((t_env *)list)->next;
		}
		return (list);
    }
	if (size == sizeof(t_token))
	{
		list = (t_token *)list;
        while ((t_token *)list && ((t_token *)list)->next)
		{
			if (((t_token *)list)->next)
            	list = ((t_token *)list)->next;
		}
		return (list);
    }
	return (list);
}

void	add_back(void **list, void *new, size_t size)
{
	void	*tmp;

	if (list)
	{
		if (!*list)
			*list = new;
		else
		{
			tmp = get_last(*list, size);
			if (size == sizeof(t_env))
				((t_env *)tmp)->next = (t_env *)new;
			else if  (size == sizeof(t_token))
				((t_token *)tmp)->next = (t_token *)new;
		}
	}
}
