/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frankgar <frankgar@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 12:44:22 by frankgar          #+#    #+#             */
/*   Updated: 2024/08/20 13:00:28 by frankgar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	set_syntax_error(t_token *token, t_basic *iter)
{
	if (token->type == REDIR)
	{
		token->type = SYN_ERROR;
		if (iter->next && iter->next->data.token->type == S_SHELL)
			return (error_msg(SYNTAX, 2, "("));
		return (error_msg(SYNTAX, 2, token->content));
	}
	else if (token->type == S_SHELL)
	{
		token->type = SUBS_SYN_ERR;
		return (error_msg(SYNTAX, 2, "("));
	}
	return (2);
}
