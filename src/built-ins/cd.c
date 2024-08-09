/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 10:52:18 by codespace         #+#    #+#             */
/*   Updated: 2024/08/09 10:43:28 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	replace(t_basic **env, char	*key, char *value)
{
	t_basic *found;

	found = bool_loop(*env, key_compare, key);
	if (found)
	{
		free(found->data.env->value);
		found->data.env->value = ft_strdup(value);
        if (!found->data.env->value)
            exit(error_msg(MALLOC, 1, "replace: iter->new"));
		return (TRUE);
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

int	update_oldpwd(t_minishell *mini, char *dir)
{
	char	*find;

	find = search_env(mini->env, "OLDPWD", KEY);
	if (find && !*find)
		add_env(&mini->env, "OLDPWD=");
	replace(&mini->env, "OLDPWD", dir);
	//tener cuidado con la memoria dinamica de cur_dir
	// ft_free(mini->old_dir, NULL);
	// mini->old_dir = mini->cur_dir;
	// ft_free(mini->cur_dir, NULL);
	// mini->cur_dir = dir;
	return (EXIT_SUCCESS);
}

int	update_pwd(t_minishell *mini, char *path)
{
	char	*dir;

	if (!path || !ft_strlen(path))
	{
		if (chdir(search_env(mini->env, "HOME", VALUE)) != 0)
			return (error_msg(PERROR, 1, "chdir: HOME"));
	}
	else if (chdir(path) == ERROR)
	{
		if (access(path, R_OK | W_OK | X_OK))
			return (error_msg(PERROR, 1, "cd"));
		return (error_msg(PERROR, 1, "cd"));
	}
	dir = get_pwd();
	if (!dir)
		return (1);
	replace(&mini->env, "PWD", dir);
	if (ft_strncmp(dir, mini->cur_dir, PATH_MAX) != 0)
		update_oldpwd(mini, dir);
	return (EXIT_SUCCESS);
}

int	_cd(t_minishell *mini, char **command, int num_arg)
{
	if (num_arg > 2)
		return (error_msg(ARGUMENT, 1, "cd"));
	if (num_arg == 1)
		update_pwd(mini, "");
	else
		update_pwd(mini, command[1]);
	return (EXIT_SUCCESS);
}