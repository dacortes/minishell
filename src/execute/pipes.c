/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacortes <dacortes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 11:42:15 by dacortes          #+#    #+#             */
/*   Updated: 2023/11/09 08:52:16 by dacortes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../inc/shell_mini.h"

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
	exit (SUCCESS);
}

static int	rdc_bin(t_get **g, t_exe *ex, int *stt)
{
	*stt = is_bin(ex);
	if (!stt)
	{
		ex->stt = *stt;
		rdc_stdinp(g, FTH);
		rdc_stdout(g, FTH);
		(ex->stt == 0) && (ex->stt = execve(ex->cmd, (*g)->arg, ex->env));
		perror("mini");
        exit(EXIT_FAILURE);
	}
	clear_cmd(ex, 1);
	exit (SUCCESS);
}

int	pipes(t_mini **sh, t_line **ln, t_get **g, t_exe *ex)
{
	int		fds[2];
	int		tmp[2];
	pid_t 	chds[ex->pipe + 1];
	pid_t	chd;
	int		i;

	tmp[0] = dup(STDIN_FILENO);
	tmp[1] = dup(STDOUT_FILENO);
	i = 0;
	while(i <= ex->pipe)
	{
		if (i < ex->pipe)
		{
			if (pipe(fds) == ERROR)
				exit(msg_error(E_PRR, 1, "fork"));
		}
		chd = fork();
		// ft_printf("%d\n", chd);
		chds[i] = chd;
		if (chd == ERROR)
			exit(msg_error(E_PRR, 1, "fork"));
		if (!chd)
		{
			if (i == 0) 
			{
				ft_printf("soy la primer pipe\n");
				close(fds[0]);
                dup2(fds[1], STDOUT_FILENO);
                close(fds[1]);
            }
			else if (i > 0 && i < ex->pipe)
			{
				ft_printf("estoy aqui\n");
				close(fds[0]);
				dup2(fds[1], STDOUT_FILENO);
				close(fds[1]);
				dup2(fds[0], STDIN_FILENO);
				close(fds[0]);
			}
			else if (i == ex->pipe)
			{
				ft_printf("soy la ultima pipe\n");
				close(fds[1]);
                dup2(fds[0], STDIN_FILENO);
                close(fds[0]);
            }
			int stt = 0;
			ex->stt = is_built_ins(ln, g);
			if (g && *g && !ex->stt)
				rdc_built_ins(sh, ln, g, ex);
			if (ex->stt == ERROR)
			{
				ex->stt = get_path(ex, *g, search_env((*sh)->env, "PATH", VAL));
				if (ex->stt == ERROR)
					rdc_bin(g, ex, &stt);
			}
			if (!stt && g && *g && !ex->stt && ex->cmd)
			{
				rdc_stdinp(g, FTH);
				rdc_stdout(g, FTH);
				(ex->stt == 0) && (ex->stt = execve(ex->cmd, (*g)->arg, ex->env));
            	exit(127);
			}
		}
		i++;
		(*g && (*g)->next) && ((*g) = (*g)->next);
	}
	close(fds[1]);
	dup2(fds[0], STDIN_FILENO);
	close(fds[0]);
	
	dup2(tmp[0], STDIN_FILENO);
	close(tmp[0]);
	dup2(tmp[1], STDOUT_FILENO);
	close(tmp[1]);
	i = 0;
	ft_printf("num pipes : %d\n", ex->pipe);
	while (i <= (ex->pipe))
	{
		/* el waipid retorna el pid del procesoo que espero  */
		// ft_printf("%d\n", waitpid(chds[i], &ex->stt, 0));
		waitpid(chds[i], &ex->stt, 0);
		if (i == ex->pipe)
			ex->stt = WEXITSTATUS(ex->stt);
		i++;
	}
	return (SUCCESS);
}
