/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 10:52:18 by codespace         #+#    #+#             */
/*   Updated: 2024/07/24 09:58:18 by codespace        ###   ########.fr       */
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
			iter->value = ft_strdup(value);//
			return (TRUE);
		}
		iter = iter->next;
	}
	return (FALSE);
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
