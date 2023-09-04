/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcespede <fcespede@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 14:05:09 by dacortes          #+#    #+#             */
/*   Updated: 2023/09/03 18:18:39 by fcespede         ###   ########.fr       */
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

int	cd(char *path, t_mini **sh)
{
	char	dir[PATH_MAX];

	if (!path || ft_strlen(path) == 0)
	{
		if (chdir(search_env((*sh)->env, "HOME", VAL)) != 0)
			return (msg_error(E_NSF, E_EXIT, "chdir"));
	}
	else if (chdir(path) != 0)
		return (msg_error(E_NSF, E_EXIT, "chdir"));
	if (getcwd(dir, sizeof(dir)) == NULL)
		return (msg_error(E_PRR, E_EXIT, "getcwd"));
	replace((*sh)->env, "PWD", dir);
	if (ft_strncmp(dir, (*sh)->dir, PATH_MAX) != 0)
	{
		replace((*sh)->env, "OLDPWD", (*sh)->dir);
		free((*sh)->old);
		(*sh)->old = ft_strdup_exit((*sh)->dir);
		free((*sh)->dir);
		(*sh)->dir = ft_strdup_exit(dir);
	}
	return (SUCCESS);
}

int	ft_cd(t_line *ln, t_mini **sh)
{
	if (ln->argc > 2)
		return (msg_error(E_ARG, 1, "cd"));
	else if (ln->argc == 2)
		cd(ln->argv[1], sh);
	else
		cd("", sh);
	return (SUCCESS);
}
