/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacortes <dacortes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 12:55:33 by dacortes          #+#    #+#             */
/*   Updated: 2023/07/28 13:03:27 by dacortes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/shell_mini.h"

int	unset(t_env *env, char *var)
{
	t_env	*rm;
	t_env	*tmp;

	rm = env;
	while (rm)
	{
		if (ft_strncmp(rm->var, var, -1) == 0)
		{
			tmp = rm->next;
			if (rm->var)
				free(rm->var);
			if (rm->val)
				free(rm->val);
			free(rm);
		}
		rm = rm->next;
	}
	rm = tmp;
	return (SUCCESS);
}
