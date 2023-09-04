/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcespede <fcespede@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 10:34:21 by dacortes          #+#    #+#             */
/*   Updated: 2023/09/03 18:54:45 by fcespede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/shell_mini.h"

int	clear_ln(t_line **ln)
{
	t_line	*rm;

	while (*ln)
	{
		rm = (*ln)->next;
		if ((*ln)->line)
		{
			// ft_printf(B"free %s\n"E, (*ln)->line);
			free((*ln)->line);
			(*ln)->line = NULL;
		}
		ft_printf("hola\n");
		if ((*ln)->argv)
		{
			ft_printf(R"free argv\n"E);
			while (*(*ln)->argv)
			{
				ft_printf("free %s\n", *(*ln)->argv);
				if (*(*ln)->argv)
					free(*(*ln)->argv++);
			}
		}
		if ((*ln)->tk)
		{
			ft_printf(Y"free tk\n"E);
			while ((*ln)->tk)
			{
				ft_printf("free %s\n", (*ln)->tk->arg);
				if ((*ln)->tk->arg)
					free((*ln)->tk->arg);
				(*ln)->tk = (*ln)->tk->next;
			}
			free((*ln)->tk);
		}
		ft_printf(G"free ln\n"E);
		(*ln) = rm;
	}
	return (SUCCESS);
}

// void	show_tk(t_token *tk)
// {
// 	t_token	*tmp;

// 	tmp = tk;
// 	while (tmp)
// 	{
// 		ft_printf(G"%s\n"E, tmp->arg);
// 		tmp = tmp->next;
// 	}
// }

// void	show_ln(t_line *ln)
// {
// 	t_line	*tmp;

// 	tmp = ln;
// 	int i = 0;
// 	while (tmp)
// 	{
// 		ft_printf(O"argc=%i |"E, tmp->argc);
// 		ft_printf(R" %i-%s\n"E, i, tmp->line);
// 		show_tk(tmp->tk);
// 		tmp = tmp->next;
// 		i++;
// 	}
// }

// void print_argv(char **argv) {
//     if (argv == NULL) {
//         printf("El argv es NULL.\n");
//         return;
//     }

//     int i = 0;
//     printf("Contenido de argv:\n");
//     while (argv[i] != NULL) {
//         printf("argv[%d] = %s\n", i, argv[i]);
//         i++;
//     }
// }

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
	while (argc--)
	{
		ft_printf("%s\n", temp_tk->arg);
		argv[argc] = ft_strdup(temp_tk->arg);
		temp_tk = temp_tk->next;
	}
	argv[argc] = NULL;
	// print_argv(argv);
	return (argv);
}

int	add_line(t_line **ln)
{
	t_line	*new;

	new = ft_calloc(sizeof(t_line), 1);
	if (!new)
		exit (msg_error(E_MEM, 1, NULL));
	new->next = *ln;
	*ln = new;
	(*ln)->argc++;
	return (SUCCESS);
}

int	copy_quotes(char *inp, t_aux *a, t_line **ln, int type)
{
	if (type == QUO || type == DQU)
	{
		a->i += (inp[a->i] == QUO) + (inp[a->i] == DQU);
		a->j = ft_strchrpos(&inp[a->i], type);
		if (a->j == ERROR)
			return (ERROR);
		a->tmp = ft_substr(inp, a->i, a->j);
		a->i += a->j + 1;
		add_token(ln, &(*ln)->tk, a->tmp, 0);
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
		add_token(ln, &(*ln)->tk, a->tmp, 0);
		free(a->tmp);
	}
	return (SUCCESS);
}

int	continue_ln(t_line **ln, char *inp, t_aux *a)
{
	(*ln)->tk = NULL;
	(*ln)->argc = 0;
	while (inp[a->i] && inp[a->i] != '|')
	{
		while (inp[a->i] && ((inp[a->i] >= 9 \
			&& inp[a->i] <= 13) || inp[a->i] == 32))
			a->i++;
		a->in_qu = ((inp[a->i] == DQU) * DQU) + ((inp[a->i] == QUO) * QUO);
		if (a->in_qu == DQU && copy_quotes(inp, a, ln, DQU) == ERROR)
			return ((ft_printf(R"Error double quotes\n"E) * 0) + ERROR);
		else if (a->in_qu == QUO && copy_quotes(inp, a, ln, QUO) == ERROR)
			return ((ft_printf(R"Error quotes\n"E) * 0) + ERROR);
		else if (inp[a->i] && inp[a->i] != '|' && !a->in_qu)
		{
			if (copy_quotes(inp, a, ln, ' ') == ERROR)
				return ((ft_printf(R"Error space\n"E) * 0) + ERROR);
		}
	}
	while (inp[a->k] && ((inp[a->k] >= 9 && inp[a->k] <= 13) \
		|| inp[a->k] == 32))
		a->k++;
	(*ln)->line = ft_substr(inp, a->k, a->i - a->k);
	a->k = a->i + 1;
	(*ln)->argv = convert_to_argv(*ln);
	add_line(ln);
	return (SUCCESS);
}

int	init_ln(char *inp, t_line **ln)
{
	t_aux	a;
	t_line	*tmp;

	a.i = 0;
	a.k = 0;
	tmp = *ln;
	if (!inp)
	{
		(*ln)->line = ft_strdup("");
		(*ln)->argv = ft_calloc(sizeof(char *), 1);
		(*ln)->argv[0] = ft_strdup("");
		return (SUCCESS);
	}
	while (inp[a.i])
	{
		if (continue_ln(&tmp, inp, &a) == ERROR)
			break ;
		if (inp[a.i])
			a.i++;
	}
	// show_ln(tmp);
	return (SUCCESS);
}
