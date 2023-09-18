/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacortes <dacortes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 10:56:02 by dacortes          #+#    #+#             */
/*   Updated: 2023/09/18 16:23:31 by dacortes         ###   ########.fr       */
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
	while (i < 3)
		new->type[i++] = type[j++];
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
