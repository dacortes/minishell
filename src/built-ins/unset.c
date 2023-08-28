/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcespede <fcespede@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 14:04:55 by dacortes          #+#    #+#             */
/*   Updated: 2023/08/28 14:37:19 by fcespede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/shell_mini.h"

int	unset(int *size, t_env **env, char *key)
{
	t_env	*rm;
	t_env	*prev;

	rm = *env;
	prev = NULL;
	while (rm)
	{
		if (ft_strncmp(rm->key, key, ft_strlen(key)) == 0)
		{
			if (prev)
				prev->next = rm->next;
			else
				*env = rm->next;
			free(rm->key);
			free(rm->val);
			free(rm);
			(*size)--;
			return (SUCCESS);
		}
		prev = rm;
		rm = rm->next;
	}
	return (ERROR);
}
