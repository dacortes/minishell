/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacortes <dacortes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 14:05:09 by dacortes          #+#    #+#             */
/*   Updated: 2023/11/13 16:06:14 by dacortes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/shell_mini.h"

int	replace(t_env *env, char *key, char *val)
{
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		if (ft_strncmp(tmp->key, key, ft_strlen(key)) == 0)
		{
			free(tmp->val);
			tmp->val = ft_strdup_exit(val);
			return (TRUE);
		}
		tmp = tmp->next;
	}
	return (FALSE);
}

int	act_oldpwd(t_mini **sh, char *dir)
{
	char	*find;

	find = search_env((*sh)->env, "OLDPWD", KEY);
	if (find && find[0] == '\0')
		_export(*sh, "OLDPWD=");
	replace((*sh)->env, "OLDPWD", (*sh)->dir);
	free((*sh)->old);
	(*sh)->old = ft_strdup_exit((*sh)->dir);
	free((*sh)->dir);
	(*sh)->dir = ft_strdup_exit(dir);
	return (SUCCESS);
}

int	cd(char *path, t_mini **sh)
{
	char	dir[PATH_MAX];

	if (!path || ft_strlen(path) == 0)
	{
		if (chdir(search_env((*sh)->env, "HOME", VAL)) != 0)
			return (msg_error(E_NSF, E_EXIT, "chdir"));
	}
	else if (chdir(path) != 0)
	{
		if (access(path, R_OK | W_OK | X_OK))
			return (msg_error(E_NSF, TRUE, "cd"));
		return (msg_error(E_NSF, E_EXIT, "cd"));
	}
	if (getcwd(dir, sizeof(dir)) == NULL)
		return (msg_error(E_PRR, E_EXIT, "getcwd"));
	replace((*sh)->env, "PWD", dir);
	if (ft_strncmp(dir, (*sh)->dir, PATH_MAX) != 0)
		act_oldpwd(sh, dir);
	return (SUCCESS);
}

int	ft_cd(t_mini **sh, t_get *g, int n_cmd)
{
	int	stt;

	stt = SUCCESS;
	if (n_cmd >= 2 && g->arg[1][0] != '\0')
		stt = cd(g->arg[1], sh);
	else if (n_cmd == 1)
		stt = cd("", sh);
	return (stt);
}
