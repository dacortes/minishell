/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacortes <dacortes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 12:49:47 by dacortes          #+#    #+#             */
/*   Updated: 2024/07/20 11:50:28 by dacortes         ###   ########.fr       */
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

// static t_env	*init_basic_env(void)
// {
// 	t_env	*result;
// 	t_env	*new;

// 	result = NULL;
// 	new = ft_calloc(sizeof(t_env), 1);
// 	if (!new)
// 		exit(-1);
// 	new->key = ft_strdup("PWD");
// 	new->value = ft_strdup("funcion que verifique el path actual");
// 	new->eql = TRUE;
// 	add_back((void **)&result, new, sizeof(t_env));
// 	new = ft_calloc(sizeof(t_env), 1);
// 	if (!new)
// 		exit (error_msg(MALLOC, 1, "init_basic_env: new"));
// 	new->key = ft_strdup("SHLVL");
// 	new->value = ft_strdup("1");
// 	new->eql = TRUE;
// 	add_back((void **)&result, new, sizeof(t_env));
// 	return (result);
// }

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

// int add_env(t_env **env, char *line)
// {
// 	t_env	*new;
// 	int		pos;

// 	new = ft_calloc(sizeof(t_env), 1);
// 	if (!new)
// 		exit (error_msg(MALLOC, 1, "init_env: new"));
// 	pos = ft_strchrpos(line, '=');
// 	return (EXIT_SUCCESS);
// }

t_env	*init_env(char **env)
{
	t_env	*result;
	t_env	*new;
	int		pos;
	int		i;

	if (!env || !*env)
		return (init_basic_env());
	i = -1;
	result = NULL;
	while (env[++i])
	{
		new = ft_calloc(sizeof(t_env), 1);
		if (!new)
			exit (error_msg(MALLOC, 1, "init_env: new"));
		int tmp = 0;
		pos = ft_strchrpos(env[i], '=');
		if (pos ==  ERROR)
			add_variable_env(&result, ft_cutdel(env[i], 0, '\0', &tmp), \
				ft_cutdel(env[i], ft_strchrpos(env[i], '='), '\0', &tmp), \
				FALSE);
		else
			add_variable_env(&result, ft_cutdel(env[i], 0, '=', &tmp), \
				ft_cutdel(env[i], ft_strchrpos(env[i], '=') + 1, '\0', &tmp), \
				TRUE);
	}
	return (result);
}