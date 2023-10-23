/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   no_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacortes <dacortes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 10:34:40 by dacortes          #+#    #+#             */
/*   Updated: 2023/10/23 15:38:56 by dacortes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/shell_mini.h"

int rdc_stdinp(t_get **g, int mode)
{
		if ((*g)->fd[0] >= 0)
		{
			if (dup2((*g)->fd[0], STDIN_FILENO) == ERROR)
			{
				if (mode == CHD)
					exit (1);
				else if (mode == FTH)
					return (1);
			}
			if (close((*g)->fd[0]) == ERROR)
			{
				if (mode == CHD)
					exit (1);
				else if (mode == FTH)
					return (1);
			}
		}
	return (SUCCESS);
}

int rdc_stdout(t_get **g, int mode)
{
	if ((*g)->fd[1] >= 0)
	{
		if ((*g)->fd[1] >= 0)
		{
			if (dup2((*g)->fd[1], STDOUT_FILENO) == ERROR)
			{
				if (mode == CHD)
					exit (1);
				else if (mode == FTH)
					return (1);
			}
			if (close((*g)->fd[1]) == ERROR)
			{
				if (mode == CHD)
					exit (1);
				else if (mode == FTH)
					return (1);
			}
		}
	}
	return (SUCCESS);
}

static	int child(t_get **g, t_exe *ex)
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
	return  (SUCCESS);
}

int	no_pipe(t_mini **sh, t_line **ln, t_get **g, t_exe *ex)
{
	int	stt;

	stt = 0;
	if (!ex->stt && !ex->pipe)
	{
		stt = is_built_ins(sh, ln, g, &ex->stt);
		if (g && *g && !stt)
		{
			int	fd[2];
			
			fd[0] = dup(STDIN_FILENO);
    		fd[1] = dup(STDOUT_FILENO);
			rdc_stdinp(g, FTH);
			rdc_stdout(g, FTH);
			exe_buitl_ins(sh, ln, g, &ex->stt);
			if (dup2(fd[0], STDIN_FILENO) == ERROR)
				return (1);
			if (dup2(fd[1], STDOUT_FILENO) == ERROR)
				return (1);
			close(fd[0]);
    		close(fd[1]);
		}
		if (stt == ERROR)
		{
			stt = get_path(ex, *g, search_env((*sh)->env, "PATH", VAL));
			if (stt == ERROR)
			{
				stt = is_bin(ex);
				if (!stt)
				{
					ex->stt = stt;
					child(g, ex);
					(ex->stt != 0) && (ex->stt = msg_error(E_BADINT, E_PRM, ex->cmd));
				}
				clear_cmd(*ex, 1);
			}
		}
		if (!stt && g && *g && !ex->stt && ex->cmd)
		{
			child(g, ex);
			(stt == 0) && clear_cmd(*ex, 2);
		}
	}
	return (SUCCESS);
}
