/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacortes <dacortes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 14:05:14 by dacortes          #+#    #+#             */
/*   Updated: 2023/08/23 10:22:12 by dacortes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/shell_mini.h"

int	add_key(t_mini *sh, char *key, char *val, int eql)
{
	t_env *new;

	new = ft_calloc(sizeof(t_env), 1);
	if (!new)
		exit (msg_error(E_MEM, 1, NULL));
	new->key = key;
	new->val = val;
	new->eql = eql;
	new->next = sh->env;
	sh->env = new;
	return (SUCCESS);
	sh->size++;
}

int	init_env(t_mini *sh, char **env)
{
	int	key;
	int	val;
	int	i;

	i = 0;
	while (env[i])
	{
		key = ft_strchrpos(env[i], '=');
		val = (ft_strlen(env[i]) - key);
		add_key(sh, ft_substr(env[i], 0, key), ft_substr(env[i], key + 1, val),
			(ft_strchrpos(env[i], '=') >= 0));
		i++;
	}
	return (SUCCESS);
}

void	show_env(t_env *env)
{
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		if (tmp->eql && tmp->val)
			ft_printf("%s=%s\n", tmp->var, tmp->val);
		else if (tmp->eql && !tmp->val)
			ft_printf("%s=\n", tmp->var);
		tmp = tmp->next;
	}
}