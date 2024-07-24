/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 10:52:18 by codespace         #+#    #+#             */
/*   Updated: 2024/07/24 12:27:48 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	replace(t_env **env, char *key, char *value)
{
	t_env	*iter;

	iter = *env;
	while (iter)
	{
		if (ft_strncmp(iter->key, key, ft_strlen(key)) == 0)
		{
			free(iter->value);
			iter->value = ft_strdup(value);
			if (iter->value)
				exit (error_msg(MALLOC, 1, "replace: iter->new"));
			return (TRUE);
		}
		iter = iter->next;
	}
	return (FALSE);
}

int	update_oldpwd(t_minishell **mini, char *dir)
{
	char	*find;
	(void)dir;
	find = search_env((*mini)->env, "OLDPWD", KEY);
	(void)find;
	// if (find && find[0] == '\0') si no ecuentra el OLDPWD lo crea
	// 	_export(*sh, "OLDPWD=");
	// replace((*mini)->env, "OLDPWD", (*mini)->dir);
	// free((*mini)->old);
	// (*sh)->old = ft_strdup_exit((*sh)->dir);
	// free((*mini)->dir);
	// (*sh)->dir = ft_strdup_exit(dir); // hay que hacer el promt
	return (EXIT_SUCCESS);
}

char	*get_pwd(void)
{
	char	*dir;

	dir = ft_calloc(PATH_MAX, 1);
	if (!dir)
		exit(error_msg(MALLOC, 1, "get_pwd: dir"));
	if (getcwd(dir, PATH_MAX) == NULL)
	{
		error_msg(PERROR, 1, "getcwd");
		return (NULL);
	}
	return (dir);
}
