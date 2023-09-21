/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacortes <dacortes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 17:19:26 by dacortes          #+#    #+#             */
/*   Updated: 2023/09/20 17:51:32 by dacortes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/shell_mini.h"

int	error_unexpected(int rep, char cut, char **fr)
{
	char	*err;

	(rep % 2 == 0) && cut == '>' && (err = "`>>\'");
	(rep % 2 == 0) && cut == '<' && (err = "`<<\'");
	(rep % 2 == 1) && cut == '>' && (err = "`>\'");
	(rep % 2 == 1) && cut == '<' && (err = "`<\'");
	if (fr && *fr)
		free(*fr);
	return (msg_error(E_SNT, E_SNT, err));
}

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
	t_token	*act;
	t_token	*new;
	char	*tmp;
	int		i;
	int		j;

	i = 0;
	j = 0;
	act = *tk;
	new = NULL;
	new = ft_calloc(sizeof(t_token), 1);
	if (!new)
		exit (msg_error(E_MEM, 1, NULL));
	ft_memcpy(new, act, sizeof(t_token));
	tmp = ft_strdup_exit(act->arg);
	new->arg = ft_strrep(tmp, pos, ft_strlen(tmp), cut);
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
	t_token	*act;
	t_token	*new;
	t_aux	a;

	ft_bzero(&a, sizeof(t_aux));
	a.tmp = ft_strdup_exit((*tk)->arg);
	a.c = ft_strchrpos(a.tmp, cut[0]);
	while (a.tmp[a.c] && a.tmp[a.c] == cut[0])
		a.c++;
	a.c -= ft_strchrpos(a.tmp, cut[0]);
	if (a.c > 2)
		return (error_unexpected(a.c, cut[0], &a.tmp));
	act = *tk;
	new = ft_calloc(sizeof(t_token), 1);
	if (!new)
		exit (msg_error(E_MEM, 1, NULL));
	while (a.i < 3)
		new->type[a.i++] = act->type[a.j++];
	if (act->arg)
		free(act->arg);
	new->arg = ft_strndup(a.tmp, ft_strchrpos(a.tmp, cut[0]));
	act->arg = ft_strdup_exit(&a.tmp[ft_strlen(new->arg)]);
	new->next = act->next;
	act->next = new;
	*tk = act;
	free(a.tmp);
	return (SUCCESS);
}

int	splt_tk(t_token **tk, int rep)
{
	int	chk;

	chk = SUCCESS;
	if ((*tk)->type[0] == FALSE && (*tk)->type[3] == T_TXT)
	{
		if (rep > 2)
			return (error_unexpected(rep, (*tk)->arg[0], NULL));
		if (ft_strlen((*tk)->arg) > 1)
		{
			if ((*tk)->arg[0] == '>' && (*tk)->arg[1] != '>')
				chk = splt_tk_start(tk, ">", 0, 0);
			else if ((*tk)->arg[0] == '<' && (*tk)->arg[1] != '<')
				chk = splt_tk_start(tk, "<", 0, 0);
			else if ((*tk)->arg[0] == '>' && (*tk)->arg[1] == '>')
				chk = splt_tk_start(tk, ">>", 0, 1);
			else if ((*tk)->arg[0] == '<' && (*tk)->arg[1] == '<')
				chk = splt_tk_start(tk, "<<", 0, 1);
			else if ((*tk)->arg[0] != '>' && ft_strchr((*tk)->arg, '>'))
				chk = splt_tk_end(tk, ">");
			else if ((*tk)->arg[0] != '<' && ft_strchr((*tk)->arg, '<'))
				chk = splt_tk_end(tk, "<");
		}
	}
	return (chk);
}

int	parse_tk(t_token **tk)
{
	t_token	*tmp;
	int		nd;
	int		num;
	int		restart;

	tmp = *tk;
	nd = 0;
	restart = FALSE;
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
			if (splt_tk(&tmp, num) == E_SNT)
				return (E_SNT);
			while (tmp && (((tmp->arg[0] == '>' && ft_strlen(tmp->arg) > 2 )
				|| (tmp->arg[0] == '>' && tmp->arg[1] == '>' && ft_strlen(tmp->arg) > 2 ))
				|| ((tmp->arg[ft_strlen(tmp->arg)] == '>' && ft_strlen(tmp->arg) > 2 )
				|| (tmp->arg[ft_strlen(tmp->arg)] == '>' && tmp->arg[ft_strlen(tmp->arg) - 1]== '>' && ft_strlen(tmp->arg) > 2 ))))
			{
				splt_tk(&tmp, (tmp->arg[0] == '>') + (tmp->arg[1] == '>'));
				identify(&tmp);
				tmp = tmp->next;
			}
			identify(&tmp);
			(tmp->next == NULL) && (tmp->type[3] = T_CMD);
			// ft_printf(F"%d\n"E, tmp->next->type[3]);
			// (tmp->next != NULL) && (restart = TRUE);
			// ft_printf(O"%s\n"E, tmp->arg);
			// ft_printf(F"%d\n"E, tmp->next->type[3]);
			ft_printf(C"%d\n"E, tmp->type[3]);
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
			if (splt_tk(&tmp, num) == E_SNT)
				return (E_SNT);
			(tmp->next != NULL) && (restart = TRUE);
			// ft_printf(C"%d\n"E, tmp->type[3]);
		}
		// if (tmp->next != NULL && restart)
		// {
		// 	ft_printf("hola\n");
		// 	tmp = *tk;
		// 	nd = 0;
		// 	restart = FALSE;
		// }
		// else
		// {
		// 	tmp = tmp->next;
		// 	nd++;
			(tmp = tmp->next) && nd++;
		// }
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
