/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacortes <dacortes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 14:52:48 by dacortes          #+#    #+#             */
/*   Updated: 2023/09/06 19:09:42 by dacortes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/shell_mini.h"

int	tets_add_token(t_line **ln, char *arg, int type)
{
	t_token *new;

	new = ft_calloc(sizeof(t_token), 1);
	if (!new)
		exit (msg_error(E_MEM, 1, NULL));
	new->arg = ft_strdup(arg);
	if (!new->arg)
		exit (msg_error(E_MEM, 1, NULL));
	new->type = type;
	new->next = NULL;
	ft_printf(R"%p\n"E, new);
	if (!(*ln)->tk)
		(*ln)->tk->next = new;
	else
	{
		new->next = (*ln)->tk;
		(*ln)->tk = new;
	}
	(*ln)->argc++;
	return (SUCCESS);
}

int	test_add_line(t_line **ln)
{
	t_line	*new;

	new = ft_calloc(sizeof(t_line), 1);
	if (!new)
		exit (msg_error(E_MEM, 1, NULL));
	new->next = NULL;
	ft_printf(F"%p\n"E, new);
	if (!(*ln))
		*ln = new;
	else
	{
		new->next = *ln;
		*ln = new;
	}
	(*ln)->argc++;
	ft_printf(F"%p\n"E, *ln);
	return (SUCCESS);
}

int test_clear_tk(t_line **ln)
{
	t_token *rm = (*ln)->tk;
	
	while (rm)
	{
		//ft_printf(R"%s\n"E, rm->arg);
		if (rm->arg)
			free(rm->arg);
		free(rm);
		rm = rm->next;
	}
	return (SUCCESS);
}

int	test_clear_ln(t_line **ln)
{
	t_line	*rm = *ln;
	t_line	*tmp;	

	while (rm)
	{
		ft_printf(B"%p\n"E, rm);
		test_clear_tk(ln);
		tmp = rm;
		rm = rm->next;
		free(tmp);
	}
	return (SUCCESS);
}

int	test_line(char *inp, t_line **ln)
{
	int i = 0;
	(void)inp;
	(*ln)->argc = 0;
	// (*ln)->tk = ft_calloc(sizeof(t_token), 1);
	// if (!(*ln)->tk)
	// 	exit (msg_error(E_MEM, 1, NULL));
	// while (i <= 2)
	// 	tets_add_token(ln, inp, i++);
	test_add_line(ln);
	ft_printf(Y"%d"E, i++);
	// test_clear_tk(ln);
	return (SUCCESS);
}