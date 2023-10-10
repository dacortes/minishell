/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_rdc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacortes <dacortes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 12:49:36 by dacortes          #+#    #+#             */
/*   Updated: 2023/10/10 18:33:10 by dacortes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/shell_mini.h"

int	ps_open(t_token **tk, int type, int *fd)
{
	char *file;

	file = (*tk)->next->arg;
	if (type == INP)
	{
		if (access(file, F_OK) == ERROR)
			return (msg_error(E_NSF, 1, file));
		if (access(file, R_OK) == ERROR)
			return (msg_error(E_PRR, 1, file));
		fd[0] = open(file, O_RDONLY);
		if (fd[0] == ERROR)
			return (1);
	}
	else if (type == OUT)
	{
		if (!access(file, F_OK) && access(file, W_OK))
			return (msg_error(E_PRM, 1, file));
		fd[1] = open(file, O_TRUNC | O_CREAT | O_WRONLY, 0666);
		if (fd[0] == ERROR)
			return (1);
	}
	return (ERROR);
}

int	test_rdc(int *fd, t_token **tk)
{
	ft_printf("%d\n", fd[0]);
	ft_printf("%d\n", fd[1]);
	/* < */
	if ((*tk)->type[3] == T_SIR)
	{
		if (fd[0] >= 0)
			close(fd[0]);
		ps_open(tk, INP, fd);
		ft_printf(R"%d\n"E, fd[0]);
		ft_printf(R"%d\n"E, fd[1]);
	}
	return (SUCCESS);
}