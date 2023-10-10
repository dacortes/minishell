/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redic.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacortes <dacortes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 14:57:38 by dacortes          #+#    #+#             */
/*   Updated: 2023/10/10 15:35:49 by dacortes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../inc/shell_mini.h"

static	t_rdc	*rdc_last(t_rdc *rdc)
{
	if (!rdc)
		return (NULL);
	while (rdc->next)
		rdc = rdc->next;
	return (rdc);
}

void	rdc_add_back(t_rdc **rdc, t_rdc *new)
{
	t_rdc	*tmp;

	if (rdc)
	{
		if (!*rdc)
		{
			*rdc = new;
			new->prev = NULL;
		}
		else
		{
			tmp = rdc_last(*rdc);
			tmp->next = new;
			new->prev = tmp;
		}
	}
}

int	add_rdc(t_rdc **rdc, int rd, char *fl)
{
	t_rdc	*new;

	new = ft_calloc(sizeof(t_rdc), 1);
	if (!new)
		exit (msg_error(E_MEM, 1, NULL));
	new->rd = rd;
	new->fl = ft_strdup_exit(fl);
	new->next = NULL;
	rdc_add_back(rdc, new);
	return (SUCCESS);
}
