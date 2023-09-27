/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacortes <dacortes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 17:02:21 by dacortes          #+#    #+#             */
/*   Updated: 2023/09/27 17:03:24 by dacortes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/shell_mini.h"

static t_get	*get_last(t_get *g)
{
	if (!g)
		return (NULL);
	while (g->next)
		g = g->next;
	return (g);
}

static void	add_back(t_get **g, t_get *new)
{
	t_get	*tmp;

	if (g)
	{
		if (!*g)
			*g = new;
		else
		{
			tmp = get_last(*(g));
			tmp->next = new;
		}
	}
}

int	add_get(t_get **g, char **arg, int len)
{
	t_get	*new;
	char	**av;
	int		i;
	int		j;

	i = 0;
	j = 0;
	new = ft_calloc(sizeof(t_get), 1);
	if (!new)
		exit (msg_error(E_MEM, 1, NULL));
	av = ft_calloc(sizeof(char *), len + 1);
	if (!av)
		exit (msg_error(E_MEM, 1, NULL));
	while (arg[i])
		av[j++] = arg[i++];
	add_back(g, new);
	return (SUCCESS);
}
