/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 16:54:05 by dacortes          #+#    #+#             */
/*   Updated: 2024/07/24 18:13:45 by frankgar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*printf_type(int type)
{
	char	*result;

	result = "no type";
	if (type == OR)
		result = "OR";
	else if (type == AND)
		result = "AND";
	else if (type == ARG)
		result = "arg";
	else if (type == PIPE)
		result = "PIPE";
	else if (type == R_IN)
		result = "Redirection in";
	else if (type == R_OUT)
		result = "Redirection out";
	else if (type == R_APP)
		result = "Redirection append";
	else if (type == R_HER)
		result = "Redirection her doc";
	else if (type == EXPAN)
		result = "Expansion";
	else if (type == S_SHELL)
		result = "Sub shell";
	else if (type == WILD_CARD)
		result = "Wild card";
	return (result);
}

int	printf_env(t_env *env)
{
	t_env	*iter;

	iter = env;
	ft_printf("%sPrint Tokens%s\n", ORANGE, END);
	while (iter)
	{
		ft_printf("%skey: *%s%s%s*%s\n", TUR, END, iter->key, TUR, END);
		ft_printf("%svalue: *%s%s%s*%s\n", TUR, END, iter->value, TUR, END);
		iter = iter->next;
	}
	return (EXIT_SUCCESS);
}

int	printf_token(t_token *token, char *col)
{
	t_token	*iter;
	char	*quote;

	iter = token;
	ft_printf("%sPrint Tokens%s\n", ORANGE, END);
	while (iter)
	{
		quote = "\033[1;34mfalse\033[m";
		ft_printf("%sContent: *%s%s%s*%s\n", col, END, iter->content, TUR, END);
		if (iter->is_quote == SIMP_QUOTES || iter->is_quote == DOUBLE_QUOTES)
		{
			ft_printf("%s Quote:%s %c\n", col, END, iter->is_quote);
			quote = "\033[1;34mtrue\033[m";
		}
		ft_printf("%s Is quote:%s %s\n", col, END, quote);
		ft_printf("%s Has space:%s %d\n", col, END, iter->has_space);
		ft_printf("%s Type:%s %s\n", col, END, printf_type(iter->type));
		if (iter->prev)
			ft_printf("%s PREV:%s %s\n", col, END, iter->prev->content);
		if (iter->type == S_SHELL)
		{
			ft_printf("%s--------SUBSHEL----------%s\n", ORANGE, END);
			if (!ft_strncmp(col, TUR, 10))
			{
				printf_token(iter->subs.token, CYAN);
			}
			if (!ft_strncmp(col, CYAN, 10))
			{
				printf_token(iter->subs.token, GREEN);
			}
			if (!ft_strncmp(col, GREEN, 10))
			{
				printf_token(iter->subs.token, YELLOW);
			}
			if (!ft_strncmp(col, YELLOW, 10))
			{
				printf_token(iter->subs.token, TUR);
			}
			ft_printf("%s------------------------%s\n", ORANGE, END);
		}
		iter = iter->next;
	}
	return (EXIT_SUCCESS);
}
