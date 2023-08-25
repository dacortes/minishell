/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacortes <dacortes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 10:25:54 by dacortes          #+#    #+#             */
/*   Updated: 2023/08/24 12:13:40 by dacortes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/shell_mini.h"

int	is_close(char *str, char delimiter)
{
	int	del;
	int	i;

	del = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == delimiter)
			del++;
		else if (str[i] == delimiter && del % 2 == 0)
		{
			while (str[i])
			{
				i++;
				if (str[i] == delimiter)
				{
					del++;
					break ;
				}
			}
		}
		i++;
	}
	return (del % 2 == 0);
}

char	*search_env(t_env *env, char *key, int type)
{
	t_env *search;

	search = env;
	if (type == KEY)
	{
		while (search)
		{
			if (ft_strncmp(search->key, key, -1) == 0)
				return (search->key);
			search = search->next;
		}
	}
	else if (type == VAL)
	{
		while (search)
		{
			if (ft_strncmp(search->key, key, -1) == 0)
				return (search->val);
			search = search->next;
		}
	}
	return (NULL);
}