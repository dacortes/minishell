/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 12:57:10 by codespace         #+#    #+#             */
/*   Updated: 2024/08/08 08:44:53 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	foo(void *node, void *end)
{
	(void)end;
	t_token	*token;

	return (token->type == PIPE || token->type == AND
		|| token->type == OR || token->type == S_SHELL);
}

int	expand_token(t_basic *token) //añadir el ptr end de frank
{
	int end;

	bool_loop_void(token, foo, end);
	return (EXIT_SUCCESS);
}