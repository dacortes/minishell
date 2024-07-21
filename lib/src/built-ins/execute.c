/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacortes <dacortes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 15:37:44 by dacortes          #+#    #+#             */
/*   Updated: 2023/11/13 15:57:45 by dacortes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/shell_mini.h"

int	its_not_the_others(t_mini **sh, t_line **ln, t_get **g, int n_cmd)
{
	t_aux	a;
	char	*low;

	low = ft_calloc(ft_strlen((*g)->arg[0]) + 1, sizeof(char));
	if (!low)
		exit (msg_error(E_MEM, E_MEM, NULL));
	ft_bzero(&a, sizeof(t_aux));
	if (ft_strncmp(str_lower((*g)->arg[0], low), "cd", -1) == 0)
		a.c = ft_cd(sh, *g, n_cmd);
	if (ft_strncmp(str_lower((*g)->arg[0], low), "echo", -1) == 0)
		ft_echo((*g)->arg, n_cmd);
	if ((ft_strncmp(str_lower((*g)->arg[0], low), "env", -1) == 0))
		(_env((*sh)->env, n_cmd)) && (a.c = 1);
	if (ft_strncmp((*g)->arg[0], "exit", -1) == 0)
		a.c = ft_exit(*sh, ln, g, n_cmd);
	a.c = magic_export(sh, g, a, n_cmd);
	free(low);
	return (a.c);
}

int	are_the_others(t_mini **sh, t_get **g, int n_cmd)
{
	char	*low;
	int		stt;

	stt = 0;
	low = ft_calloc(ft_strlen((*g)->arg[0]) + 1, sizeof(char));
	if (!low)
		exit (msg_error(E_MEM, E_MEM, NULL));
	if ((ft_strncmp(str_lower((*g)->arg[0], low), "pwd", -1) == 0))
		pwd();
	if ((ft_strncmp((*g)->arg[0], "unset", -1) == 0))
		stt = magic_unset(sh, g, n_cmd);
	else
	{
		free(low);
		return (SUCCESS);
	}
	free(low);
	return (stt);
}

static int	ft_is(char *cmd)
{
	char	*low;

	low = ft_calloc(ft_strlen(cmd) + 1, sizeof(char));
	if (!low)
		exit (msg_error(E_MEM, E_MEM, NULL));
	if (!(ft_strncmp(str_lower(cmd, low), "cd", -1) == 0)
		&& !(ft_strncmp(cmd, "echo", -1) == 0)
		&& !(ft_strncmp(str_lower(cmd, low), "env", -1) == 0)
		&& !(ft_strncmp(cmd, "exit", -1) == 0)
		&& !(ft_strncmp(cmd, "export", -1) == 0)
		&& !(ft_strncmp(str_lower(cmd, low), "pwd", -1) == 0)
		&& !(ft_strncmp(cmd, "unset", -1) == 0))
	{
		free(low);
		return (ERROR);
	}
	free(low);
	return (SUCCESS);
}

int	is_built_ins(t_line **ln, t_get **g)
{
	int	n_cmd;

	if (!*ln || !*g)
		return (SUCCESS);
	if (g && *g && (*g)->arg && (*g)->arg[0]
		&& ft_is((*g)->arg[0]) != ERROR)
		n_cmd = ft_double_ptr_len((void **)(*g)->arg);
	else
		return (ERROR);
	return (SUCCESS);
}

int	exe_built_ins(t_mini **sh, t_line **ln, t_get **g, int *chk)
{
	int	n_cmd;
	int	aux_stt;

	aux_stt = 0;
	n_cmd = ft_double_ptr_len((void **)(*g)->arg);
	if (*chk != E_SNT && *g && (*g)->arg[0] && (*g)->arg[0][0] != '\0')
	{
		*chk = its_not_the_others(sh, ln, g, n_cmd);
		(*chk == 1) && (aux_stt = 1);
		*chk = are_the_others(sh, g, n_cmd);
		(aux_stt) && (*chk = 1);
	}
	return (SUCCESS);
}
