/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacortes <dacortes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 11:55:21 by dacortes          #+#    #+#             */
/*   Updated: 2023/09/19 12:18:04 by dacortes         ###   ########.fr       */
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

void	show_line(t_line *ln)
{
	t_line	*tmp;
	t_token	*tk_tmp;

	tmp = ln;
	ft_printf(O"nodes the line\n"E);
	while (tmp)
	{
		(O"nodes the token\n"E);
		tk_tmp = ln->tk;
		ft_printf(Y"%p\n"E, tmp);
		while (tk_tmp)
		{
			ft_printf(F"%s\n"E, tk_tmp->arg);
			tk_tmp = tk_tmp->next;
		}
		if (!tmp->next)
			ft_printf(R"%p\n"E, tmp);
		tmp = tmp->next;
	}
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
	if (!(*ln))
		*ln = new;
	else
	{
		new->next = *ln;
		*ln = new;
	}
	return (SUCCESS);
}

int	type_expand(char *inp, t_aux *a, t_token **tk, int type)
{
	int	array[3];

	array[0] = type;
	array[1] = ((inp[a->i] == QUO) * T_TXT) + ((inp[a->i] == DQU) * T_EXP);
	array[2] = 0;
	a->i += (inp[a->i] == QUO) + (inp[a->i] == DQU);
	a->j = ft_strchrpos(&inp[a->i], type);
	if (a->j == ERROR)
		return (ERROR);
	a->tmp = ft_substr(inp, a->i, a->j);
	if (!a->tmp)
		exit (msg_error(E_MEM, 1, NULL));
	a->i += a->j + 1;
	add_token(tk, a->tmp, array, &a->c);
	free(a->tmp);
	return (SUCCESS);
}
