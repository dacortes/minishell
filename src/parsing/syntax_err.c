/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_err.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 19:13:49 by frankgar          #+#    #+#             */
/*   Updated: 2024/07/27 11:45:41 by frankgar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	syntax_command(t_token **token)
{
	t_token	*tmp;
	int		arg_count;
	int		subs_count;


	tmp = *token;
	arg_count = 0;
	subs_count = 0;
	while (tmp && !(tmp->type == PIPE || tmp->type & L_OPERAND))
	{
		if (tmp->type & ARG && !(tmp->prev && tmp->prev->type & REDIR))
		{
			if (subs_count)
			{
				tmp->next->type = SYN_ERROR;
				return (error_msg(SYNTAX, 1, "("));
			}
			arg_count++;
		}
		else if (tmp->type == S_SHELL)
		{
			if (subs_count)
			{
				tmp->next->type = SYN_ERROR;
				return (error_msg(SYNTAX, 1, "("));
			}
			else if (arg_count)
			{
				tmp->next->type = SYN_ERROR;
				return (error_msg(SYNTAX, 1, tmp->next->content));
			}
			subs_count++;
		}
		tmp = tmp->prev;
	}
	return (EXIT_SUCCESS);
}

int	syntax_error(t_token **token)
{
	t_token *tmp;
	int		status;

	tmp = *token;
	while (tmp && tmp->next)
	{
		if (tmp->type == PIPE || tmp->type & L_OPERAND)
		{
			status = syntax_command(&tmp->prev);
			if (status) 
				return (status);
		}
		else if (tmp->type & REDIR && (tmp->next && !(tmp->next->type & ARG)))
		{
			tmp->type = SYN_ERROR;
			if (tmp->next->type == S_SHELL)
				return (error_msg(SYNTAX, 1, "("));
			return (error_msg(SYNTAX, 1, tmp->content));
		}
		tmp = tmp->next;
	}
	status = syntax_command(&tmp);
	if (status)
		return (status);
	return (EXIT_SUCCESS);
}
