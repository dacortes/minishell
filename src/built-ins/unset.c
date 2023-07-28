/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacortes <dacortes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 12:55:33 by dacortes          #+#    #+#             */
/*   Updated: 2023/07/28 13:40:47 by dacortes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/shell_mini.h"

void	magic_node(t_mini *sh)
{
	t_env	*node;

	if (!sh->env)
	{
		ft_printf(R"No hay nodos\n"E);
		return ;
	}
	node = sh->env;
	while (node)
	{
		ft_printf(B"node actual➜"E" %p\n", node);
		ft_printf(Y"data➜var"E" %s\n", node->var);
		ft_printf(G"node siguente➜"E" %p\n", node);
		node = node->next;
	}
	ft_printf(B"size del env %d\n"E, sh->e_size);
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

int	unset(int *size, t_env **env, char *var)
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
			(*size)--;
			return (SUCCESS);
		}
		prev = rm;
		rm = rm->next;
	}
	return (ERROR);
}
