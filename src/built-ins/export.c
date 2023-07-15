/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacortes <dacortes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 14:06:54 by dacortes          #+#    #+#             */
/*   Updated: 2023/07/15 16:38:30 by dacortes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/shell_mini.h"

/* agregar */
int	add_var_env(t_mini *sh, char *var)
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
	if (ft_strchrpos(var, '=') == ERROR)
	{
		free(new->val);
		new->val = NULL;
	}
	new->next = NULL;
	if (sh->e_size > 0)
	{
		new->next = sh->env;
		sh->env = new;
	}
	sh->e_size++;
	return (SUCCESS);
}
