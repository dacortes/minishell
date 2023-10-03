/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacortes <dacortes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 11:47:13 by dacortes          #+#    #+#             */
/*   Updated: 2023/10/03 18:53:02 by dacortes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/shell_mini.h"

/*
	split_path(search_env(sh->env, "PATH", VAL));
	cuando esta ejecutando comandos.
*/
int	get_path(t_exe *ex, t_get *g, char *path)
{
	t_aux a;

	ft_bzero(&a, sizeof(t_aux));
	ex->pht = ft_split(path, ':');
	if (!ex->pht)
		exit (msg_error(E_MEM, 1, NULL));
	if (g->arg[0] && g->arg[0][0] == '/')
		return (msg_error(E_NSF, 127, g->arg[0]));
	while (ex->pht[a.i])
	{
		a.tmp = ft_addend_char(ex->pht[a.i], '/');
		if (!a.tmp)
			exit (msg_error(E_MEM, 1, NULL));
		ex->cmd = ft_strjoin(a.tmp, g->arg[0]);
		if (!ex->cmd)
			exit (msg_error(E_MEM, 1, NULL));
		if (access(ex->cmd, 0) == SUCCESS)
		{
			ft_printf(G"%s\n"E, ex->cmd);
			free(a.tmp);
			return (TRUE);
		}
		free(ex->cmd);
		free(a.tmp);
		a.i++;
	}
	ex->cmd = ft_strdup_exit(g->arg[0]);
	ft_printf(G"%s\n"E, ex->cmd);
	return (FALSE);
}