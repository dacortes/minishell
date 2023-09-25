/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacortes <dacortes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 11:55:21 by dacortes          #+#    #+#             */
/*   Updated: 2023/09/25 10:11:03 by dacortes         ###   ########.fr       */
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
		while (rm->argv[i])
			free(rm->argv[i++]);
		if (rm->argv)
			free(rm->argv);
		tmp = rm;
		rm = rm->next;
		free(tmp);
	}
	*ln = NULL;
	return (SUCCESS);
}

char	**convert_to_argv(t_line *ln)
{
	int		argc;
	char	**argv;
	t_token	*temp_tk;
	int		i;

	i = 0;
	argc = ln->argc;
	argv = ft_calloc(argc + 1, sizeof(char *));
	if (!argv)
		exit (msg_error(E_MEM, 1, NULL));
	temp_tk = ln->tk;
	while (argc--)
	{
		argv[argc] = ft_strdup_exit(temp_tk->arg);
		temp_tk = temp_tk->next;
	}
	return (argv);
}
