/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacortes <dacortes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 16:54:05 by dacortes          #+#    #+#             */
/*   Updated: 2024/07/13 12:25:56 by dacortes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <minishell.h>

int	printf_token(t_token *token)
{
	t_token	*iter;
	char	*quote;

	iter = token;
	quote = "\033[1;34mfalse\033[m";
	ft_printf("%sPrint Tokens%s\n", ORANGE, END);
	while (iter)
	{
		ft_printf("%sContent: *%s%s%s*%s\n", TUR, END, iter->content, TUR, END);
		if (iter->is_quote == SIMP_QUOTES || iter->is_quote == DOUBLE_QUOTES)
		{
			ft_printf("%s Quote:%s %c\n", TUR, END, iter->is_quote);
			quote = "\033[1;34mtrue\033[m";
		}
		ft_printf("%s Is quote:%s %s\n", TUR, END, quote);
		ft_printf("%s has space:%s %d\n", TUR, END, iter->has_space);
		/* imprimir el type normalizado */
		iter = iter->next;
	}
	ft_printf("");
	return (EXIT_SUCCESS);
}