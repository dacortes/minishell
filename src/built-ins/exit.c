/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacortes <dacortes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 14:05:18 by dacortes          #+#    #+#             */
/*   Updated: 2023/10/26 09:54:11 by dacortes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/shell_mini.h"

static int free_err(char *err)
{
	if (err)
	{
		free(err);
		err = NULL;
	}
	return (SUCCESS);
}

static void	loop_ext(t_mini *sh, t_line **ln, t_get **g)
{
	char	**argv;
	char	*err;
	int		i;
	int		cl;

	i = 0;
	argv = (*g)->arg;
	err = ft_strdup_exit(argv[1]);
	if (argv[1][0] && (argv[1][0] == '-' || argv[1][0] == '+') \
		&& (!argv[1][1]))
		exit (msg_error(EX, 255, err) + free_err(err));
	else if (argv[1][0] && (argv[1][0] == '-' || argv[1][0] == '+') \
		&& argv[1][1] && !ft_isdigit(argv[1][1]))
		exit (msg_error(EX, 255, err) + free_err(err));
	while (argv[1][i])
	{
		if (!ft_isdigit(argv[1][i]) && argv[1][i] != '-' \
			&& argv[1][i] != '+')
		{
			cl = clear_ln(ln) + clear_get(g) + clear(sh);
			exit (msg_error(EX, 255, err) + free_err(err));
		}
		i++;
	}
	free_err(err);
}

int	ft_exit(t_mini *sh, t_line **ln, t_get **g, int n_cmd)
{
	ft_printf("exit\n");
	if (n_cmd == 1)
	{
		clear_ln(ln);
		clear_get(g);
		clear(sh);
		clear_history();
		exit (SUCCESS);
	}
	else if (n_cmd >= 2)
	{
		loop_ext(sh, ln, g);
		if (n_cmd > 2)
			return (msg_error(E_ARG, 1, "exit"));
		exit (ft_atoi((*g)->arg[1]));
	}
	return (SUCCESS);
}
