/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacortes <dacortes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 14:05:14 by dacortes          #+#    #+#             */
/*   Updated: 2023/08/23 12:30:03 by dacortes         ###   ########.fr       */
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
	return (SUCCESS);
	sh->size++;
}

int	init_env(t_mini *sh, char **env)
{
	int		key;
	int		val;
	int		i;
	char	*_key;
	char	*_val;

	i = ft_double_ptr_len((void **)env) - 1;
	while (env[i])
	{
		key = ft_strchrpos(env[i], '=');
		val = (ft_strlen(env[i]) - key);
		_key = ft_substr(env[i], 0, key);
		_val = ft_substr(env[i], key + 1, val);
		if (!_key || !_val)
			exit (msg_error(E_MEM, 1, NULL));
		add_key(sh, _key, _val, (ft_strchrpos(env[i], '=') >= 0));
		free(_key);
		free(_val);
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
