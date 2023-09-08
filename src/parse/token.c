/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacortes <dacortes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 10:56:02 by dacortes          #+#    #+#             */
/*   Updated: 2023/09/08 18:57:42 by dacortes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/shell_mini.h"

void	show_tokens(t_line *ln)
{
	t_token	*tmp;

	tmp = ln->tk;
	while (tmp)
	{
		ft_printf(F"%s\n"E, tmp->arg);
		tmp = tmp->next;
	}
}

int	clear_tk(t_token **tk)
{
	t_token	*rm;
	t_token	*tmp;

	rm = *tk;
	while (rm)
	{
		if (rm->arg)
			free(rm->arg);
		tmp = rm;
		rm = rm->next;
		free(tmp);
	}
	*tk = NULL;
	return (SUCCESS);
}

// int	expand_tk(t_token **tk, t_env *env)
// {
// 	t_token *tmp;
// 	char	*ex;
// 	int		i;

// 	tmp = *tk;
// 	while (tmp)
// 	{
// 		if (tmp->type == T_EXP)
// 		{
// 			i = ft_strchrpos(tmp->arg, '$');
// 			if (i != ERROR)
// 			{
// 				ft_printf(T"%d\n"E, i);
// 				if (search_env(env, &tmp->arg[i + 1], VAL))
// 				{
// 					ex = ft_strdup_exit(search_env(env, &tmp->arg[i + 1], VAL));
// 					i -= (tmp->arg[i] == '$');
// 					while (i >= 0)
// 					{
// 						char *add = ft_addstart_char(ex, tmp->arg[i--]);
// 						free(ex);
// 						ex = ft_strdup_exit(add);
// 						free(add);
// 					}
// 				}
// 				else
// 					ex = ft_strdup_exit("");
// 				if (tmp->arg)
// 					free(tmp->arg);
// 				tmp->arg = ft_strdup_exit(ex);
// 				free(ex);
// 			}
// 		}
// 		tmp = tmp->next;
// 	}
// 	return (SUCCESS);
// }

void	expand_exp(t_env *env, t_aux *a, t_token *tmp)
{
	a->e = ft_strdup_exit(search_env(env, &tmp->arg[a->i + 1], VAL));
	a->i -= (tmp->arg[a->i] == '$');
	while (a->i >= 0)
	{
		a->tmp = ft_addstart_char(a->e, tmp->arg[a->i--]);
		free(a->e);
		a->e = ft_strdup_exit(a->tmp);
		free(a->tmp);
	}
}

int	expand_tk(t_token **tk, t_env *env)
{
	t_token *tmp;
	t_aux	a;

	tmp = *tk;
	while (tmp)
	{
		if (tmp->type == T_EXP)
		{
			a.i = ft_strchrpos(tmp->arg, '$');
			if (a.i != ERROR)
			{
				if (search_env(env, &tmp->arg[a.i + 1], VAL))
					expand_exp(env, &a, tmp);
				else
					a.e = ft_strdup_exit("");
				if (tmp->arg)
					free(tmp->arg);
				tmp->arg = ft_strdup_exit(a.e);
				free(a.e);
			}
		}
		tmp = tmp->next;
	}
	return (SUCCESS);
}

int	add_token(t_token **tk, char *arg, int type, int *count)
{
	t_token	*new;

	new = ft_calloc(sizeof(t_token), 1);
	if (!new)
		exit (msg_error(E_MEM, 1, NULL));
	new->arg = ft_strdup(arg);
	if (!new->arg)
		exit (msg_error(E_MEM, 1, NULL));
	new->type = type;
	new->next = NULL;
	if (!(*tk))
		*tk = new;
	else
	{
		new->next = *tk;
		(*tk) = new;
	}
	(*count)++;
	return (SUCCESS);
}
