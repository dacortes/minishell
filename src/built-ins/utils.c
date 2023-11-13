/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacortes <dacortes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 14:26:11 by dacortes          #+#    #+#             */
/*   Updated: 2023/11/13 15:53:27 by dacortes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/shell_mini.h"

char	*str_lower(char *str, char *low)
{
	int		i;

	i = 0;
	while (str[i])
	{
		low[i] = ft_tolower(str[i]);
		i++;
	}
	return (low);
}

int	magic_export(t_mini **sh, t_get **g, t_aux a, int n_cmd)
{
	if ((ft_strncmp((*g)->arg[0], "export", -1) == 0))
	{
		if (n_cmd >= 2)
		{
			a.i = 1;
			while ((*g)->arg[a.i])
				(_export(*sh, (*g)->arg[a.i++])) && (a.c = 1);
		}
		else
			show_export((*sh)->env);
	}
	return (a.c);
}
