/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacortes <dacortes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 15:37:44 by dacortes          #+#    #+#             */
/*   Updated: 2023/10/04 14:43:51 by dacortes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/shell_mini.h"

int	its_not_the_others(t_mini **sh, t_line **ln, t_get **g, int n_cmd)
{
	t_aux	a;

	ft_bzero(&a, sizeof(t_aux));
	if (ft_strncmp((*g)->arg[0], "cd", -1) == 0
		|| (ft_strncmp((*g)->arg[0], "CD", -1) == 0))
		a.c = ft_cd(sh, *g, n_cmd);
	if (ft_strncmp((*g)->arg[0], "echo", -1) == 0
		|| (ft_strncmp((*g)->arg[0], "ECHO", -1) == 0))
		ft_echo((*g)->arg, n_cmd);
	if ((ft_strncmp((*g)->arg[0], "env", -1) == 0)
		|| (ft_strncmp((*g)->arg[0], "ENV", -1) == 0))
		(_env((*sh)->env, n_cmd)) && (a.c = 1);
	if (ft_strncmp((*g)->arg[0], "exit", -1) == 0)
		a.c = ft_exit(*sh, ln, g, n_cmd);
	if ((ft_strncmp((*g)->arg[0], "export", -1) == 0))
	{
		if (n_cmd >= 2)
		{
			while ((*g)->arg[a.i])
				(_export(*sh, (*g)->arg[a.i++])) && (a.c = 1);
		}
		else
			show_export((*sh)->env);
	}
	return (a.c);
}

int	are_the_others(t_mini **sh, t_get **g, int n_cmd)
{
	int	i;

	i = 0;
	if ((ft_strncmp((*g)->arg[0], "pwd", -1) == 0)
		|| (ft_strncmp((*g)->arg[0], "PWD", -1) == 0))
		pwd();
	if ((ft_strncmp((*g)->arg[0], "unset", -1) == 0))
	{
		if (n_cmd >= 2)
		{
			while ((*g)->arg[i])
				(unset(&(*sh)->size, &(*sh)->env, (*g)->arg[i++]));
		}
	}
	else
		return (ERROR);
	return (SUCCESS);
}

/* la funcion debe hacer un minus para los cmd cd, env, pwd*/
static int	ft_is(char *cmd)
{
	if (!(ft_strncmp(cmd, "cd", -1) == 0)
		&& !(ft_strncmp(cmd, "CD", -1) == 0)
		&& !(ft_strncmp(cmd, "echo", -1) == 0)
		&& !(ft_strncmp(cmd, "env", -1) == 0)
		&& !(ft_strncmp(cmd, "ENV", -1) == 0)
		&& !(ft_strncmp(cmd, "exit", -1) == 0)
		&& !(ft_strncmp(cmd, "export", -1) == 0)
		&& !(ft_strncmp(cmd, "pwd", -1) == 0)
		&& !(ft_strncmp(cmd, "PWD", -1) == 0)
		&& !(ft_strncmp(cmd, "unset", -1) == 0))
		return (ERROR);
	return (SUCCESS);
}

int	is_built_ins(t_mini **sh, t_line **ln, t_get **g, int *chk)
{
	int	n_cmd;
	int	i;

	if (!*ln || !*g)
		return (SUCCESS);
	if (g && *g && (*g)->arg && (*g)->arg[0]
		&& ft_is((*g)->arg[0]) != ERROR)
		n_cmd = ft_double_ptr_len((void **)(*g)->arg);
	else
		return (ERROR);
	i = 1;
	if (*chk != E_SNT && *g && (*g)->arg[0] && (*g)->arg[0][0] != '\0')
	{
		*chk = its_not_the_others(sh, ln, g, n_cmd);
		are_the_others(sh, g, n_cmd);
	}
	return (SUCCESS);
}
