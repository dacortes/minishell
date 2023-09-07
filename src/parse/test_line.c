/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacortes <dacortes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 14:52:48 by dacortes          #+#    #+#             */
/*   Updated: 2023/09/07 11:23:43 by dacortes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/shell_mini.h"

int	tets_add_token(t_token **tk, char *arg, int type)
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
	if (!(*tk))
		*tk = new;
	else
	{
		new->next = *tk;
		(*tk) = new;
	}
	return (SUCCESS);
}

// t_token *tets_add_token(t_token **cur, char *arg, int type)
// {
//     t_token *new;

//     new = ft_calloc(sizeof(t_token), 1);
//     if (!new)
//         exit (msg_error(E_MEM, 1, NULL));
//     new->arg = ft_strdup(arg);
//     if (!new->arg)
//         exit (msg_error(E_MEM, 1, NULL));
//     new->type = type;
// 	new->next = NULL;
// 	if (!(*cur))
// 		*cur = new;
// 	else
// 	{
// 		new->next = *cur;
// 		*cur = new;
// 	}
//     ft_printf(R"%p\n"E, new);
//     return (*cur);
// }


int	test_add_line(t_line **ln, t_token *tk)
{
	t_line	*new;

	new = ft_calloc(sizeof(t_line), 1);
	if (!new)
		exit (msg_error(E_MEM, 1, NULL));
	new->tk = tk;
	new->next = NULL;
	ft_printf(F"%p\n"E, new);
	if (!(*ln))
		*ln = new;
	else
	{
		new->next = *ln;
		*ln = new;
	}
	return (SUCCESS);
}

int test_clear_tk(t_token **tk)
{
	t_token *rm = *tk;
	t_token	*tmp;
	
	while (rm)
	{
        if (rm->arg)
        {
            ft_printf(Y"%p\n"E, rm);
            ft_printf(C"%s\n"E, rm->arg);
            free(rm->arg);
        }
        tmp = rm;
        rm = rm->next;
        free(tmp);
	}
	*tk = NULL;
	return (SUCCESS);
}

int	test_clear_ln(t_line **ln)
{
	t_line	*rm = *ln;
	t_line	*tmp;	

	while (rm)
	{
		ft_printf(B"%p\n"E, rm);
		ft_printf(Y"%p\n"E, (*ln)->tk);
		test_clear_tk(&(*ln)->tk);
		tmp = rm;
		rm = rm->next;
		free(tmp);
	}
	*ln = NULL;
	return (SUCCESS);
}

int	test_line(char *inp, t_line **ln)
{
	int i = 0;
	t_token *tk = NULL;
	(void)i;
	(void)inp;
	// (*ln)->argc = 0;
	// if (!tk)
	// 	exit (msg_error(E_MEM, 1, NULL));
	while (i <= 2)
		tets_add_token(&tk, inp, i++);
	test_add_line(ln, tk);
	return (SUCCESS);
}