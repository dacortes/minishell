/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacortes <dacortes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 11:09:06 by dacortes          #+#    #+#             */
/*   Updated: 2023/09/27 10:09:16 by dacortes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/shell_mini.h"

 #include <string.h>
int	search_cmd(t_line **ln, t_get *g)
{
	t_line	*tmp;
	t_token	*tk;

	(void)g;
	tmp = *ln;
	while (tmp)
	{
		tk = tmp->tk;
		ft_printf(Y"line\n"E);
		while (tk)
		{
			if ((tk->type[3] >= 3 && tk->type[3] <= 6) || tk->type[3] == T_FD
				|| tk->type[3] == T_CMD)
				tk = tk->next;
			else
			{
				ft_printf(C"search_cmd *%s*\n"E, tk->arg);
				tk->type[3] = T_CMD;
				tk = tmp->tk;
			}
			tk = tk->next;
		}
		tmp = tmp->next;
	}
	return (SUCCESS);
}

/*line -- env -- t_get*/
int	get_cmd(t_line **ln, t_env *env, t_get g)
{
	(void)ln;
	(void)env;
	(void)g;
	return (SUCCESS);
}