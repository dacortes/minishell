/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacortes <dacortes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 16:07:55 by dacortes          #+#    #+#             */
/*   Updated: 2023/07/17 19:58:57 by dacortes         ###   ########.fr       */
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
	(void)sh;
	char	dir[PATH_MAX];
	int		chek;

	if (sizeof(path) >= PATH_MAX)
		return (msg_error(E_NSF, E_EXIT, "chdir"));
	if (!path)
	{
		chdir(getenv("HOME"));
		/* esto hay que cambiarlo hay 
		que actualizar el olpwd al new*/
		if (getcwd(dir, sizeof(dir)) == NULL)
			return(msg_error(E_PRR, E_EXIT, "getcwd"));
		replace_static((*sh)->env, "PWD", dir, TRUE);
		ft_printf("%s\n", dir);
	}
	chek = chdir(path);
	if (path && chek < SUCCESS)
		return (msg_error(E_NSF, E_EXIT, "chdir"));
	else if (path && chek == SUCCESS)
	{
		if (getcwd(dir, sizeof(dir)) == NULL)
			return(msg_error(E_PRR, E_EXIT, "getcwd"));
		replace_static((*sh)->env, "PWD", dir, TRUE);
		(*sh)->dir = dir;
		ft_printf("%s\n", dir);
	}
	return (SUCCESS);
}

/* test */
// int	cd(char *path, t_mini **sh)
// {
// 	char	dir[PATH_MAX];
// 	int		chek;

// 	if (sizeof(path) >= PATH_MAX)
// 		return (msg_error(E_NSF, E_EXIT, "chdir"));
// 	if (!path)
// 	{
// 		chdir(getenv("HOME"));

// 		if (getcwd(dir, sizeof(dir)) == NULL)
// 			return(msg_error(E_PRR, E_EXIT, "getcwd"));
// 		ft_printf("%s\n", dir);
// 	}
// 	return (SUCCESS);
// }