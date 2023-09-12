/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacortes <dacortes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 10:56:02 by dacortes          #+#    #+#             */
/*   Updated: 2023/09/12 16:31:05 by dacortes         ###   ########.fr       */
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

int	expand_tk(t_token **tk, t_env *env)
{
	t_token *tmp;
	t_aux	a;
	char	*expanded_arg;

	tmp = *tk;
	while (tmp)
	{
		if (tmp->type == T_EXP)
		{
			a.e = ft_strdup(tmp->arg);
			char *dollar = a.e;
			while ((dollar = ft_strchr(dollar, '$')) != NULL)
			{
				int start = dollar - a.e;
				int end = start + 1;
				while (a.e[end] && (ft_isalnum(a.e[end]) || a.e[end] == '_'))
					end++;
				char *var_name = ft_strndup(a.e + start + 1, end - start - 1);
				char *var_value = search_env(env, var_name, VAL);
				free(var_name);
				if (var_value)
				{
					expanded_arg = ft_strrep(a.e, start, end, var_value);
					free(a.e);
					a.e = expanded_arg;
					dollar = a.e + start + ft_strlen(var_value);
				}
				else
				{
					expanded_arg = ft_strrep(a.e, start, end, "");
					free(a.e);
					a.e = expanded_arg;
					dollar = a.e + start;
				}
			}
			
			if (tmp->arg)
				free(tmp->arg);
			tmp->arg = ft_strdup_exit(a.e);
			free(a.e);
		}
		tmp = tmp->next;
	}
	return (SUCCESS);
}
