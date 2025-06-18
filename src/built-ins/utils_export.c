/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacortes <dacortes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 10:40:56 by dacortes          #+#    #+#             */
/*   Updated: 2024/08/18 18:33:47 by frankgar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	printf_export(void *content)
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
