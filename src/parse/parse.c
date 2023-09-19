/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacortes <dacortes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 17:19:26 by dacortes          #+#    #+#             */
/*   Updated: 2023/09/19 18:56:28 by dacortes         ###   ########.fr       */
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

int	splt_tk_start(t_token **tk, char *cut, int pos, int sum)
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
	tmp = ft_strdup_exit(act->arg);
	new->arg = ft_strrep(tmp, pos, ft_strlen(tmp), cut);
	new->next = act->next;
	if (act->arg)
		free(act->arg);
	act->arg = ft_strdup_exit(&act->arg[pos + sum + 1]);
	act->next = new;
	*tk = act;
	free(tmp);
	return (SUCCESS);
}

int	splt_tk_end(t_token **tk, char *cut)
{
	(void)tk;
	(void)cut;
	// (void)pos;
	// (void)sum;
	// t_token *act;
	// t_token *new;
	char	*tmp;
	char	*err;
	int		num;

	tmp = ft_strdup_exit((*tk)->arg);
	num = ft_strchrpos(tmp, cut[0]);
	// if (tmp[num])
	// 	ft_printf("%s\n", tmp[num]);
	while (tmp[num] && tmp[num] == cut[0])
		num++;
	if (num > 2)
	{
		cut[0] == '>' && (err = "`>\'");
		cut[0] == '<' && (err = "`<\'");
		free(tmp);
		return (msg_error(E_SNT, E_SNT, err));
	}
	ft_printf(T"%s\n"E, &tmp[ft_strchrpos(tmp, cut[0])]);
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
					if (tmp->arg[0] == '>' && tmp->arg[1] != '>')
						splt_tk_start(&tmp, ">", 0, 0);
					else if (tmp->arg[0] == '<' && tmp->arg[1] != '<')
						splt_tk_start(&tmp, "<", 0, 0);
					else if (tmp->arg[0] == '>' && tmp->arg[1] == '>')
						splt_tk_start(&tmp, ">>", 0, 1);
					else if (tmp->arg[0] == '<' && tmp->arg[1] == '<')
						splt_tk_start(&tmp, "<<", 0, 1);
					else if (tmp->arg[0] != '>' && ft_strchr(tmp->arg, '>'))
						splt_tk_end(&tmp, ">"/*, 0, 0*/);
					// 	splt_tk_start(&tmp, ">", 0, 0);
					// else if (tmp->arg[0] != '<' && tmp->arg[1] != '<')
					// 	splt_tk_start(&tmp, "<", 0, 0);
					// else if (tmp->arg[0] != '>' && tmp->arg[1] == '>')
					// 	splt_tk_start(&tmp, ">>", 0, 1);
					// else if (tmp->arg[0] != '<' && tmp->arg[1] == '<')
					// 	splt_tk_start(&tmp, "<<", 0, 1);
				}
			}
			// ft_printf(C"%s\n"E, tmp->arg);
			(tmp->next == NULL) && (tmp->type[3] = T_CMD);
			// ft_printf(C"%d\n"E, tmp->type[3]);
		}
		else
		{
			num = 0;
			while (tmp->arg[num] && (tmp->arg[num] == '<'))
				num++;
			while (tmp->arg[num] && (tmp->arg[num] == '>'))
				num++;
			tmp->type[3] = T_TXT;
			identify(&tmp);
			// ft_printf(R"%d\n"E, tmp->type[0]);
			if (tmp->type[0] == FALSE && tmp->type[3] == T_TXT)
			{
				if (num > 2)
					return (msg_error(E_SNT, E_SNT, "`newline\'"));
				if (ft_strlen(tmp->arg) > 1)
				{
					if (tmp->arg[0] == '>' && tmp->arg[1] != '>')
						splt_tk_start(&tmp, ">", 0, 0);
					else if (tmp->arg[0] == '<' && tmp->arg[1] != '<')
						splt_tk_start(&tmp, "<", 0, 0);
					else if (tmp->arg[0] == '>' && tmp->arg[1] == '>')
						splt_tk_start(&tmp, ">>", 0, 1);
					else if (tmp->arg[0] == '<' && tmp->arg[1] == '<')
						splt_tk_start(&tmp, "<<", 0, 1);
				}
			}
			// ft_printf(C"%s\n"E, tmp->arg);
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
