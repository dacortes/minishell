/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacortes <dacortes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 12:09:24 by dacortes          #+#    #+#             */
/*   Updated: 2024/07/10 10:54:33 by dacortes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	init_token(t_token **token, char *content, int del)
{
	t_token	*new;

	new = ft_calloc(sizeof(t_env), 1);
	if (!new)
		exit (EXIT_FAILURE);
	new->content = content;
	if (!new->content)
		exit (EXIT_FAILURE);
	new->is_quote += (del == SIMP_QUOTES) * SIMP_QUOTES;
	new->is_quote += (del == DOUBLE_QUOTES) * DOUBLE_QUOTES;
	/* arreglar el type */
	new->type = del;
	add_back((void **)&token, new, sizeof(t_token));
	return (EXIT_SUCCESS);
}

int	metacharacters(t_token **token, char *line, int del, int *pos)
{
	int	end;
	
	if (line[++(*pos)])
		;
	while (!token && line[*pos] && line[*pos] != del)
		++(*pos);
	end = ft_strchrpos(&line[*pos], del);
	if (end == ERROR)
		return (EXIT_SUCCESS);
	init_token(token, ft_strndup(&line[*pos], end), del);
	(*pos) = end;
	if (line[*pos] && line[*pos] == del)
		++(*pos);
	return (EXIT_SUCCESS);
}

int	basic_checker(char *line, int end)
{
	int i = 0;
	int	tmp = 0;

	t_token *token = NULL;

	if (!line[0])
		return (EXIT_SUCCESS);
	while (line[i] && i <= end)
	{
		while(line[i] == ' ')
			i++;
		if (line[i] == DOUBLE_QUOTES)
		{
			// i++;
			// while (line[i] && line[i] != 34 && i <= end)
			// 	i++;
			// if (line[i] != 34)
			// 	return (EXIT_FAILURE);
			// i++;
			metacharacters(&token, line, DOUBLE_QUOTES, &i);
			if (basic_checker(&line[i], end - i))
				return (EXIT_FAILURE);
		}
		else if (line[i] == SIMP_QUOTES) /* 39 == '*/
		{
			i++;
			while (line[i] && line[i] != 39 && i <= end)
				i++;
			if (line[i] != SIMP_QUOTES)
				return (EXIT_FAILURE);
			i++;
			if (basic_checker(&line[i], end - i))
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
				{
					count[1] =  end - tmp - 1;
				}
				tmp++;
			}
			if (count[0] != 0)
				return(EXIT_FAILURE);
			if (basic_checker(&line[i], count[1]))
				return (EXIT_FAILURE);
			i = tmp;
		}
		else
			i++;
	}

	t_token *iter = token;
	if (!iter)
		printf("no asigno memoria");
	while (iter)
	{
		printf("content %s\n", iter->content);
		iter = iter->next;
	}
	return (EXIT_SUCCESS);
}

// int pre_token(t_token **token, char *line, int end)
// {
// 	return (EXIT_SUCCESS);
// }

int parsing(t_minishell *mini)
{
	char	*line;
	int		len;

	line = mini->get_line.read_line;
	len = ft_strlen(line);
	if (basic_checker(line, ft_strlen(line)))
		return (EXIT_FAILURE);
	// if (pre_token(line, len))
	// 	return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}