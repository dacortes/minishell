/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   no_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacortes <dacortes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 10:34:40 by dacortes          #+#    #+#             */
/*   Updated: 2023/10/26 15:47:48 by dacortes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/shell_mini.h"

static int	child(t_get **g, t_exe *ex)
{
	pid_t	pid;

	pid = fork();
	if (g && *g && !pid)
	{
		rdc_stdinp(g, CHD);
		rdc_stdout(g, CHD);
		(ex->stt == 0) && (ex->stt = execve(ex->cmd, (*g)->arg, ex->env));
		exit (127);
	}
	waitpid(pid, &ex->stt, 0);
	ex->stt = WEXITSTATUS(ex->stt);
	return (SUCCESS);
}

static int	rdc_built_ins(t_mini **sh, t_line **ln, t_get **g, t_exe *ex)
{
	int	fd[2];

	fd[0] = dup(STDIN_FILENO);
	fd[1] = dup(STDOUT_FILENO);
	rdc_stdinp(g, FTH);
	rdc_stdout(g, FTH);
	exe_built_ins(sh, ln, g, &ex->stt);
	if (dup2(fd[0], STDIN_FILENO) == ERROR)
		return (1);
	if (dup2(fd[1], STDOUT_FILENO) == ERROR)
		return (1);
	close(fd[0]);
	close(fd[1]);
	return (SUCCESS);
}

static int	rdc_bin(t_get **g, t_exe *ex, int *stt)
{
	*stt = is_bin(ex);
	if (!stt)
	{
		ex->stt = *stt;
		child(g, ex);
		(ex->stt != 0) && (ex->stt = msg_error(E_BADINT, E_PRM, ex->cmd));
	}
	clear_cmd(ex, 1);
	return (SUCCESS);
}

int	no_pipe(t_mini **sh, t_line **ln, t_get **g, t_exe *ex)
{
	int	stt;

	stt = 0;
	if (!ex->stt && !ex->pipe)
	{
		stt = is_built_ins(ln, g);
		if (g && *g && !stt)
			rdc_built_ins(sh, ln, g, ex);
		if (stt == ERROR)
		{
			stt = get_path(ex, *g, search_env((*sh)->env, "PATH", VAL));
			if (stt == ERROR)
				rdc_bin(g, ex, &stt);
		}
		if (!stt && g && *g && !ex->stt && ex->cmd)
		{
			child(g, ex);
			(stt == 0) && clear_cmd(ex, 1);
		}
	}
	return (SUCCESS);
}
