/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 12:09:24 by dacortes          #+#    #+#             */
/*   Updated: 2024/08/02 13:52:20 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	basic_checker(t_basic **token, char *line, int end)
{
	int i = 0;
	int	status = 0;

	*token = NULL;
	if (!end || !line[0])
		return (EXIT_SUCCESS);
	while (i <= end && line[i])
	{
		while(line[i] == ' ')
			i++;
		if (line[i] == DOUBLE_QUOTES)
		{
			status = metacharacters(token, line, "\"zz", &i);
			if (status)
				return (status);
		}
		else if (line[i] == SIMP_QUOTES)
		{
			status = metacharacters(token, line, "\'zz", &i);
			if (status)
				return (status);
		}
		else if (line[i] == '&' || line[i] == '|')
		{
			status =  metacharacters(token, line, " &|", &i);
			if (status)
				return (status);
		}
		else if (line[i] == '<' || line[i] == '>')
		{
			status =  metacharacters(token, line, " <>", &i);
			if (status)
				return (status);
		}
		else if (line[i] == '(')
		{
			status = check_subshell(token, line, &i, end);
			if (status)
				return (status);
		}
		else if (line[i] == ')')
            return(error_msg(SYNTAX, 2, ")"));
		else if (line[i])
			status = not_metacharacters(token, line, " zz", &i);
	}
	return (EXIT_SUCCESS);
}

int	get_subshell(t_minishell *subs)
{
	t_basic	*iter;
	t_token			*token;

	iter = subs->token;
	while (iter)
	{
		token = iter->data.token;
		if (token->type == S_SHELL)
		{
			token->token_content.subs->get_line = ft_strdup(token->content);
			if (!token->token_content.subs->get_line)
				exit (error_msg(MALLOC, 1, "get_subshell: get_line"));
			token->token_content.subs->status = parsing(token->token_content.subs);
			if (token->token_content.subs->status)
				return (token->token_content.subs->status);
		}
		iter = iter->next;
	}
	return (EXIT_SUCCESS);
}

int parsing(t_minishell *mini)
{
	char	*line;
	int		len;

	line = mini->get_line;
	if (!line)
		exit (EXIT_SUCCESS);
	len = ft_strlen(line);
	mini->status = basic_checker(&mini->token, line, len);
	if (mini->status)
		return (mini->status);
	if (mini->token)
		add_prev(&mini->token);
	mini->status = syntax_error(&mini->token);
	if (mini->status)
		return (mini->status);
	mini->status = get_subshell(mini);
	if (mini->status)
	 	return (mini->status);
	return (EXIT_SUCCESS);
}
