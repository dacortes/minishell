/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacortes <dacortes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 14:06:54 by dacortes          #+#    #+#             */
/*   Updated: 2023/07/15 18:22:24 by dacortes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/shell_mini.h"

int	replace_val(t_env *env, char *var, char *val)
{
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		if (ft_strncmp(tmp->var, var, ft_strlen(var)) == 0)
		{
			free(var);
			if (tmp->val)
				free(tmp->val);
			tmp->val = val;
			ft_printf(Y"Estoy aqui %s\n"E, val);
			return (TRUE);
		}
		tmp = tmp->next;
	}
	return (FALSE);
}

int	add_var_env(t_mini *sh, char *var, char *val)
{
	t_env	*new;

	new = (t_env *)ft_calloc(sizeof(t_env), 1);
	if (!new)
		exit (msg_error(E_MEM, 1, NULL));
	new->var = var;
	new->val = val;
	new->next = NULL;
	if (sh->e_size > 0)
	{
		new->next = sh->env;
		sh->env = new;
	}
	sh->e_size++;
	return (SUCCESS);
}

int	export(t_mini *sh, char *str)
{
	char	*var;
	char	*val;
	int		len_r;
	int 	len_k;

	len_r = ft_strchrpos(str, '=');
	len_k = (ft_strlen(str) - len_r);
	var = ft_substr(str, 0, len_r);
	val = ft_substr(str, len_r + 1, len_k);
	ft_printf(B"%s\n"E, val);
	if (!var || !val)
		exit (msg_error(E_MEM, 1, NULL));
	if (ft_strchrpos(str, '=') == ERROR)
	{
		free(val);
		val = NULL;
	}
	if (replace_val(sh->env, var, val))
		;
	else
		add_var_env(sh, var, val);
	return (SUCCESS);
}
