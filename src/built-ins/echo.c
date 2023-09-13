/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacortes <dacortes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 14:26:33 by dacortes          #+#    #+#             */
/*   Updated: 2023/09/13 15:13:30 by dacortes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/shell_mini.h"

/* falta decirle a los tokes si tienen espacio antes */
static int check_echo(char *argv)
{
	int i;

	i = 1;
	if (argv[0] == '-')
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
	int i;
	int	check;
	(void)argv;

	i = 1;
	ft_printf(G"------echo------\n"E);
	argc == 1 && ft_printf("\n");
	if (argc >= 2)
	{
		check = check_echo(argv[1]);
		if (check)
			i++;
		while (argv[i])
			ft_printf("%s", argv[i++]);
		check == FALSE && ft_printf("\n");
	}
	return (SUCCESS);
}