/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manager_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 14:45:41 by frankgar          #+#    #+#             */
/*   Updated: 2024/08/16 17:43:48 by frankgar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int get_env_size(t_basic *env)
{
	int		i;
	t_basic *iter;

	i = 0;
	iter = env;
	while (iter)
	{
		if (iter->data.env->eql == TRUE)
			i++;
		iter = iter->next;
	}
	return (i);
}

char **substract_env(t_minishell *mini)
{
	char	**env;
	char	*tmp;
	int		i;
	t_basic	*iter;

	i = 0;
	env = protected(ft_calloc(get_env_size(mini->env), sizeof(char *)), "env");
	iter = mini->env;
	while(iter)
	{
		if (iter->data.env->eql == TRUE)
		{
			env[i] = protected(ft_strjoin("", iter->data.env->key), "ENV");
			tmp = env[i];
			env[i] = protected(ft_strjoin(env[i], "="), "ENV");
			free (tmp);
			tmp = env[i];
			env[i] = protected(ft_strjoin(env[i], iter->data.env->value), "ENV");
			free(tmp);
			i++;
		}
		iter = iter->next;
	}
	return (env);
}

char	*select_cmd_path(char **path, char *cmd)
{
	int		x;
	char	*tmp;
	char	*cmd_path;

	x = -1;
	cmd_path = NULL;
	while (path[++x] && !cmd_path)
	{
		tmp = protected(ft_strjoin(path[x], cmd), "CMD");
		if (access(tmp, F_OK) == 0)
			cmd_path = protected(ft_strdup(tmp), "CMD");
		if (tmp)
		{
			free(tmp);
			tmp = NULL;
		}
		if (path[x])
		{
			free(path[x]);
			tmp = NULL;
		}
	}
	return (cmd_path);
}

char *get_path(t_minishell *mini, char *cmd)
{
	char	**path;
	char	*tmp;
	int		i;

	i = -1;
	/*if (ft_strcharpos(cmd, "/") != -1)
		return ("");*/
	path = protected(ft_split(search_env(mini->env, "PATH", 2), ':'), "PATH");
	while (path[++i])
	{
		tmp = path[i];
		path[i] = protected(ft_strjoin(path[i], "/"), "PATH");
		free(tmp);
	}
	tmp = select_cmd_path(path, cmd);
	free(path);
	if (!tmp)
		return (cmd);
	return(tmp);
}
