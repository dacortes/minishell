/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacortes <dacortes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 14:52:48 by dacortes          #+#    #+#             */
/*   Updated: 2023/09/07 18:32:29 by dacortes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/shell_mini.h"

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

int	clear_ln(t_line **ln)
{
	t_line	*rm = *ln;
	t_line	*tmp;	

	while (rm)
	{
		clear_tk(&(*ln)->tk);
		if (rm->line)
			free(rm->line);
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
	argv = malloc((argc + 1) * sizeof(char *));
	if (!argv)
		exit (msg_error(E_MEM, 1, NULL));
	temp_tk = ln->tk;
	ft_printf(C"ln=%p\n"E, ln);
	ft_printf(O"tmp_tk%p\n"E, temp_tk);
	ft_printf(R"argv=%p"E, argv[0]);
	while (argc--)
	{
		ft_printf("%s\n", temp_tk->arg);
		argv[argc] = ft_strdup(temp_tk->arg);
		if (!argv[argc])
			exit (msg_error(E_MEM, 1, NULL));
		temp_tk = temp_tk->next;
	}
	argv[argc] = NULL;
	ft_printf(C"ln=%p\n"E, ln);
	ft_printf(O"tmp_tk%p\n"E, temp_tk);
	ft_printf(R"argv=%p"E, argv);
	// print_argv(argv);
	return (argv);
}

int	copy_quotes(char *inp, t_aux *a, int *count, t_token **tk, int type)
{
	if (type == QUO || type == DQU)
	{
		a->i += (inp[a->i] == QUO) + (inp[a->i] == DQU);
		a->j = ft_strchrpos(&inp[a->i], type);
		if (a->j == ERROR)
			return (ERROR);
		a->tmp = ft_substr(inp, a->i, a->j);
		if (!a->tmp)
			exit (msg_error(E_MEM, 1, NULL));
		a->i += a->j + 1;
		add_token(tk, a->tmp, 0, count);
		free(a->tmp);
	}
	else
	{
		a->j = a->i;
		while (inp[a->j] && inp[a->j] != ' ' && inp[a->j] != '|' \
			&& inp[a->j] != QUO && inp[a->j] != DQU)
			a->j++;
		a->tmp = ft_substr(inp, a->i, a->j - a->i);
		a->i = a->j;
		add_token(tk, a->tmp, 0, count);
		free(a->tmp);
	}
	return (SUCCESS);
}

void	test(t_line *ln)
{
	t_line *tmp;
	t_token	*tk_tmp;

	tmp = ln;
	tk_tmp = ln->tk;
	ft_printf(O"nodes the line\n"E);
	while (tmp)
	{
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
int	continue_ln(t_line **ln, t_token **tk, t_aux *a, char *inp)
{
	int 	i;
	char	*tmp;

	i = 0;
	while (inp[a->i] && inp[a->i] != '|')
	{
		while (inp[a->i] && ((inp[a->i] >= 9 \
			&& inp[a->i] <= 13) || inp[a->i] == 32))
			a->i++;
		a->in_qu = ((inp[a->i] == DQU) * DQU) + ((inp[a->i] == QUO) * QUO);
		if (a->in_qu == DQU && copy_quotes(inp, a, &i, tk, DQU) == ERROR)
			return ((ft_printf(R"Error double quotes\n"E) * 0) + ERROR);
		else if (a->in_qu == QUO && copy_quotes(inp, a, &i, tk, QUO) == ERROR)
			return ((ft_printf(R"Error quotes\n"E) * 0) + ERROR);
		else if (inp[a->i] && inp[a->i] != '|' && !a->in_qu)
		{
			if (copy_quotes(inp, a, &i, tk, ' ') == ERROR)
				return ((ft_printf(R"Error space\n"E) * 0) + ERROR);
		}
	}
	while (inp[a->k] && ((inp[a->k] >= 9 && inp[a->k] <= 13) \
		|| inp[a->k] == 32))
		a->k++;
	tmp = ft_substr(inp, a->k, a->i - a->k);
	a->k = a->i + 1;
	add_line(ln, *tk, tmp);
	(*ln)->argc = i;
	free (tmp);
	ft_printf(O"%d\n"E, (*ln)->argc);
	return (SUCCESS);
}

int	test_line(char *inp, t_line **ln)
{
	t_aux	a;
	t_token	*tk;

	tk  =  NULL;
	ft_bzero(&a, sizeof(t_aux));
	while (inp[a.i])
	{
		if (continue_ln(ln, &tk, &a, inp) == ERROR)
			break ;
		if (inp[a.i])
			a.i++;
	}
	return (SUCCESS);
}
