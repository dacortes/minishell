/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacortes <dacortes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 16:31:56 by dacortes          #+#    #+#             */
/*   Updated: 2023/10/23 16:56:42 by dacortes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/shell_mini.h"

int	rdc_stdinp(t_get **g, int mode)
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

int	rdc_stdout(t_get **g, int mode)
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
