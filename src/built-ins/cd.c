/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacortes <dacortes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 16:07:55 by dacortes          #+#    #+#             */
/*   Updated: 2023/07/19 17:57:58 by dacortes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/shell_mini.h"

/* si el home no tiene nada */
/* tenemos que guardar la ubicacion del pwd el actual y el old */
/* hay que crear un getenv propio para saber puntualmente donde se encuentra*/

int	replace_static(t_env *env, char *var, char *val, int eql)
{
	t_env *tmp;

	tmp = env;
	while (tmp)
	{
		if (ft_strncmp(tmp->var, var, -1) == 0)
		{
			if (ft_strncmp(tmp->val, val, -1) != 0)
				free(tmp->val);
			tmp->val = val;
			tmp->eql = eql;
			return (TRUE);
		}
		tmp = tmp->next;
	}
	return (SUCCESS);
}

int	cd(char *path, t_mini **sh)
{
	char	dir[PATH_MAX];
	int		check;

	check = 0;
	if (sizeof(path) >= PATH_MAX)
		return (msg_error(E_NSF, E_EXIT, "chdir"));
	if (!path)
	{
		check = chdir(find_var_env((*sh)->env, "HOME", VAR));
			return (msg_error(E_NSF, E_EXIT, "chdir"));
		if (getcwd(dir, sizeof(dir)) == NULL)
			return(msg_error(E_PRR, E_EXIT, "getcwd"));
		replace_static((*sh)->env, "PWD", dir, TRUE);
		ft_printf("%s\n", dir);
	}
	else
	{
		check = chdir(path);
		if (check < SUCCESS)
			return (msg_error(E_NSF, E_EXIT, "chdir"));
		if (getcwd(dir, sizeof(dir)) == NULL)
			return(msg_error(E_PRR, E_EXIT, "getcwd"));
		replace_static((*sh)->env, "PWD", dir, TRUE);
		if (ft_strncmp(dir, (*sh)->dir, -1) != 0)
		{
			free((*sh)->old);
			(*sh)->old = (*sh)->dir;
			(*sh)->dir = ft_strdup(dir);
		}
		ft_printf("%s\n", dir);
	}
	return (SUCCESS);
}
