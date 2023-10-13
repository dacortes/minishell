/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   no_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacortes <dacortes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 10:34:40 by dacortes          #+#    #+#             */
/*   Updated: 2023/10/13 11:52:56 by dacortes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/shell_mini.h"

static	int child(t_get **g, t_exe *ex)
{
	pid_t	pid;

	pid = fork();
	if (!pid)
	{
		if ((*g)->fd[0] >= 0)
		{
			if (dup2((*g)->fd[0], STDIN_FILENO) == ERROR)
				exit (1);
			close((*g)->fd[0]);
		}
		if ((*g)->fd[1] >= 0)
		{
			if (dup2((*g)->fd[1], STDOUT_FILENO) == ERROR)
				exit (1);
			close((*g)->fd[1]);
		}
		(ex->stt == 0) && execve(ex->cmd, (*g)->arg, ex->env);
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
		if (is_built_ins(sh, ln, g, &ex->stt) == ERROR)
		{
			stt = get_path(ex, *g, search_env((*sh)->env, "PATH", VAL));
			if (stt == ERROR)
			{
				if (!ex->stt)
					{
						stt = is_bin(ex);
						clear_cmd(*ex, 1);
					}
				clear_cmd(*ex, 2);
			}
		}
		if (!stt && !ex->stt && ex->cmd)
		{
			child(g, ex);
			(stt == 0) && clear_cmd(*ex, 2);
		}
	}
	return (SUCCESS);
}