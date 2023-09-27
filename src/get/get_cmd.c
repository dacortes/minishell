/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacortes <dacortes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 11:09:06 by dacortes          #+#    #+#             */
/*   Updated: 2023/09/27 17:35:46 by dacortes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/shell_mini.h"

 #include <string.h>

int	search_hrdoc()
{
	return (SUCCESS);
}

int	search_cmd(t_line **ln, t_get **g)
{
	(void)ln;
	(void)g;
	// t_line	*tmp;
	// t_token	*tk;
	return (SUCCESS);
}

/* executer */
int	get_cmd(t_line **ln, t_env *env, t_get *g)
{
	(void)ln;
	(void)env;
	(void)g;
	return (SUCCESS);
}

int	get_init(t_line **ln, t_get **g)
{
	t_line	*tmp;
	// t_token	*tk;
	// char	**arg;

	if (!*ln)
		return (SUCCESS);
	tmp = *ln;
	*g = ft_calloc(sizeof(t_get), 1);
	if (!*g)
		exit (msg_error(E_MEM, 1, NULL));
	while (tmp)
	{
		// tk = tmp->tk;
		ft_printf("%d\n", tmp->argc);
		tmp = tmp->next;
	}
	free(*g);
	return (SUCCESS);
}