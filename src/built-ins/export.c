/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 15:21:04 by dacortes          #+#    #+#             */
/*   Updated: 2024/08/09 15:02:01 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	check_key(char *key, int *flag)
{
	int	i;

	if (!key)
		return (FALSE);
	if (!ft_isalpha(key[0]) && key[0] != '_')
		return (FALSE);
	i = 1;
	while (key[i] && key[i] != '+' && key[i] != '=')
	{
		if (!ft_isalnum(key[i]) && !ft_isalpha(key[i]))
			return (FALSE);
		i++;
	}
	if (key[i] == '+')
		*flag = i;
	if (*flag == NOT_FOUND && !key[i])
		return (TRUE);
	if ((*flag != NOT_FOUND && key[i + 1] && key[i + 1] != '=')
		|| (*flag && !key[i + 1]))
		return(FALSE);
	return (TRUE);
}

int	replace_plus_equal(t_basic **env, char *key, char *value)
{
	char	*new_value;
	char	*find_value;

	find_value = search_env(*env, key, VALUE);
	new_value = ft_strjoin(find_value, value);
	if (!new_value)
 		exit(error_msg(MALLOC, 1, "replace_plus_equal: new_value"));
	replace(env, key, new_value);
	free(new_value);
	return (EXIT_SUCCESS);
}

int	add_export(t_basic **env, char *line)
{
	t_env	aux;
	int		pos;
	int		foo;

	foo = NOT_FOUND;
	if (!check_key(line, &foo))
		return (error_msg(EXPORT, 1, line));
	pos = ft_strchrpos(line, '=');
	if (pos == NOT_FOUND)
		pos = ft_strlen(line);
	aux.key = ft_strndup(line, pos - (foo != NOT_FOUND && line[foo] == '+'));
	if (!aux.key)
		exit (error_msg(MALLOC, 1, "add_export: aux.key"));
	if (foo != NOT_FOUND && foo < pos)
		ft_memmove(&line[foo], &line[foo + 1], ft_strlen(&line[foo + 1]) + 1);
	pos += (line[pos] == '=') * 1;
	aux.value = search_env(*env, aux.key, KEY);
	if (!*aux.value)
		add_env(env, line);
	else if (*aux.value && pos != NOT_FOUND)
		replace_plus_equal(env, aux.key, &line[pos]);
	else if (*aux.value && pos == NOT_FOUND)
		replace(env, aux.key, &line[pos]);
	return (free(aux.key), EXIT_SUCCESS);
}

int	export_loop(t_basic **env, char **command)
{
	int	status;
	int	i = 1;

	status = 0;
	while (command[i])
	{
		if (add_export(env, command[i]))
			status = 1;
		i++;
	}
	add_prev(env, FALSE);
	return (status);
}

int	_export(t_basic *env)
{
	content_loop(env, printf_export);
	return (EXIT_SUCCESS);
}