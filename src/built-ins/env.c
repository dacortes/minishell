/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 12:49:47 by dacortes          #+#    #+#             */
/*   Updated: 2024/08/02 13:52:20 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	add_variable_env(t_basic **list_env, char *key, char *value, short eql)
{
	t_basic *new_node;

	if (!key)
		exit (error_msg(MALLOC, 1, "add_variable_env: key"));
	if (!value)
		exit (error_msg(MALLOC, 1, "add_variable_env: value"));
	new_node = ft_calloc(1, sizeof(t_basic));
	if (!new_node)
		exit (error_msg(MALLOC, 1, "add_variable_env: new_node"));
	new_node->data.env = ft_calloc(1, sizeof(t_env));
	if (!new_node->data.env)
		exit (error_msg(MALLOC, 1, "add_variable_env: new_node->env"));
	new_node->data.env->key = key;
	new_node->data.env->value = is_shlvl(key, value);
	new_node->data.env->eql = eql;
	new_node->next = NULL;
	add_back(list_env, new_node);
	return (EXIT_SUCCESS);
}

static t_basic	*init_basic_env(void)
{
	t_basic	*list_env;

	list_env = NULL;
	add_variable_env(&list_env, ft_strdup("PWD"), get_pwd(), TRUE);
	add_variable_env(&list_env, ft_strdup("SHLVL"), ft_strdup("1"), TRUE);
	return (list_env);
}

int	add_env(t_basic **new_env, char *line)
{
	int	pos;
	int tmp = 0;

	pos = ft_strchrpos(line, '=');
	if (pos == NOT_FOUND)
	{
		add_variable_env(new_env, ft_cutdel(line, 0, '\0', &tmp), \
			ft_cutdel(line, ft_strchrpos(line, '='), '\0', &tmp), FALSE);
	}
	else
	{
		add_variable_env(new_env, ft_cutdel(line, 0, '=', &tmp), \
			ft_cutdel(line, ft_strchrpos(line, '=') + 1, '\0', &tmp), TRUE);
	}
	return (EXIT_SUCCESS);
}

t_basic *init_env(char **env)
{
	t_basic	*new_env;
	int				i;

	if (!env || !*env)
		return (init_basic_env());
	i = -1;
	new_env = NULL;
	while (env[++i])
		add_env(&new_env, env[i]);
	return (new_env);
}

int	_env(t_basic *list, int num_commands)
{
	if (num_commands > 1)
		return (error_msg(ARGUMENT, 1, "env"));
	content_loop(list, printf_env);
	return (EXIT_SUCCESS);
}
