/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacortes <dacortes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 14:05:24 by dacortes          #+#    #+#             */
/*   Updated: 2023/08/23 15:28:29 by dacortes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/shell_mini.h"

int	check_key(char *inp)
{
	int	i;

	if (!ft_isalpha(inp[0]) && inp[0] != '_')
		return (TRUE);
	i = 1;
	while (inp[i] && inp[i] != '=')
	{
		if (!ft_isalnum(inp[i]) || !ft_isalpha(inp[i]))
			return (TRUE);
		i++;
	}
	return (SUCCESS);
}

int	is_it_replaceable(t_env *env, t_aux tmp)
{
	t_env	*find;

	find = env;
	while (find)
	{
		if (ft_strncmp(find->key, tmp._key, -1) == 0)
		{
			if (find->eql && ft_strncmp(find->val, "", sizeof("")) != 0)
				free(find->val);
			find->val = ft_strdup(tmp._val);
			find->eql = tmp.eql;
			return (TRUE);
		}
		find = find->next;
	}
	return (FALSE);
}

void	put_value_null(t_aux *tmp, char *inp)
{
	if (tmp->eql && !inp[tmp->val + 1])
	{
		free(tmp->_val);
		tmp->_val = ft_strdup("");
		if (!tmp->_val)
			exit (msg_error(E_MEM, 1, NULL));
	}
	else if (!tmp->eql)
	{
		free(tmp->_val);
		tmp->_val = NULL;
	}
}

/* queda un leak de m emoria */
int	_export(t_mini *sh, char *inp)
{
	t_aux tmp;

	if (check_key(inp))
		return (msg_error(E_EXP, 1, inp));
	tmp.eql = (ft_strchrpos(inp, '=') >= 0);
	tmp.key = ft_strchrpos(inp, '=');
	tmp.val = (ft_strlen(inp) - tmp.key);
	tmp._key = ft_substr(inp, 0, tmp.key);
	tmp._val = ft_substr(inp, tmp.key + 1, tmp.val);
	put_value_null(&tmp, inp);
	if (!tmp._key || !tmp._val)
		exit (msg_error(E_MEM, 1, NULL));
	if (is_it_replaceable(sh->env, tmp))
		;
	else
		add_key(sh, tmp._key, tmp._val, tmp.eql);
	free(tmp._key);
	free(tmp._val);
	return (SUCCESS);
}