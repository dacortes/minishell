/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacortes <dacortes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 11:45:03 by dacortes          #+#    #+#             */
/*   Updated: 2023/07/15 16:40:35 by dacortes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/shell_mini.h"

int	new_var_env(t_mini *shell, char *var)
{
	t_env	*new;
	int		len_r;
	int		len_l;

	len_r = ft_strchrpos(var, '=');
	len_l = (ft_strlen(var) - len_r);
	new = (t_env *)ft_calloc(sizeof(t_env), 1);
	if (!new)
		exit (msg_error(E_MEM, 1, NULL));
	new->var = ft_substr(var, 0, len_r);
	if (!new->var)
		exit (msg_error(E_MEM, 1, NULL));
	new->val = ft_substr(var, len_r + 1, len_l);
	if (!new->val)
		exit (msg_error(E_MEM, 1, NULL));
	new->next = NULL;
	if (shell->e_size == 0)
		shell->env = new;
	else
	{
		new->next = shell->env;
		shell->env = new;
	}
	shell->e_size++;
	return (SUCCESS);
}

char	*find_var_env(t_env *env, char *find, int type)
{
	t_env	*tmp;

	tmp = env;
	if (type == KEY)
	{
		while (tmp)
		{
			if (ft_strncmp(tmp->var, find, ft_strlen(find)) == 0)
				return (tmp->val);
			tmp = tmp->next;
		}
	}
	else if (type == VAR)
	{
		while (tmp)
		{
			if (ft_strncmp(tmp->val, find, ft_strlen(find)) == 0)
				return (tmp->var);
			tmp = tmp->next;
		}
	}
	return (NULL);
}

void	printf_env(t_env *env)
{
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		if (tmp->val)
			printf("%s=%s\n", tmp->var, tmp->val);
		tmp = tmp->next;
	}
}
