/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacortes <dacortes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 14:06:54 by dacortes          #+#    #+#             */
/*   Updated: 2023/07/17 14:24:35 by dacortes         ###   ########.fr       */
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
			ft_printf(R"El ptr de varriable es:%p\n"E, var);
			ft_printf(R"El ptr de value es:%p\n"E, tmp->val);
			ft_printf(Y"El valor del ptr de value es :%s\n"E, tmp->val);
			free(var);
			if (tmp->eql && ft_strncmp(tmp->val, "", sizeof("")) != 0)
				free(tmp->val);
			tmp->val = val;
			return (TRUE);
		}
		tmp = tmp->next;
	}
	return (FALSE);
}

int	add_var_env(t_mini *sh, char *var, char *val, int eql)
{
	t_env	*new;

	new = (t_env *)ft_calloc(sizeof(t_env), 1);
	if (!new)
		exit (msg_error(E_MEM, 1, NULL));
	new->var = var;
	new->val = val;
	new->eql = eql;
	new->next = NULL;
	if (sh->e_size > 0)
	{
		new->next = sh->env;
		sh->env = new;
	}
	sh->e_size++;
	return (SUCCESS);
}

static int	check_exp_var(char *str)
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

int	export(t_mini *sh, char *str)
{
	t_axu	aux;

	if (check_exp_var(str))
		return (msg_error(E_EXP, 1, str));
	aux.len_r = ft_strchrpos(str, '=');
	aux.len_k = (ft_strlen(str) - aux.len_r);
	aux.var = ft_substr(str, 0, aux.len_r);
	aux.val = ft_substr(str, aux.len_r + 1, aux.len_k);
	if (!aux.var || !aux.val)
		exit (msg_error(E_MEM, 1, NULL));
	if (ft_strchrpos(str, '=') && !str[aux.len_r + 1])
	{
		aux.eql = TRUE;
		free(aux.val);
		aux.val = "";
		ft_printf(C"estoy qui\n"E);
	}
	if (ft_strchrpos(str, '=') == ERROR)
	{
		aux.eql = FALSE;
		free(aux.val);
		aux.val = NULL;
	}
	if (replace_val(sh->env, aux.var, aux.val))
		;
	else
		add_var_env(sh, aux.var, aux.val, aux.eql);
	return (SUCCESS);
}

void	print_export(t_env *env)
{
	t_env *tmp;

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