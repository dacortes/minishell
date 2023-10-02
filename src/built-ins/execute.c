/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacortes <dacortes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 15:37:44 by dacortes          #+#    #+#             */
/*   Updated: 2023/09/29 17:56:00 by dacortes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/shell_mini.h"

int	is_built_ins(t_mini **sh, t_line **ln, t_get **g, int *chk)
{
	int	n_cmd;
	int	i;

	if (!*ln || !*g)
		return (SUCCESS);
	i = 1;
	n_cmd = ft_double_ptr_len((void **)(*g)->arg);
	if (*chk != E_SNT && *g && (*g)->arg[0] && (*g)->arg[0][0] != '\0')
	{
		if (ft_strncmp((*g)->arg[0], "cd", -1) == 0)
			ft_cd(sh, *g, n_cmd);
		if (ft_strncmp((*g)->arg[0], "exit", -1) == 0)
			ft_exit(*sh, ln, g, n_cmd);
		if ((ft_strncmp((*g)->arg[0], "env", -1) == 0)
			|| (ft_strncmp((*g)->arg[0], "ENV", -1) == 0))
			_env((*sh)->env);
		if ((ft_strncmp((*g)->arg[0], "export", -1) == 0))
		{
			if (n_cmd >= 2)
			{
				while ((*g)->arg[i])
					_export(*sh, (*g)->arg[i++]);
			}
			else
				show_export((*sh)->env);
		}
		return (TRUE);
	}
	return (ERROR);
}
