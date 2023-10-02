/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacortes <dacortes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 15:37:44 by dacortes          #+#    #+#             */
/*   Updated: 2023/10/02 13:03:55 by dacortes         ###   ########.fr       */
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
		if (ft_strncmp((*g)->arg[0], "cd", -1) == 0
			|| (ft_strncmp((*g)->arg[0], "CD", -1) == 0))
			ft_cd(sh, *g, n_cmd);
		if ((ft_strncmp((*g)->arg[0], "env", -1) == 0)
			|| (ft_strncmp((*g)->arg[0], "ENV", -1) == 0))
			(_env((*sh)->env, n_cmd)) && (*chk = 1);
		if (ft_strncmp((*g)->arg[0], "exit", -1) == 0)
			*chk = ft_exit(*sh, ln, g, n_cmd);
		if ((ft_strncmp((*g)->arg[0], "export", -1) == 0))
		{
			if (n_cmd >= 2)
			{
				while ((*g)->arg[i])
					(_export(*sh, (*g)->arg[i++])) && (*chk = 1);
			}
			else
				show_export((*sh)->env);
		}
		if ((ft_strncmp((*g)->arg[0], "pwd", -1) == 0) 
			|| (ft_strncmp((*g)->arg[0], "PWD", -1) == 0))
			pwd();
		
		return (TRUE);
	}
	return (ERROR);
}
