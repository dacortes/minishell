/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacortes <dacortes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 14:06:54 by dacortes          #+#    #+#             */
/*   Updated: 2023/07/17 10:31:10 by dacortes         ###   ########.fr       */
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

int	check_exp_var(char *str)
{
	int	i;

	i = 1;
	if (!ft_isalpha(str[0]) && str[0] != '_')
		return (TRUE);
	while(str[i] && str[i] != '=')
	{
		if (!ft_isalnum(str[i]) || !ft_isalnum(str[i]))
			return (TRUE);
		i++;
	}
	return (SUCCESS);
}
/*
si se le ingresa a= pero sin valor, el valor tiene una str vacia
*/
int	export(t_mini *sh, char *str)
{
	char	*var;
	char	*val;
	int		len_r;
	int		len_k;

	if (check_exp_var(str))
		return (msg_error(E_EXP, 1, str));
	len_r = ft_strchrpos(str, '=');
	len_k = (ft_strlen(str) - len_r);
	var = ft_substr(str, 0, len_r);
	val = ft_substr(str, len_r + 1, len_k);
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
