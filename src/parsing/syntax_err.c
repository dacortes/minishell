/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_err.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frankgar <frankgar@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 19:13:49 by frankgar          #+#    #+#             */
/*   Updated: 2024/07/22 16:37:49 by frankgar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char *get_token_cont(int flag)
{
	if (flag == AND)
		return ("&&");
	else if (flag == ARG)
		return ("cmd");
	else if (flag == PIPE)
		return ("|");
	else if (flag == R_IN)
		return ("<");
	else if (flag == R_OUT)
		return (">");
	else if (flag == R_APP)
		return (">>");
	else if (flag == R_HER)
		return ("<<");
	else if (flag == EXPAN)
		return ("$");
	else if (flag == S_SHELL)
		return (")");
	return (NULL);
}

int get_prev_arg(t_token *start, t_token *end, int target)
{
	if (start && end)
	{
		while(start != end)
		{
			if (start->type == target)
				return (1);
			start = start->next;
		}
	}
	return (0);
}

int	syntax_error(t_token **token)
{
	t_token *tmp;
	int		heardoc_flag;

	heardoc_flag = 0;
	tmp = *token;
	while (tmp)
	{
		if (tmp->type == OR || tmp->type == PIPE || tmp->type == AND)
		{
			if (!get_prev_arg(*token, tmp, ))
				return (error_msg(SYNTAX, 1, get_token_cont(tmp->type)));
		}
		else if (tmp->type >= R_IN && tmp->type <= R_HER)
		{
			if (tmp->next && tmp->next->type != ARG || tmp->next->type != EXPAN)
				return (error_msg(SYNTAX, 1, get_token_cont(tmp->type)));
		}
		tmp = tmp->next;
	}
}

int main()
{
}
