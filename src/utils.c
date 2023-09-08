/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacortes <dacortes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 10:25:54 by dacortes          #+#    #+#             */
/*   Updated: 2023/09/08 11:51:06 by dacortes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/shell_mini.h"

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

char	*ft_strdup_exit(const char *s1)
{
	char	*cp;

	cp = (char *)malloc(ft_strlen(s1) + 1);
	if (!cp)
		exit (msg_error(E_MEM, E_EXIT, "ft_strdup"));
	ft_memcpy(cp, s1, ft_strlen(s1) + 1);
	return (cp);
}
