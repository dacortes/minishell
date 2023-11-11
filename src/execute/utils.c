/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacortes <dacortes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 17:48:26 by dacortes          #+#    #+#             */
/*   Updated: 2023/11/11 13:02:49 by dacortes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/shell_mini.h"

int	pp_rdc_bin(t_get **g, t_exe *ex, int *stt)
{
	*stt = is_bin(ex);
	if (!*stt)
	{
		ex->stt = *stt;
		rdc_stdinp(g, FTH);
		rdc_stdout(g, FTH);
		(ex->stt == 0) && (ex->stt = execve(ex->cmd, (*g)->arg, ex->env));
		perror("mini");
		exit(EXIT_FAILURE);
	}
	clear_cmd(ex, 1);
	if (*stt != SUCCESS)
		exit (*stt);
	exit (SUCCESS);
}

int	pp_rdc_built_ins(t_mini **sh, t_line **ln, t_get **g, t_exe *ex)
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
