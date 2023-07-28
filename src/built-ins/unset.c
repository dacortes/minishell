/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacortes <dacortes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 12:55:33 by dacortes          #+#    #+#             */
/*   Updated: 2023/07/28 13:32:42 by dacortes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/shell_mini.h"

void	magic_mode(t_env *env)
{
	t_env	*node;

	if (!env)
	{
		ft_printf(R"No hay nodos\n"E);
		return ;
	}
	node = env;
	while (node)
	{
		ft_printf(B"node actual➜"E" %p\n", node);
		ft_printf(Y"data➜var"E" %s\n", node->var);
		ft_printf(G"node siguente➜"E" %p\n", node);
		node = node->next;
	}
}

// int	unset(t_env *env, char *var)
// {
// 	t_env	*rm;
// 	t_env	*tmp;

// 	rm = env;
// 	while (rm)
// 	{
// 		if (ft_strncmp(rm->var, var, -1) == 0)
// 		{
// 			tmp = rm->next;
// 			if (rm->var)
// 				free(rm->var);
// 			if (rm->val)
// 				free(rm->val);
// 			free(rm);
// 			rm = tmp;
// 		}
// 		rm = rm->next;
// 	}
// 	return (SUCCESS);
// }

int	unset(t_env **env, char *var)
{
	t_env	*rm;
	t_env	*prev;

	rm = *env;
	prev = NULL;
	while (rm)
	{
		if (ft_strncmp(rm->var, var, -1) == 0)
		{
			if (prev)
				prev->next = rm->next;
			else
				*env = rm->next;
			free(rm->var);
			free(rm->val);
			free(rm);
			return (SUCCESS);
		}
		prev = rm;
		rm = rm->next;
	}
	return (ERROR);
}
