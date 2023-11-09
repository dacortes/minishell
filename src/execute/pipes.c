/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacortes <dacortes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 11:42:15 by dacortes          #+#    #+#             */
/*   Updated: 2023/11/09 17:35:38 by dacortes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../inc/shell_mini.h"

/* error < hola.sh | < hola.sh */
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
	int		stt_chd;

	tmp[0] = dup(STDIN_FILENO);
	tmp[1] = dup(STDOUT_FILENO);
	i = 0;
	stt_chd = 0;
	while(i <= ex->pipe)
	{
			if (i < ex->pipe)
			{
				if (pipe(fds) == ERROR)
					exit(msg_error(E_PRR, 1, "fork"));
			}
		chd = fork();
		stt_chd = chd;
		chds[i] = chd;
		if (chd == ERROR)
			exit(msg_error(E_PRR, 1, "fork"));
		if (!chd)
		{
			if (i < ex->pipe) 
			{
				close(fds[0]);
                dup2(fds[1], STDOUT_FILENO);
                close(fds[1]);
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
			exit (0);
		}
		i++;
		(*g && (*g)->next) && ((*g) = (*g)->next);
		close(fds[1]);
		dup2(fds[0], STDIN_FILENO);
		close(fds[0]);
	}
	dup2(tmp[0], STDIN_FILENO);
	close(tmp[0]);
	dup2(tmp[1], STDOUT_FILENO);
	close(tmp[1]);
	i = 0;
	while (i <= (ex->pipe))
	{
		/* el waipid retorna el pid del procesoo que espero  */
		ft_printf("%d\n", waitpid(chds[i], &ex->stt, 0));
		ft_printf(R"%d\n"E, stt_chd);
		if (waitpid(chds[i], &ex->stt, 0) == stt_chd)
		{
			ft_printf("%d\n", stt_chd);
			ex->stt = WEXITSTATUS(ex->stt);
		}
		i++;
	}
	return (SUCCESS);
}
/* errors */
/*bash: unset: `1a': not a valid identifier
cd ""
cd ''
echo ""''""''""''
echo ''""""a*/