/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_err.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 19:13:49 by frankgar          #+#    #+#             */
/*   Updated: 2024/08/01 15:18:00 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	syntax_command(t_basic_list **content)
{
	t_basic_list	*iter;
	t_token			*token;
	int				arg_count;
	int				subs_count;

	iter = *content;
	if (!iter)
		return (EXIT_FAILURE);
	arg_count = 0;
	subs_count = 0;
	token = iter->list_content.token;
	while (iter && !(token->type == PIPE || token->type & L_OPERAND))
	{
		if (token->type & ARG && !(iter->prev && iter->prev->list_content.token->type & REDIR))
		{
			ft_printf("estoy dentro\n");
			if (subs_count)
			{
				iter->next->list_content.token->type = SYN_ERROR;
				return (error_msg(SYNTAX, 1, "("));
			}
			arg_count++;
		}
		else if (token->type == S_SHELL)
		{
			if (subs_count)
			{
				iter->next->list_content.token->type = SYN_ERROR;
				return (error_msg(SYNTAX, 1, "("));
			}
			else if (arg_count)
			{
				iter->next->list_content.token->type = SYN_ERROR;
				return (error_msg(SYNTAX, 1, iter->next->list_content.token->content));
			}
			subs_count++;
		}
		token = iter->list_content.token;
		iter = iter->prev;
	}
	if (!arg_count && !subs_count)
		return (error_msg(SYNTAX, 1, token->content));
	return (EXIT_SUCCESS);
}

int	syntax_error(t_basic_list **content)
{
	t_basic_list	*iter;
	t_token			*token;
	int				status;

	iter = *content;
	while (iter)
	{
		token = iter->list_content.token;
		if (token->type == PIPE || token->type & L_OPERAND)
		{
			status = syntax_command(&iter->prev);
			if (status) 
				return (error_msg(SYNTAX, 1, token->content));
		}
		else if (token->type & REDIR && ((iter->next && !(iter->next->list_content.token->type & ARG))
			|| !iter->next))
		{
			token->type = SYN_ERROR;
			if (iter->next && iter->next->list_content.token->type == S_SHELL)
				return (error_msg(SYNTAX, 1, "("));
			return (error_msg(SYNTAX, 1, token->content));
		}
		if (iter->next)
			iter = iter->next;
		else
			break;
	}
	status = syntax_command(&iter);
	if (status)
		return (status);
	return (EXIT_SUCCESS);
}