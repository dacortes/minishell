/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manager_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frankgar <frankgar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 14:45:41 by frankgar          #+#    #+#             */
/*   Updated: 2024/08/19 09:48:54 by frankgar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	get_env_size(t_basic *env)
{
	int		i;
	t_basic	*iter;

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

char	**substract_env(t_minishell *mini)
{
	char	**env;
	char	*tmp;
	int		i;
	t_basic	*iter;

	i = 0;
	env = protected(ft_calloc(get_env_size(mini->env), sizeof(char *)), "env");
	iter = mini->env;
	while (iter)
	{
		if (iter->data.env->eql == TRUE)
		{
			env[i] = protected(ft_strjoin("", iter->data.env->key), "ENV");
			tmp = env[i];
			env[i] = protected(ft_strjoin(env[i], "="), "ENV");
			free (tmp);
			tmp = env[i];
			env[i] = protected
				(ft_strjoin(env[i], iter->data.env->value), "ENV");
			free(tmp);
			i++;
		}
		iter = iter->next;
	}
	return (env);
}

char	*select_cmd_path(char **path, char *cmd)
{
	int		i;
	char	*tmp;
	char	*cmd_path;

	i = -1;
	cmd_path = NULL;
	while (path[++i] && !cmd_path)
	{
		tmp = protected(ft_strjoin(path[i], cmd), "CMD");
		if (access(tmp, F_OK) == 0)
			cmd_path = protected(ft_strdup(tmp), "CMD");
		if (tmp)
		{
			free(tmp);
			tmp = NULL;
		}
		if (path[i])
		{
			free(path[i]);
			tmp = NULL;
		}
	}
	if (!cmd_path)
		exit(error_msg(NO_FOUND, 127, cmd));
	return (cmd_path);
}

char	*get_executable(char *cmd)
{
	struct stat	stats;
	int			result;

	if (access(cmd, F_OK) == ERROR)
		exit(error_msg(PERROR, 127, cmd));
	result = stat(cmd, &stats);
	if (result == 0 && (stats.st_mode & S_IFMT) == S_IFDIR)
		exit(error_msg(IS_DIR, 126, cmd));
	else if (result == ERROR)
		exit(error_msg(PERROR, 1, cmd));
	return (cmd);
}

char	*get_path(t_minishell *mini, char *cmd)
{
	char	**path;
	char	*tmp;
	int		i;

	i = -1;
	if (!cmd)
		exit (mini->status);
	if (ft_strchrpos(cmd, '/') != -1)
		return (get_executable(cmd));
	path = protected(ft_split(search_env(mini->env, "PATH", 2), ':'), "PATH");
	while (path[++i])
	{
		tmp = path[i];
		path[i] = protected(ft_strjoin(path[i], "/"), "PATH");
		free(tmp);
	}
	tmp = select_cmd_path(path, cmd);
	free(path);
	return (tmp);
}
