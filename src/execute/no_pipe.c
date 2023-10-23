/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   no_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacortes <dacortes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 10:34:40 by dacortes          #+#    #+#             */
/*   Updated: 2023/10/23 10:37:05 by dacortes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/shell_mini.h"

static	int child(t_get **g, t_exe *ex)
{
	pid_t	pid;

	pid = fork();
	if (g && *g && !pid)
	{	
		if ((*g)->fd[0] >= 0)
		{
			if (dup2((*g)->fd[0], STDIN_FILENO) == ERROR)
				exit (1);
			if (close((*g)->fd[0]) == ERROR)
				ft_printf("palito fd[0]\n");
		}
		if ((*g)->fd[1] >= 0)
		{
			if (dup2((*g)->fd[1], STDOUT_FILENO) == ERROR)
				exit (1);
			if (close((*g)->fd[1]) == ERROR)
				ft_printf("palito fd[1]\n");
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
		stt = is_built_ins(sh, ln, g, &ex->stt);
		if (g && *g && !stt)
		{
			int	fd[2];
			
			fd[0] = dup(STDIN_FILENO);
    		fd[1] = dup(STDOUT_FILENO);
			if ((*g)->fd[0] >= 0)
			{
				if (dup2((*g)->fd[0], STDIN_FILENO) == ERROR)
            		return (ft_printf(R"error STDIN_FILENO\n"E));
        		close((*g)->fd[0]);
			}
		    if ((*g)->fd[1] >= 0)
    		{
				if (dup2((*g)->fd[1], STDOUT_FILENO) == ERROR)
					return (ft_printf(R"error STDOUT_FILENO\n"E));
				close((*g)->fd[1]);
    		}
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
				if (!ex->stt)
					{
						stt = is_bin(ex);
						clear_cmd(*ex, 1);
					}
				clear_cmd(*ex, 2);
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