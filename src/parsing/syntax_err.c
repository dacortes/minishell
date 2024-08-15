/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_err.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 19:13:49 by frankgar          #+#    #+#             */
/*   Updated: 2024/08/15 17:26:58 by frankgar         ###   ########.fr       */
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
				return (error_msg(SYNTAX, 2, "("));
			}
			arg_count++;
		}
		else if (token->type == S_SHELL)
		{
			if (subs_count)
			{
				iter->next->data.token->type = SYN_ERROR;
				return (error_msg(SYNTAX, 2, "("));
			}
			else if (arg_count)
			{
				while (iter && !(iter->data.token->type & ARG && !(iter->prev->data.token->type & REDIR)))
					iter = iter->next;
				iter->data.token->type = SYN_ERROR;
				return (error_msg(SYNTAX, 2, iter->data.token->content));
			}
			subs_count++;
		}
		iter = iter->prev;
	}
	if (!arg_count && !subs_count && !redir_flag)
		return (error_msg(SYNTAX, 2, token->content));
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
				return (status);
			redir_flag = 0;
		}
		else if (token->type & REDIR && iter->next && iter->next->data.token->type & ARG)
			redir_flag = 1;
		else if (token->type & REDIR && ((iter->next && !(iter->next->data.token->type & ARG))
			|| !iter->next))
		{
			token->type = SYN_ERROR;
			if (iter->next && iter->next->data.token->type == S_SHELL)
				return (error_msg(SYNTAX, 2, "("));
			return (error_msg(SYNTAX, 2, token->content));
		}
		else if (token->type == S_SHELL && (iter->prev 
			&& !(iter->prev->data.token->type & L_OPERAND 
			|| iter->prev->data.token->type == PIPE)))
				return (error_msg(SYNTAX, 2, "("));
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
