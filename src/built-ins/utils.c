/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 09:36:38 by codespace         #+#    #+#             */
/*   Updated: 2024/07/24 12:12:29 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*search_env(t_env *env, char *key, int type)
{
	t_env	*search;

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
	else if (type == VALUE)
	{
		while (search)
		{
			if (ft_strncmp(search->key, key, -1) == 0)
				return (search->value);
			search = search->next;
		}
	}
	return (NOT);
}
