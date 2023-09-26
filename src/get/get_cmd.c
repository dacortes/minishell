/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacortes <dacortes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 11:09:06 by dacortes          #+#    #+#             */
/*   Updated: 2023/09/26 15:47:48 by dacortes         ###   ########.fr       */
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
			ft_printf(Y"token: "E"%s\n"E, tk->arg);

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