/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacortes <dacortes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 14:26:33 by dacortes          #+#    #+#             */
/*   Updated: 2023/09/18 16:20:58 by dacortes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/shell_mini.h"

/* falta decirle a los tokes si tienen espacio antes */
static int	check_echo(char *argv)
{
	int	i;

	i = 1;
	if (!argv)
		return (FALSE);
	if (argv[0] && argv[1] && argv[0] == '-')
	{
		while (argv[i] && argv[i] == 'n')
			i++;
		if (argv[i] == '\0')
			return (TRUE);
	}
	return (FALSE);
}

int	ft_echo(char **argv, int argc)
{
	t_aux	a;

	(1 && (a.i = 1)) && (a.j = 1);
	a.k = 0;
	argc == 1 && ft_printf("\n");
	if (argc >= 2)
	{
		while (argv[a.j])
		{
			a.key = check_echo(argv[a.j]);
			while (a.key)
			{
				(a.j++) && (a.k++);
				a.key = check_echo(argv[a.j]);
			}
			if (!a.key)
				break ;
		}
		a.key = check_echo(argv[a.j - 1]);
		a.i = a.j;
		while (argv[a.i])
			ft_printf("%s", argv[a.i++]);
		a.key == FALSE && ft_printf("\n");
	}
	return (SUCCESS);
}
