/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacortes <dacortes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 12:49:47 by dacortes          #+#    #+#             */
/*   Updated: 2024/07/20 14:48:40 by dacortes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	add_variable_env(t_env **env, char *key, char *value, short eql)
{
	t_env	*new;

	if (!key)
		exit (error_msg(MALLOC, 1, "add_variable_env: key"));
	if (!value)
		exit (error_msg(MALLOC, 1, "add_variable_env: value"));
	new = ft_calloc(sizeof(t_env), 1);
	if (!new)
		exit (error_msg(MALLOC, 1, "add_variable_env: new"));
	new->key = key;
	new->value = value;
	new->eql = eql;
	new->next = NULL;
	add_back((void **)env, new, sizeof(t_env));
	return (EXIT_SUCCESS);
}

//enlazar con la funcion que busca el path
static t_env	*init_basic_env(void)
{
	t_env	*result;

	result = NULL;
	add_variable_env(&result, ft_strdup("PWD"), ft_strdup("agregar el path actual"), TRUE);
	add_variable_env(&result, ft_strdup("SHLVL"), ft_strdup("1"), TRUE);
	return (result);
}

int	clear_env(t_env **env)
{
	t_env	*clear;

	while (*env)
	{
		clear = *env;
		*env = (*env)->next;
		ft_free(&clear->key, &clear->value);
		free(clear);
	}
	return (EXIT_SUCCESS);
}

int add_env(t_env **env, char *line)
{
	t_env	*new;
	int		pos;
	int		tmp;

	new = ft_calloc(sizeof(t_env), 1);
	if (!new)
		exit (error_msg(MALLOC, 1, "init_env: new"));
	tmp = 0;
	pos = ft_strchrpos(line, '=');
	if (pos == NOT_FOUND)
		add_variable_env(env, ft_cutdel(line, 0, '\0', &tmp), \
			ft_cutdel(line, ft_strchrpos(line, '='), '\0', &tmp), FALSE);
	else
		add_variable_env(env, ft_cutdel(line, 0, '=', &tmp), \
		ft_cutdel(line, ft_strchrpos(line, '=') + 1, '\0', &tmp), TRUE);
	return (EXIT_SUCCESS);
}

t_env	*init_env(char **env)
{
	t_env	*result;
	int		i;

	if (!env || !*env)
		return (init_basic_env());
	i = -1;
	result = NULL;
	while (env[++i])
		add_env(&result, env[i]);
	return (result);
}

int	_env(t_env *env, int num_commands)
{
	t_env	*iter;

	if (num_commands > 1)
		return (error_msg(ARGUMENT, 1, "env"));
	iter = env;
	while (iter)
	{
		if (iter->eql && iter->value)
			ft_printf("%s=%s\n", iter->key, iter->value);
		else if (iter->eql && !iter->key)
			ft_printf("%s=\n", iter->key);
		iter = iter->next;
	}
	return (EXIT_SUCCESS);
}
