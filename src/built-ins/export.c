/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacortes <dacortes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 14:06:54 by dacortes          #+#    #+#             */
/*   Updated: 2023/07/17 18:20:29 by dacortes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/shell_mini.h"

int	replace_val(t_env *env, char *var, char *val, int eql)
{
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		if (ft_strncmp(tmp->var, var, -1) == 0)
		{
			free(var);
			if (tmp->eql && ft_strncmp(tmp->val, "", sizeof("")) != 0)
				free(tmp->val);
			tmp->val = val;
			tmp->eql = eql;
			ft_printf(F"status eql:%d\n", tmp->eql);
			return (TRUE);
		}
		tmp = tmp->next;
	}
	return (FALSE);
}

static int	check_exp_var(char *str)
{
	int	i;

	i = 1;
	if (!ft_isalpha(str[0]) && str[0] != '_')
		return (TRUE);
	while (str[i] && str[i] != '=')
	{
		if (!ft_isalnum(str[i]) || !ft_isalnum(str[i]))
			return (TRUE);
		i++;
	}
	return (SUCCESS);
}

void	put_value_null(t_axu aux, char *str)
{
	if (ft_strchrpos(str, '=') && !str[aux.len_r + 1])
	{
		aux.eql = TRUE;
		free(aux.val);
		aux.val = "";
	}
	if (ft_strchrpos(str, '=') == ERROR)
	{
		aux.eql = FALSE;
		free(aux.val);
		aux.val = NULL;
	}
}

int	export(t_mini *sh, char *str)
{
	t_axu	aux;

	if (check_exp_var(str))
		return (msg_error(E_EXP, 1, str));
	aux.eql = FALSE;
	aux.len_r = ft_strchrpos(str, '=');
	aux.len_k = (ft_strlen(str) - aux.len_r);
	aux.var = ft_substr(str, 0, aux.len_r);
	aux.val = ft_substr(str, aux.len_r + 1, aux.len_k);
	if (!aux.var || !aux.val)
		exit (msg_error(E_MEM, 1, NULL));
	if (ft_strchrpos(str, '=') && str[aux.len_r + 1])
		aux.eql = TRUE;
	if (ft_strchrpos(str, '=') && !str[aux.len_r + 1])
	{
		aux.eql = TRUE;
		free(aux.val);
		aux.val = "";
	}
	if (ft_strchrpos(str, '=') == ERROR)
	{
		aux.eql = FALSE;
		free(aux.val);
		aux.val = NULL;
	}
	// put_value_null(aux, str);
	if (replace_val(sh->env, aux.var, aux.val, aux.eql))
		;
	else
		add_var_env(sh, aux.var, aux.val, aux.eql);
	return (SUCCESS);
}

void	print_export(t_env *env)
{
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		if (!tmp->eql && !tmp->val)
			ft_printf("%s\n", tmp->var);
		else if (tmp->eql && !tmp->val)
			ft_printf("%s=\"\"\n", tmp->var);
		else
			ft_printf("%s=\"%s\"\n", tmp->var, tmp->val);
		tmp = tmp->next;
	}
}
