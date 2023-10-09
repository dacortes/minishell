/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacortes <dacortes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 17:20:55 by dacortes          #+#    #+#             */
/*   Updated: 2023/10/09 10:39:54 by dacortes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/shell_mini.h"

int	clear(t_mini *sh)
{
	t_env	*rm;
	t_env	*tmp;

	rm = sh->env;
	while (rm)
	{
		tmp = rm;
		if (rm->key)
			free(rm->key);
		if (rm->val)
			free(rm->val);
		rm = rm->next;
		free(tmp);
	}
	if (sh->dir)
		free(sh->dir);
	if (sh->old)
		free(sh->old);
	free(sh);
	return (SUCCESS);
}

int	is_null(t_mini **sh, t_line **ln, t_get **g, char *inp)
{
	if (!inp)
	{
		clear(*sh);
		clear_get(g);
		clear_ln(ln);
		exit (SUCCESS);
	}
	return (SUCCESS);
}

int	clear_cmd(t_exe ex, int stt)
{
	if (stt == 1)
	{
		if (ex.cmd && *ex.cmd)
		{
			free(ex.cmd);
			ex.cmd = NULL;
		}
		clear_dptr((void **)ex.pth);
	}
	else if (stt == 2)
	{
		if (ex.stt == 0 && ex.cmd && *ex.cmd)
		{
			free(ex.cmd);
			ex.cmd = NULL;
		}
		ex.stt == 0 && clear_dptr((void **)ex.pth);
	}
	return (SUCCESS);
}

int	clear_pross(t_line **ln, t_get **g, t_exe ex)
{
	if (ex.inp && ex.inp[0] != '\0')
		add_history(ex.inp);
	clear_dptr((void **)ex.env);
	clear_get(g);
	clear_ln(ln);
	if (ex.inp)
		free(ex.inp);
	return (SUCCESS);
}
