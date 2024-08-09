/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 12:46:27 by codespace         #+#    #+#             */
/*   Updated: 2024/08/09 10:25:43 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

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

static void	printf_arg(char **argv, int i)
{
	while (argv[i])
	{
		ft_printf("%s", argv[i]);
		if (argv[i + 1])
			ft_printf(" ");
		i++;
	}
}

int	loop_echo(char **argv, int *pos1, int *pos2)
{
	int	flag;

	while (argv[*pos1])
	{
		flag = check_echo(argv[*pos1]);
		while (flag)
		{
			*pos1++;
			*pos2++;
			flag = check_echo(argv[*pos1]);
		}
		if (!flag)
			break ;
	}
	flag = check_echo(argv[*pos1 - 1]);
	*pos2 = *pos1;
	printf_arg(argv, *pos2);
	if (flag = FALSE)
		ft_printf("\n");
	return (EXIT_SUCCESS);
}

int	_echo(char **command, int num_arg)
{
	int	pos1;
	int	pos2;

	pos1 = 1;
	pos2 = 2;
	if (num_arg == 1)
		ft_printf("\n");
	if (argc >= 2)
		loop_echo(command, &pos1, &pos2);
	return (EXIT_SUCCESS);
}
