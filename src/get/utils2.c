/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacortes <dacortes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 09:38:12 by dacortes          #+#    #+#             */
/*   Updated: 2023/10/05 14:06:39 by dacortes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/shell_mini.h"

int	count_tk(t_token *tk)
{
	t_token	*iter;
	int		num;

	num = 0;
	if (!tk)
		return (num);
	iter = tk;
	while (iter)
	{
		num++;
		iter = iter->next;
	}
	return (num);
}

int	is_bin(t_exe *ex)
{
	if (!ex || !ex->cmd || !ex->cmd)
		return (SUCCESS);
	if ((ex->cmd[0] == '.' && ex->cmd[1] != '/'))
	{
		ft_printf(B"estoy aqui\n"E);
		return ((ex->stt = msg_error(E_CNF, E_CNF, ex->cmd)));
	}
	else if (!(ex->cmd[0] == '.' && ex->cmd[1] == '/'))
	{
		ft_printf(R"estoy aqui\n"E);
		return ((ex->stt = msg_error(E_NSF, E_CNF, ex->cmd)));
	}
	if (ft_strchr(ex->cmd, '/') && access(ex->cmd, F_OK))
	{
		ft_printf(Y"estoy aqui\n"E);
		return ((ex->stt = msg_error(E_CNF, E_CNF, ex->cmd)));
	}
	else if (ft_strchr(ex->cmd, '/') && access(ex->cmd, X_OK))
		return ((ex->stt = msg_error(E_PRM, E_PRM, ex->cmd)));
	return (SUCCESS);
}
