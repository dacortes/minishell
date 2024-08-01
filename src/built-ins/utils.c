/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 09:36:38 by codespace         #+#    #+#             */
/*   Updated: 2024/08/01 09:59:23 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void printf_env(void *content)
{
	t_env	*env;

	env = ((t_type_list *)content)->env;
	if (!env)
		return ;
	if(env && env->eql && env->key && env->value)
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
	if (value[0] != '-' && size == 10 &&
		ft_strncmp(value, "2147483647", 10) > 0)
		return (0);
	if (value[0] == '-' && size == 11 &&
		ft_strncmp(value, "-2147483648", 11) > 0)
		return (0);
	if (value[0] == '+' && size == 11 &&
		ft_strncmp(value, "+2147483647", 11) > 0)
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
