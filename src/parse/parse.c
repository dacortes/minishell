/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacortes <dacortes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 17:19:26 by dacortes          #+#    #+#             */
/*   Updated: 2023/09/19 17:56:38 by dacortes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/shell_mini.h"

int	identify(t_token **tk)
{
	(ft_strlen((*tk)->arg) == 1 && (*tk)->type[0] == FALSE
		&& (*tk)->arg[0] == '<' && ((*tk)->type[3] = T_SIR));
	(ft_strlen((*tk)->arg) == 1 && (*tk)->type[0] == FALSE
		&& (*tk)->arg[0] == '>' && ((*tk)->type[3] = T_SOR));
	(ft_strlen((*tk)->arg) == 2 && (*tk)->type[0] == FALSE
		&& ft_strncmp((*tk)->arg, "<<", 2) == 0 && ((*tk)->type[3] = T_RDHD));
	(ft_strlen((*tk)->arg) == 2 && (*tk)->type[0] == FALSE
		&& ft_strncmp((*tk)->arg, ">>", 2) == 0 && ((*tk)->type[3] = T_RDAP));
	return ((*tk)->type[3]);
}

int	div_token(t_token **tk, char *cut, int pos, int sum)
{
	t_token *act;
	t_token *new;
	char	*tmp;
	int		i;
	int		j;

	act = *tk;
	((i = 0) || (j = 0));
	new = ft_calloc(sizeof(t_token), 1);
	if (!new)
		exit (msg_error(E_MEM, 1, NULL));
	while (i < 3)
		new->type[i++] = act->type[j++];
	ft_printf(Y"%d\n"E, act->type[0]);
	tmp = ft_strdup_exit(act->arg);
	new->arg = ft_strdup_exit(&act->arg[pos + sum + 1]);
	new->next = act->next;
	if (act->arg)
		free(act->arg);
	act->arg = ft_strrep(tmp, pos, ft_strlen(tmp), cut);
	act->next = new;
	*tk = act;
	free(tmp);
	return (SUCCESS);
}

int	parse_tk(t_token **tk)
{
	t_token	*tmp;
	int		nd;
	int		num;

	tmp = *tk;
	nd = 0;
	while (tmp)
	{
		if (!nd)
		{
			num = 0;
			while (tmp->arg[num] && (tmp->arg[num] == '<'))
				num++;
			while (tmp->arg[num] && (tmp->arg[num] == '>'))
				num++;
			if (tmp->arg && ft_strlen(tmp->arg) == 1 && tmp->type[0] == FALSE
				&& (tmp->arg[0] == '<' || tmp->arg[0] == '>'))
				return (msg_error(E_SNT, E_SNT, "`newline\'"));
			else if (tmp->arg && ft_strlen(tmp->arg) == 2 && tmp->type[0] == FALSE
				&& ((ft_strncmp(tmp->arg, "<<", 2) == 0)
					|| (ft_strncmp(tmp->arg, ">>", 2) == 0)))
				return (msg_error(E_SNT, E_SNT, "`newline\'"));
			tmp->type[3] = T_TXT;
			if (tmp->type[0] == FALSE && tmp->type[3] == T_TXT)
			{
				if (num > 2)
					return (msg_error(E_SNT, E_SNT, "`newline\'"));
				if (ft_strlen(tmp->arg) > 1)
				{
					ft_printf("queso\n");
					if (tmp->arg[0] == '>' && tmp->arg[1] != '>')
						div_token(&tmp, ">", 0, 0);
					else if (tmp->arg[0] == '<' && tmp->arg[1] != '<')
						div_token(&tmp, "<", 0, 0);
					else if (tmp->arg[0] == '>' && tmp->arg[1] == '>')
						div_token(&tmp, ">>", 0, 1);
					else if (tmp->arg[0] == '<' && tmp->arg[1] == '<')
						div_token(&tmp, "<<", 0, 1);
				}
			}
			ft_printf(C"%s\n"E, tmp->arg);
			(tmp->next == NULL) && (tmp->type[3] = T_CMD);
			ft_printf(C"%d\n"E, tmp->type[3]);
		}
		else
		{
			tmp->type[3] = T_TXT;
			identify(&tmp);
			ft_printf(R"%d\n"E, tmp->type[0]);
			if (tmp->type[0] == FALSE && tmp->type[3] == T_TXT)
			{
				ft_printf(C"%s\n"E, tmp->arg);
				ft_printf("separar si es un redic correcto\n");
			}
			// ft_printf(C"%d\n"E, tmp->type[3]);
		}
		(tmp = tmp->next) && nd++;
	}
	return (SUCCESS);
}

int	ft_parse(t_line **ln)
{
	t_line	*tmp;

	tmp = *ln;
	while (tmp)
	{
		if (parse_tk(&tmp->tk) == E_SNT)
			return (E_SNT);
		tmp = tmp->next;
	}
	return (SUCCESS);
}
