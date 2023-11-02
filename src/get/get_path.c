/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacortes <dacortes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 11:47:13 by dacortes          #+#    #+#             */
/*   Updated: 2023/11/02 08:56:00 by dacortes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/shell_mini.h"

static int	search_path(t_exe *ex, t_get *g, t_aux *a)
{
	while (ex->pth[a->i])
	{
		a->tmp = ft_addend_char(ex->pth[a->i], '/');
		if (!a->tmp)
			exit (msg_error(E_MEM, 1, NULL));
		ex->cmd = ft_strjoin(a->tmp, g->arg[0]);
		if (!ex->cmd)
			exit (msg_error(E_MEM, 1, NULL));
		if (access(ex->cmd, 0) == SUCCESS)
		{
			free(a->tmp);
			return (SUCCESS);
		}
		free(ex->cmd);
		free(a->tmp);
		a->i++;
	}
	return (ERROR);
}

static int	is_path(t_exe *ex, t_get *g)
{
	struct stat	path_stat;

	if (!g)
		return (SUCCESS);
	if (g->arg && ((ft_strnstr(g->arg[0], "/", ft_strlen(g->arg[0])))
			|| (g->arg[0][0] == '.' && g->arg[0][1] == '/')
			|| (ft_strnstr(g->arg[0], "../", ft_strlen(g->arg[0])))))
	{
		if (stat(g->arg[0], &path_stat) == 0)
		{
			if (S_ISREG(path_stat.st_mode))
			{
				ex->pth = NULL;
				ex->cmd = ft_strdup_exit(g->arg[0]);
				return (SUCCESS);
			}
			else if (S_ISDIR(path_stat.st_mode))
				return (msg_error(E_ISD, 126, g->arg[0]));
		}
		return (msg_error(E_NSF, E_CNF, g->arg[0]));
	}
	return (ERROR);
}

int	get_path(t_exe *ex, t_get *g, char *path)
{
	t_aux	a;

	if (!g || !g->arg || !*g->arg)
	{
		ex->pth = NULL;
		return (SUCCESS);
	}
	ft_bzero(&a, sizeof(t_aux));
	a.k = is_path(ex, g);
	if (a.k == E_CNF || a.k == 126)
		return ((ex->stt = ((a.k == E_CNF) * E_CNF) + ((a.k == 126) * 126)
				+ ((a.k == 0) * 0 + ERROR)));
	ex->pth = ft_split(path, ':');
	if (!ex->pth)
		exit (msg_error(E_MEM, 1, NULL));
	if (search_path(ex, g, &a) == SUCCESS)
		return ((ex->stt = SUCCESS));
	ex->cmd = ft_strdup_exit(g->arg[0]);
	return (ERROR);
}
