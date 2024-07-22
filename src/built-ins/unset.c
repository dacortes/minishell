/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacortes <dacortes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 14:33:00 by dacortes          #+#    #+#             */
/*   Updated: 2024/07/20 14:51:01 by dacortes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	_unset(t_env **env, char *key)
{
	t_env	*rm;
	t_env	*prev;

	rm = *env;
	prev = NULL;
	while (rm)
	{
		if (!ft_strncmp(rm->key, key, ft_strlen(key)))
		{
			if (prev)
				prev->next = rm->next;
			else
				*env = rm->next;
			ft_free(&rm->key, &rm->value);
			free(rm);
			return (EXIT_SUCCESS);
		}
		prev = rm;
		rm = rm->next;
	}
	return (EXIT_SUCCESS);
}

