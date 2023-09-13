/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacortes <dacortes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 14:05:18 by dacortes          #+#    #+#             */
/*   Updated: 2023/09/13 14:31:29 by dacortes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/shell_mini.h"

static void	loop_ext(t_line **ln, t_mini *sh, char **argv)
{
	int	i;

	i = 0;
	while (argv[1][i])
	{
		if (!ft_isdigit(argv[1][i]) && argv[1][i] != '-' \
			&& argv[1][i] != '+')
		{
			clear_ln(ln);
			clear(sh);
			exit (msg_error(EX, 255, argv[1]));
		}
		i++;
	}
}

int	ft_exit(t_line **ln, t_mini *sh, char **argv, int argc)
{
	if (argc == 1)
	{
		clear_ln(ln);
		clear(sh);
		clear_history();
		exit (SUCCESS);
	}
	else if (argc >= 2)
	{
		loop_ext(ln, sh, argv);
		if (argc > 2)
			return (msg_error(E_ARG, 1, "exit"));
		exit (ft_atoi(argv[1]));
	}
	return (SUCCESS);
}
