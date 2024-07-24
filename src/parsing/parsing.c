/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 12:09:24 by dacortes          #+#    #+#             */
/*   Updated: 2024/07/24 08:59:59 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	basic_checker(t_token **token, char *line, int end)
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
            return(error_msg(SYNTAX, 2, error_normalization("(")));
		else if (line[i])
			status = not_metacharacters(token, line, " zz", &i);
	}
	return (EXIT_SUCCESS);
}

int parsing(t_minishell *mini)
{
	char	*line;
	int		len;

	line = mini->get_line.read_line;
	if (!line)
		exit (EXIT_SUCCESS);
	len = ft_strlen(line);
	mini->status = basic_checker(&mini->token, line, len);
	if (mini->status)
		return (mini->status);
	if (mini->token)
		add_prev((void **)&mini->token);
	mini->status = syntax_error(&mini->token);
	if (mini->status)
		return (mini->status);
	// mini->status = get_subshell(mini);
	// if (mini->status)
	// 	return (mini->status);
	// mini->status = check_tokens(&mini->token);
	printf_token(mini->token);
	return (EXIT_SUCCESS);
}
