/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_err.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 19:13:49 by frankgar          #+#    #+#             */
/*   Updated: 2024/07/24 10:13:01 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char *get_token_cont(int flag)
{
	if (flag == AND)
		return ("&&");
	else if (flag == OR)
		return ("||");
	else if (flag == ARG)
		return ("cmd");
	else if (flag == PIPE)
		return ("|");
	else if (flag == R_IN)
		return ("<");
	else if (flag == R_OUT)
		return (">");
	else if (flag == R_APP)
		return (">>");
	else if (flag == R_HER)
		return ("<<");
	else if (flag == EXPAN)
		return ("$");
	else if (flag == S_SHELL)
		return (")");
	else if (flag == WILD_CARD)
		return ("*");
	return (NULL);
}

int check_prev_arg(t_token *list, int target)
{
	if (list && list->type & target)
	{
			return (TRUE);
	}
	return (FALSE);
}

int	syntax_error(t_token **token)
{
	t_token *tmp;

	tmp = *token;
	while (tmp && tmp->next)
	{	
		if (tmp->type == OR || tmp->type == PIPE || tmp->type == AND)
		{
			if (!check_prev_arg(tmp, ARG | EXPAN | S_SHELL | WILD_CARD)) 
				return (error_msg(SYNTAX, 1, get_token_cont(tmp->type)));
		}
		else if (tmp->type >= R_IN && tmp->type <= R_HER)
		{
			if (tmp->next && !(tmp->next->type & (EXPAN | ARG | WILD_CARD)))
				return (error_msg(SYNTAX, 1, get_token_cont(tmp->type)));
		}
		tmp = tmp->next;
	}
	if (tmp && !check_prev_arg(tmp, ARG | EXPAN | S_SHELL | WILD_CARD))
		return (error_msg(SYNTAX, 1, get_token_cont(tmp->type)));
	return (EXIT_SUCCESS);
}
