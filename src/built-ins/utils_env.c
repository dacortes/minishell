/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacortes <dacortes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 09:36:38 by dacortes          #+#    #+#             */
/*   Updated: 2024/08/18 18:33:00 by frankgar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	printf_env(void *content)
{
	t_env	*env;

	env = ((t_data_type *)content)->env;
	if (!env)
		return ;
	if (env && env->eql && env->key && env->value)
		ft_printf("%s=%s\n", env->key, env->value);
	else if (env && env->eql && env->key && !*env->value)
		ft_printf("%s=\n", env->key);
}

int	parsing_shlvl(char *value)
{
	int	size;

	size = ft_strlen(value);
	if (size == 0 || ((size > 10 && value[0] != '-')
			&& (size > 10 && value[0] != '+')) || size > 11)
		return (0);
	if (value[0] != '-' && size == 10
		&& ft_strncmp(value, "2147483647", 10) > 0)
		return (0);
	if (value[0] == '-' && size == 11
		&& ft_strncmp(value, "-2147483648", 11) > 0)
		return (0);
	if (value[0] == '+' && size == 11
		&& ft_strncmp(value, "+2147483647", 11) > 0)
		return (0);
	return (ft_atoi(value));
}

char	*is_shlvl(char *key, char *value)
{
	int		shlvl;

	shlvl = 0;
	if (ft_strncmp(key, "SHLVL", -1) == FOUND)
	{
		shlvl = parsing_shlvl(value);
		if (shlvl < 0 || shlvl >= 1000)
			shlvl = 0;
		shlvl++;
		free(value);
		value = ft_itoa(shlvl);
	}
	return (value);
}

int	key_compare(t_data_type *data, void *key)
{
	return (!ft_strncmp(data->env->key, (char *)key, -1));
}

char	*search_env(t_basic *env, char *key, int type)
{
	t_basic	*find;

	find = bool_loop(env, key_compare, key);
	if (!find)
		return ("");
	if (type == KEY)
		return (find->data.env->key);
	else if (type == VALUE)
		return (find->data.env->value);
	return ("");
}
