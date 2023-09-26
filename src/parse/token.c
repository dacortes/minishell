/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacortes <dacortes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 10:56:02 by dacortes          #+#    #+#             */
/*   Updated: 2023/09/26 18:42:05 by dacortes         ###   ########.fr       */
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
	ft_printf(F"*********LINE\n"E);
	while (tmp)
	{
		ft_printf(O"*Analize*\n"E);
		tmp->type[0] == FALSE && ft_printf(F"[0]QUO Type:"E" not quotes\n");
		tmp->type[0] == QUO && ft_printf(F"[0]QUO Type:"E" QUO quote\n");
		tmp->type[0] == DQU && ft_printf(F"[0]QUO Type:"E" DQU db_cuote\n");
		tmp->type[1] == T_EXP && ft_printf(F"[1]Tk  Type:"E" T_EXP expand\n");
		tmp->type[1] == T_TXT && ft_printf(F"[1]Tk  Type:"E" T_TXT text\n");
		tmp->type[2] == FALSE && ft_printf(F"[2]SP  Type:"E" not space\n");
		tmp->type[2] && ft_printf(F"[2]SP  Type:"E" num:%d\n", tmp->type[2]);
		tmp->type[3] == T_CMD && ft_printf(F"[3]TP  Type:"E" T_CMD comman\n");
		tmp->type[3] == T_TXT && ft_printf(F"[3]TP  Type:"E" T_TXT text\n");
		tmp->type[3] == T_SIR && ft_printf(F"[3]TP  Type:"E" T_SIR \'<\'\n");
		tmp->type[3] == T_SOR && ft_printf(F"[3]TP  Type:"E" T_SOR \'>\'\n");
		tmp->type[3] == T_RDHD && ft_printf(F"[3]TP  Type:"E" T_RDHD \'<<\'\n");
		tmp->type[3] == T_RDAP && ft_printf(F"[3]TP  Type:"E" T_RDAP \'>>\'\n");
		ft_printf(O"Token:"E" *%s*\n", tmp->arg);
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
