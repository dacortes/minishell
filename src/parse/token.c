/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacortes <dacortes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 10:56:02 by dacortes          #+#    #+#             */
/*   Updated: 2023/09/26 14:58:19 by dacortes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/shell_mini.h"

/*
	Spaces are counted from the text to the right.
*/
void	show_tokens(t_line *ln)
{
	t_token	*tmp;

	tmp = ln->tk;
	while (tmp)
	{
		tmp->type[0] == FALSE && ft_printf(F"QUO   Type:"E" not quotes\n");
		tmp->type[0] == QUO && ft_printf(F"QUO   Type:"E" quote\n");
		tmp->type[0] == DQU && ft_printf(F"QUO   Type:"E" double cuote\n");
		tmp->type[1] == T_CMD && ft_printf(F"TOKEN Type:"E" command\n");
		tmp->type[1] == T_EXP && ft_printf(F"TOKEN Type:"E" expand\n");
		tmp->type[1] == DQU && ft_printf(F"TOKEN Type:"E" text\n");
		tmp->type[2] == FALSE && ft_printf(F"SPACE Type:"E" not space\n");
		tmp->type[2] && ft_printf(F"SPACE Type:"E" %d\n", tmp->type[2]);
		tmp->type[3] == T_CMD && ft_printf(F"TYPE  Type:"E" comman\n");
		tmp->type[3] == T_TXT && ft_printf(F"TYPE  Type:"E" text\n");
		tmp->type[3] == T_SIR && ft_printf(F"TYPE  Type:"E" \'<\'\n");
		tmp->type[3] == T_SOR && ft_printf(F"TYPE  Type:"E" \'>\'\n");
		tmp->type[3] == T_RDHD && ft_printf(F"TYPE  Type:"E" \'<<\'\n");
		tmp->type[3] == T_RDAP && ft_printf(F"TYPE  Type:"E" \'>>\'\n");
		ft_printf(O"*%s*\n"E, tmp->arg);
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

t_token	*token_last(t_token *tk)
{
	if (!tk)
		return (NULL);
	while (tk->next)
		tk = tk->next;
	return (tk);
}

void	add_back(t_token **tk, t_token *new)
{
	t_token	*tmp;

	if (tk)
	{
		if (!*tk)
			*tk = new;
		else
		{
			tmp = token_last(*(tk));
			tmp->next = new;
		}
	}
}

int	add_token(t_token **tk, char *arg, int *type, int *count)
{
	t_token	*new;
	int		i;
	int		j;

	i = 0;
	j = 0;
	new = ft_calloc(sizeof(t_token), 1);
	if (!new)
		exit (msg_error(E_MEM, 1, NULL));
	new->arg = ft_strdup(arg);
	if (!new->arg)
		exit (msg_error(E_MEM, 1, NULL));
	while (i < 4)
		new->type[i++] = type[j++];
	add_back(tk, new);
	(*count)++;
	return (SUCCESS);
}
