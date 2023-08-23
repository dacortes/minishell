/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacortes <dacortes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 14:05:14 by dacortes          #+#    #+#             */
/*   Updated: 2023/08/23 15:05:35 by dacortes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/shell_mini.h"

int	add_key(t_mini *sh, char *key, char *val, int eql)
{
	t_env	*new;

	new = ft_calloc(sizeof(t_env), 1);
	if (!new)
		exit (msg_error(E_MEM, 1, NULL));
	new->key = ft_strdup((const char *)key);
	new->val = ft_strdup((const char *)val);
	new->eql = eql;
	new->next = sh->env;
	sh->env = new;
	sh->size++;
	return (SUCCESS);
}

int	init_env(t_mini *sh, char **env)
{
	t_aux	tmp;
	int		i;

	i = ft_double_ptr_len((void **)env) - 1;
	while (env[i])
	{
		tmp.key = ft_strchrpos(env[i], '=');
		tmp.val = (ft_strlen(env[i]) - tmp.key);
		tmp._key = ft_substr(env[i], 0, tmp.key);
		tmp._val = ft_substr(env[i], tmp.key + 1, tmp.val);
		if (!tmp._key || !tmp._val)
			exit (msg_error(E_MEM, 1, NULL));
		add_key(sh, tmp._key, tmp._val, (ft_strchrpos(env[i], '=') >= 0));
		free(tmp._key);
		free(tmp._val);
		i--;
	}
	return (SUCCESS);
}

void	_env(t_env *env)
{
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		if (tmp->eql && tmp->val)
			ft_printf("%s=%s\n", tmp->key, tmp->val);
		else if (tmp->eql && !tmp->key)
			ft_printf("%s=\n", tmp->key);
		tmp = tmp->next;
	}
}
