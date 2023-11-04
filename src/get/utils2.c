/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacortes <dacortes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 09:38:12 by dacortes          #+#    #+#             */
/*   Updated: 2023/11/04 12:59:16 by dacortes         ###   ########.fr       */
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
	if (ft_strnstr(ex->cmd, "./", ft_strlen(ex->cmd)) && access(ex->cmd, F_OK))
		return ((ex->stt = msg_error(E_CNF, E_CNF, ex->cmd)));
	if (ft_strnstr(ex->cmd, "./", ft_strlen(ex->cmd)) && access(ex->cmd, X_OK))
		return ((ex->stt = msg_error(E_PRM, E_PRM, ex->cmd)));
	if (!ft_strnstr(ex->cmd, "/", ft_strlen(ex->cmd)))
		return ((ex->stt = msg_error(E_CNF, E_CNF, ex->cmd)));
	return (SUCCESS);
}

t_env	*get_env(int flag, t_env *env)
{
	static t_env	*get;

	if (flag == TRUE)
		get = env;
	return (get);
}
