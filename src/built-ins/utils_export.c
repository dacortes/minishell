/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 10:40:56 by codespace         #+#    #+#             */
/*   Updated: 2024/08/04 10:41:19 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void printf_export(void *content)
{
	t_env	*env;

	env = ((t_data_type *)content)->env;
	if (!env)
		return ;
	if (!env->eql)
		ft_printf("declare -x %s\n", env->key);
	else if (env->eql && !env->value[0])
		ft_printf("declare -x %s=\"\"\n", env->key);
	else
		ft_printf("declare -x %s=\"%s\"\n", env->key, env->value);
}
