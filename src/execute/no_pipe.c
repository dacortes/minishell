/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   no_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcespede <fcespede@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 10:34:40 by dacortes          #+#    #+#             */
/*   Updated: 2023/11/12 18:22:20 by fcespede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/shell_mini.h"

static int	child(t_get **g, t_exe *ex)
{
	pid_t	pid;

	pid = fork();
	if (g && *g && !pid)
	{
		signal(SIGINT, exit);
		signal(SIGQUIT, exit);
		rdc_stdinp(g, CHD);
		rdc_stdout(g, CHD);
		(ex->stt == 0) && (ex->stt = execve(ex->cmd, (*g)->arg, ex->env));
		exit (127);
	}
	waitpid(pid, &ex->stt, 0);
	if (WIFEXITED(ex->stt))
		ex->stt = WEXITSTATUS(ex->stt);
	else
		handle_signaled(&ex->stt, WTERMSIG(ex->stt));
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
	fd[0] = -2;
	fd[1] = -2;
	return (SUCCESS);
}

static int	rdc_bin(t_get **g, t_exe *ex, int *stt)
{
	*stt = is_bin(ex);
	if (!*stt)
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
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	if (!ex->stt && !ex->pipe)
	{
		if (!g || !*g || !(*g)->arg[0])
			return (SUCCESS);
		stt = is_built_ins(ln, g);
		(g && *g && !stt) && rdc_built_ins(sh, ln, g, ex);
		if (stt == ERROR)
		{
			stt = get_path(ex, *g, search_env((*sh)->env, "PATH", VAL));
			if (g && *g && (*g)->arg[0] && !(*g)->arg[0][0])
				return (SUCCESS);
			(stt == ERROR) && rdc_bin(g, ex, &stt);
		}
		if (!stt && g && *g && !ex->stt && ex->cmd)
		{
			child(g, ex);
			(stt == 0) && clear_cmd(ex, 1);
		}
	}
	return (SUCCESS);
}
