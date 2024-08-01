/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 16:54:05 by dacortes          #+#    #+#             */
/*   Updated: 2024/08/01 15:27:07 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>


char	*printf_type(int type)
{
	int		i;
	int		keys[12] = {OR, AND, ARG, PIPE, R_IN, R_OUT, R_APP, R_HER, EXPAN,
			S_SHELL, WILD_CARD, SYN_ERROR};
	char	*values[13] = {"OR", "AND", "arg", "PIPE", "Redirection in",
		"Redirection out", "Redirection append", "Redirection her doc",
		"Expansion", "Sub shell", "Wild card", "syntax error", "no type"};
	
	i = -1;
	while (++i < 11)
	{
		if (type == keys[i])
			return values[i];
	}
	return (values[i]);
}

void	printf_subshell(t_basic_list *content)
{
	ft_printf("%s\n", ORANGE"--------SUBSHEL----------"END);
	iter_list_list_content(content, printf_content_token);
	ft_printf("%s\n", ORANGE"------------------------"END);
}

void	printf_content_token(void *content)
{
	char			*quote;
	t_token			*token;
	t_token			*prev_token;
	t_basic_list	*prev;

	token = ((t_basic_list *)content)->list_content.token;
	prev = ((t_basic_list *)content)->prev;
	quote = BLUE"false"END;
	ft_printf("%s%s%s\n", TUR"Content: *"END, token->content, TUR"*"END);
	if (token->is_quote == SIMP_QUOTES || token->is_quote == DOUBLE_QUOTES)
	{
		ft_printf("%s\n", TUR" Type quote: "END, token->is_quote);
		quote = BLUE"true"END;
	}
	ft_printf("%s%s\n", TUR" Is quote: "END, quote);
	ft_printf("%s%d\n", TUR" Has space: "END, token->has_space);
	ft_printf("%s%s\n", TUR" Type: "END, printf_type(token->type));
	if (prev)
	{
		prev_token = ((t_basic_list *)content)->prev->list_content.token;
		if (prev_token)
			ft_printf("%s%s\n", TUR" PREV: "END, prev_token->content);
	}
	if (token->type == S_SHELL)
		printf_subshell(token->token_content.subs->token);
}

void	printf_token(t_basic_list *token)
{
	ft_printf("%s\n", ORANGE"Print Tokens"END);
	iter_list_list_content(token, printf_content_token);
}
