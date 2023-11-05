/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacortes <dacortes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 11:42:15 by dacortes          #+#    #+#             */
/*   Updated: 2023/11/05 13:08:48 by dacortes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../inc/shell_mini.h"

/*
	ls | ls | ls  | ls | ls|a
	error: muestra todo en la estandar outpu
	dacortes➜minishell 🗂 ᐅ Makefile
	mini: Makefile: command not found
	dacortes➜minishell 🗂 ᐅ README.md
	mini: README.md: command not found
	dacortes➜minishell 🗂 ᐅ a.test
	mini: a.test: command not found
	dacortes➜minishell 🗂 ᐅ h.test
	mini: h.test: command not found
	dacortes➜minishell 🗂 ᐅ inc
	mini: inc: command not found
	dacortes➜minishell 🗂 ᐅ lib
	mini: lib: command not found
	dacortes➜minishell 🗂 ᐅ minishell
	mini: minishell: command not found
	dacortes➜minishell 🗂 ᐅ p.test
	mini: p.test: command not found
	dacortes➜minishell 🗂 ᐅ src
	mini: src: command not found
*/
// void init_pipes(int *fds, int n_pipes)
// {
// 	int	i;

//  	i = 0;
// 	while (i < n_pipes)
// 	{
// 		if (pipe(fds + i * 2) == ERROR)
// 			exit(msg_error(E_PRR, 1, "pipes"));
// 		i++;
// 	}
// }

// void clear_pipes(int *fds, int n_pipes)
// {
// 	int i;

// 	i = 0;
// 	while (i < n_pipes * 2)
// 		close(fds[i++]);
// }

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

// int create_childs(t_mini **sh, t_line **ln, t_get **g, t_exe *ex)
// {
// 	int		fds[ex->pipe * 2];
// 	pid_t	chds[ex->pipe + 1];
// 	t_aux	a;

// 	init_pipes(fds, ex->pipe);
// 	ft_bzero(&a, sizeof(t_aux));
// 	while (a.i <= ex->pipe)
// 	{
// 		chds[a.i] = fork();
// 		if (chds[a.i] == ERROR)
// 			exit(msg_error(E_PRR, 1, "fork"));
// 		if (!chds[a.i])
// 		{
// 			int stt = 0;
// 			if (a.i > 0)
// 				dup2(fds[(a.i - 1) * 2], STDIN_FILENO);
// 			if (a.i < ex->pipe)
// 				dup2(fds[a.i * 2 + 1], STDOUT_FILENO);
// 			clear_pipes(fds, ex->pipe);
// 			ex->stt = is_built_ins(ln, g);
// 			if (g && *g && !ex->stt)
// 				rdc_built_ins(sh, ln, g, ex);
// 			if (ex->stt == ERROR)
// 			{
// 				ex->stt = get_path(ex, *g, search_env((*sh)->env, "PATH", VAL));
// 				if (ex->stt == ERROR)
// 					rdc_bin(g, ex, &stt);
// 			}
// 			if (!stt && g && *g && !ex->stt && ex->cmd)
// 			{
// 				rdc_stdinp(g, CHD);
// 				rdc_stdout(g, CHD);
// 				(ex->stt == 0) && (ex->stt = execve(ex->cmd, (*g)->arg, ex->env));
// 				perror("mini");
//             	exit(EXIT_FAILURE);
// 			}
// 		}
// 		a.i++;
// 		(*g && (*g)->next) && ((*g) = (*g)->next);
// 	}
// 	clear_pipes(fds, ex->pipe);
// 	while (a.c <= ex->pipe)
// 	{
// 		waitpid(chds[a.c], &ex->stt, 0);
// 		ex->stt = WEXITSTATUS(ex->stt);
// 		a.c++;
// 	}
// 	return (SUCCESS);
// }

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
		chds[i] = chd;
		if (chd == ERROR)
			exit(msg_error(E_PRR, 1, "fork"));
		if (!chd)
		{
			if (i > 0)
			{
				close(fds[1]);
				dup2(fds[0], STDIN_FILENO);
				close(fds[0]);
			}
			if (i < ex->pipe)
			{
				close(fds[0]);
				if (dup2(fds[1], STDOUT_FILENO) == ERROR)
					return (1);
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
				ft_printf("%s\n", ex->cmd);
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
	dup2(tmp[1], STDOUT_FILENO);
	close(tmp[0]);
	close(tmp[1]);
	i = 0;
	while (i <= ex->pipe)
	{
		waitpid(chds[i], &ex->stt, 0);
		ex->stt = WEXITSTATUS(ex->stt);
		i++;
	}
	return (SUCCESS);
}
