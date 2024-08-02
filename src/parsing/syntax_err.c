/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_err.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 19:13:49 by frankgar          #+#    #+#             */
/*   Updated: 2024/08/02 13:52:20 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	syntax_command(t_basic **content, int redir_flag)
{
	t_basic	*iter;
	t_token			*token;
	int				arg_count;
	int				subs_count;

	iter = *content;
	if (!iter)
		return (EXIT_FAILURE);
	arg_count = 0;
	subs_count = 0;
	token = iter->data.token;
	while (iter && !(token->type == PIPE || token->type & L_OPERAND))
	{
		token = iter->data.token;
		if (token->type & ARG && !(iter->prev && iter->prev->data.token->type & REDIR))
		{
			if (subs_count)
			{
				iter->next->data.token->type = SYN_ERROR;
				return (error_msg(SYNTAX, 1, "("));
			}
			arg_count++;
		}
		else if (token->type == S_SHELL)
		{
			if (subs_count)
			{
				iter->next->data.token->type = SYN_ERROR;
				return (error_msg(SYNTAX, 1, "("));
			}
			else if (arg_count)
			{
				iter->next->data.token->type = SYN_ERROR;
				return (error_msg(SYNTAX, 1, iter->next->data.token->content));
			}
			subs_count++;
		}
		iter = iter->prev;
	}
	if (!arg_count && !subs_count && !redir_flag)
		return (error_msg(SYNTAX, 1, token->content));
	return (EXIT_SUCCESS);
}

int	syntax_error(t_basic **content)
{
	t_basic	*iter;
	t_token			*token;
	int				status;
	int				redir_flag;

	redir_flag = 0;
	iter = *content;
	while (iter)
	{
		token = iter->data.token;
		if (token->type == PIPE || token->type & L_OPERAND)
		{
			status = syntax_command(&iter->prev, redir_flag);
			if (status) 
				return (error_msg(SYNTAX, 1, token->content));
			redir_flag = 0;
		}
		else if (token->type & REDIR && iter->next && iter->next->data.token->type & ARG)
			redir_flag = 1;
		else if (token->type & REDIR && ((iter->next && !(iter->next->data.token->type & ARG))
			|| !iter->next))
		{
			token->type = SYN_ERROR;
			if (iter->next && iter->next->data.token->type == S_SHELL)
				return (error_msg(SYNTAX, 1, "("));
			return (error_msg(SYNTAX, 1, token->content));
		}
		if (iter->next)
			iter = iter->next;
		else
			break;
	}
	status = syntax_command(&iter, redir_flag);
	if (status)
		return (status);
	return (EXIT_SUCCESS);
}