/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacortes <dacortes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 12:09:24 by dacortes          #+#    #+#             */
/*   Updated: 2024/07/10 16:53:22 by dacortes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	init_token(t_token **token, char *content, int del)
{
	t_token	*new;

	new = ft_calloc(sizeof(t_token), 1);
	if (!new)
		exit (EXIT_FAILURE);
	new->content = content;
	if (!new->content)
		exit (EXIT_FAILURE);
	new->is_quote += (del == SIMP_QUOTES) * SIMP_QUOTES;
	new->is_quote += (del == DOUBLE_QUOTES) * DOUBLE_QUOTES;
	/* arreglar el type */
	new->type = del;
	new->next = NULL;
	add_back((void **)token, new, sizeof(t_token));
	// add_back_token(token, new);
	return (EXIT_SUCCESS);
}

int	metacharacters(t_token **token, char *line, int del, int *pos)
{
	int	end;
	
	if (line[*pos])
		(*pos)++;
	end = ft_strchrpos(&line[*pos], del);
	if (end == ERROR)
		return (EXIT_FAILURE);
	init_token(token, ft_strndup(&line[*pos], end), del);
	(*pos) += end;
	if (line[*pos] == del)
		++(*pos);
	return (EXIT_SUCCESS);
}

int	basic_checker(t_token **token, char *line, int end)
{
	int i = 0;
	int	tmp = 0;

	*token = NULL;
	if (!end || !line[0])
		return (EXIT_SUCCESS);
	while (i <= end && line[i])
	{
		while(line[i] == ' ')
			i++;
		if (line[i] == DOUBLE_QUOTES || line[i] == SIMP_QUOTES)
		{
			if (metacharacters(token, line, line[i], &i))
				return (EXIT_FAILURE);
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
				return(EXIT_FAILURE);
			if (basic_checker(token, &line[i], count[1]))
				return (EXIT_FAILURE);
			i = tmp;
		}
		else
			i++;
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
	if (basic_checker(&mini->token, line, ft_strlen(line)))
		return (EXIT_FAILURE);
	t_token *iter = mini->token;
	if (!iter)
		printf("holi\n");
	while (iter)
	{
		printf("content *%s*\n", iter->content);
		iter = iter->next;
	}
	return (EXIT_SUCCESS);
}