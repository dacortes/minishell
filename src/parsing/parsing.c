/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacortes <dacortes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 12:09:24 by dacortes          #+#    #+#             */
/*   Updated: 2024/07/18 14:47:45 by dacortes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	basic_checker(t_token **token, char *line, int end)
{
	int i = 0;
	int	tmp = 0;
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
		else if (line[i] == '(' || line[i] == ')')
		{
			
			if  (line[i] == ')')
				return (EXIT_FAILURE);
			int count[2] = {1, -2};
			i++;
			tmp = i;
			while (line[tmp] && tmp <= end)
			{
				if (line[tmp] == '(')
					count[0]++;
				else if (line[tmp] == ')')
					count[0]--;
				if(count[0] == 0 && count[1] == -1)
					count[1] =  end - tmp - 1;
				tmp++;
			}
			if (count[0] != 0)
				return(error_msg(SYNTAX, 2, error_normalization("(")));
			if (basic_checker(token, &line[i], count[1]))
				return (2);
			i = tmp;
		}
		else if (line[i])
			status = not_metacharacters(token, line, " zz", &i);
	}
	return (EXIT_SUCCESS);
}

int	check_tokens(t_token **token)
{
	t_token	*iter;

	iter = *token;
	while (iter)
	{
		if (iter->content && ft_strlen(iter->content) == 2)
		{
			ft_printf("soy una patata: %s\n", iter->content);
		}
		iter = iter->next;
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
	// mini->status = check_tokens(&mini->token);
	printf_token(mini->token);
	return (EXIT_SUCCESS);
}