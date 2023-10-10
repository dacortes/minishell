/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_rdc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacortes <dacortes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 12:49:36 by dacortes          #+#    #+#             */
/*   Updated: 2023/10/10 15:53:32 by dacortes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/shell_mini.h"

int	parse_open(t_rdc **rdc, int type)
{
	if (type == INP)
	{
		if (access((*rdc)->fl, F_OK) == ERROR)
			return (msg_error(E_NSF, 1, (*rdc)->fl));
		if (access((*rdc)->fl, R_OK) == ERROR)
			return (msg_error(E_PRR, 1, (*rdc)->fl));
		(*rdc)->fd[0] = open((*rdc)->fl, O_RDONLY);
		if ((*rdc)->fd[0] == ERROR)
			return (1);
	}
	else if (type == OUT)
	{
		if (!access((*rdc)->fl, F_OK) && access((*rdc)->fl, W_OK))
			return (msg_error(E_PRM, 1, (*rdc)->fl));
		(*rdc)->fd[1] = open((*rdc)->fl, O_TRUNC | O_CREAT | O_WRONLY, 0666);
		if ((*rdc)->fd[0] == ERROR)
			return (1);
	}
	return (ERROR);
}

int	is_stdin_rd(t_token **tk, t_rdc **rdc)
{
	if ((*tk)->type[3] == T_SIR)
	{
		add_rdc(rdc, T_SIR, (*tk)->next->arg);
		parse_open(rdc, INP);
		if (dup2((*rdc)->fd[0], STDIN_FILENO) == ERROR)
		{
			close ((*rdc)->fd[0]);
			return (msg_error(E_PRR, 1, "dup"));
		}
	close ((*rdc)->fd[0]);
	}
	return (SUCCESS);
}

int	is_heredoc(t_token **tk)
{
	char	*inp;

	inp = "";
	if ((*tk)->type[3] == T_RDHD)
	{
		while (inp && (*tk)->next && (*tk)->next->arg)
		{
			inp = readline(O"> "E);
			if (ft_strncmp((*tk)->next->arg, inp, -1) == 0)
			{
				free (inp);
				break ;
			}
			free (inp);
		}
	}
	return (SUCCESS);
}

void	show_rdc(t_rdc *rdc, int md)
{
	t_rdc	*iter;

	if (!rdc)
		return ;
	iter = rdc;
	while ((md == 1) && iter)
	{
		(iter->rd == T_SIR) && ft_printf("is "O"<"E" file: %s\n", iter->fl);
		(iter->rd == T_SOR) && ft_printf("is "O">"E" file: %s\n", iter->fl);
		(iter->rd == T_RDHD) && ft_printf("is "O"<<"E" file: %s\n", iter->fl);
		(iter->rd == T_RDAP) && ft_printf("is "O">>"E" file: %s\n", iter->fl);
		iter = iter->next;
		ft_printf("%p\n", iter);
	}
	while ((md == 2) && iter)
	{

		(iter->rd == T_SIR) && ft_printf("is "O"<"E" file: %s\n", iter->fl);
		(iter->rd == T_SOR) && ft_printf("is "O">"E" file: %s\n", iter->fl);
		(iter->rd == T_RDHD) && ft_printf("is "O"<<"E" file: %s\n", iter->fl);
		(iter->rd == T_RDAP) && ft_printf("is "O">>"E" file: %s\n", iter->fl);
		iter = iter->prev;
	}
}

int	clear_rdc(t_rdc **rdc)
{
	t_rdc *rm;
	t_rdc *tmp;

	if (!rdc || !*rdc)
		return (SUCCESS);
	rm = *rdc;
	while (rm)
	{
		tmp = rm;
		if (rm->fl)
			free(rm->fl);
		rm = rm->next;
		if (tmp)
			free (tmp);
	}	
	return (SUCCESS);
}

/* falta ponerle el status */
t_rdc	*is_redirention(t_token **tk)
{
	t_rdc	*rdc;

	rdc = NULL;
	(void)tk;
	is_stdin_rd(tk, &rdc);
	return (rdc);
}
