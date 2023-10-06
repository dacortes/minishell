/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacortes <dacortes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 11:55:21 by dacortes          #+#    #+#             */
/*   Updated: 2023/10/06 16:50:11 by dacortes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/shell_mini.h"

int	clear_ln(t_line **ln)
{
	t_line	*rm;
	t_line	*tmp;
	int		i;

	rm = *ln;
	while (rm)
	{
		i = 0;
		clear_tk(&rm->tk);
		if (rm->line)
			free(rm->line);
		tmp = rm;
		rm = rm->next;
		free(tmp);
	}
	*ln = NULL;
	return (SUCCESS);
}

static t_line	*line_last(t_line *ln)
{
	if (!ln)
		return (NULL);
	while (ln->next)
		ln = ln->next;
	return (ln);
}

void	add_back(t_line **ln, t_line *new)
{
	t_line	*tmp;

	if (ln)
	{
		if (!*ln)
			*ln = new;
		else
		{
			tmp = line_last(*(ln));
			tmp->next = new;
		}
	}
}

int	add_line(t_line **ln, t_token *tk, char	*line)
{
	t_line	*new;

	new = ft_calloc(sizeof(t_line), 1);
	if (!new)
		exit (msg_error(E_MEM, 1, NULL));
	new->tk = tk;
	new->line = ft_strdup(line);
	if (!line)
		exit (msg_error(E_MEM, 1, NULL));
	new->next = NULL;
	add_back(ln, new);
	return (SUCCESS);
}
