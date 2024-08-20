/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 16:54:05 by dacortes          #+#    #+#             */
/*   Updated: 2024/08/20 15:48:29 by frankgar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*printf_type(int type)
{
	int			i;
	static int	keys[12] = {OR, AND, ARG, PIPE, R_IN, R_OUT, R_APP, R_HER,
		EXPAN, S_SHELL, WILD_CARD, SYN_ERROR};
	static char	*values[13] = {"OR", "AND", "arg", "PIPE", "Redirection in",
		"Redirection out", "Redirection append", "Redirection her doc",
		"Expansion", "Sub shell", "Wild card", "syntax error", "no type"};

	i = -1;
	while (++i < 11)
	{
		if (type == keys[i])
			return (values[i]);
	}
	return (values[i]);
}

void	printf_subshell(t_basic *content)
{
	ft_printf("%s\n", ORANGE"--------SUBSHEL----------"END);
	content_loop(content, printf_content_token);
	ft_printf("%s\n", ORANGE"------------------------"END);
}

void	aux_print_token(
		void *content, t_token *prev_token, t_basic *prev, t_token *token)
{
	char			*quote;
	char			*expanded;

	quote = BLUE"false"END;
	expanded = YELLOW"false"END;
	if (token->is_quote == SIMP_QUOTES || token->is_quote == DOUBLE_QUOTES)
	{
		ft_printf("%s%c\n", TUR" Type quote: "END, token->is_quote);
		quote = BLUE"true"END;
	}
	if (token->expanded)
		expanded = YELLOW"true"END;
	ft_printf("%s%s\n", TUR" Is quote: "END, quote);
	ft_printf("%s%s\n", TUR" Type: "END, printf_type(token->type));
	ft_printf("%s%s\n", TUR" expanded: "END, expanded);
	ft_printf("%s%d\n", TUR" Has space: "END, token->has_space);
	if (prev)
	{
		prev_token = ((t_basic *)content)->prev->data.token;
		if (prev_token)
			ft_printf("%s%s\n", TUR" PREV: "END, prev_token->content);
	}
}

void	printf_content_token(void *content)
{
	t_token			*token;
	t_token			*prev_token;
	t_basic			*prev;

	prev_token = NULL;
	token = ((t_basic *)content)->data.token;
	prev = ((t_basic *)content)->prev;
	ft_printf("%s%s%s\n", TUR"Content: *"END, token->content, TUR"*"END);
	aux_print_token(content, prev_token, prev, token);
	if (token->type == S_SHELL)
		printf_subshell(token->token_content.subs->token);
}

void	printf_token(t_basic *token)
{
	ft_printf("%s\n", ORANGE"Print Tokens"END);
	content_loop(token, printf_content_token);
}
