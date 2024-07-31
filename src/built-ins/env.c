/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 12:49:47 by dacortes          #+#    #+#             */
/*   Updated: 2024/07/31 18:48:41 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	add_variable_env(t_basic_list **list_env, char *key, char *value, short eql)
{
	t_basic_list *new_node;

	if (!key)
		exit (error_msg(MALLOC, 1, "add_variable_env: key"));
	if (!value)
		exit (error_msg(MALLOC, 1, "add_variable_env: value"));
	new_node = ft_calloc(1, sizeof(t_basic_list));
	if (!new_node)
		exit (error_msg(MALLOC, 1, "add_variable_env: new_node"));
	new_node->list_content.env = ft_calloc(1, sizeof(t_env));
	if (!new_node->list_content.env)
		exit (error_msg(MALLOC, 1, "add_variable_env: new_node->env"));
	new_node->list_content.env->key = key;
	new_node->list_content.env->value = value;
	new_node->list_content.env->eql = eql;
	new_node->next = NULL;
	add_back(list_env, new_node);
	return (EXIT_SUCCESS);
}

int	add_env(t_basic_list **new_env, char *line)
{
	// int	pos;
	int tmp = 0;

	// pos = ft_strchrpos(line, '=');
	add_variable_env(new_env, ft_cutdel(line, 0, '=', &tmp), \
		ft_cutdel(line, ft_strchrpos(line, '=') + 1, '\0', &tmp), TRUE);
	return (EXIT_SUCCESS);
}

t_basic_list *init_env(char **env)
{
	t_basic_list	*new_env;
	int				i;

	// if (!env || !*env)
	// 	return (init_basic_env());
	i = -1;
	new_env = NULL;
	while (env[++i])
		add_env(&new_env, env[i]);
	return (new_env);
}

void *printf_env(t_type_list content)
{
	t_env	*env;

	env = content.env;
	if (!env)
		return (NULL);
	if(env && env->eql && env->key && env->value)
	{
		ft_printf("%s=%s\n", env->key, env->value);
		printf("soy patatin\n");
	}
	else if (env && env->eql && env->key && !*env->value)
		ft_printf("%s=\n", env->key);
	else
			printf("perro\n");
	printf("ese algo\n");
	return (NULL);
}

int	_env(t_basic_list *list, int num_commands)
{
	if (num_commands > 1)
		return (error_msg(ARGUMENT, 1, "env"));
	iter_list(list, printf_env(list->list_content));
	return (EXIT_SUCCESS);
}
