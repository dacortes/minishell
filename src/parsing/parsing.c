/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacortes <dacortes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 12:09:24 by dacortes          #+#    #+#             */
/*   Updated: 2024/07/08 17:56:50 by dacortes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <minishell.h>
#include <stdarg.h>

// int	metacharacters(t_token **token, char *line, int del, int *pos)
// {
// 	if (line[*pos] == del)
// 	{
// 		++(*pos);
// 		while (!token && line[*pos] && line[*pos] != del)
// 			++(*pos);
		
// 	}
// 	return (EXIT_SUCCESS);
// }

int	basic_checker(char *line, int end)
{
	int i = 0;
	int	tmp = 0;

	if (!line[0])
		return (EXIT_SUCCESS);
	while (line[i] && i <= end)
	{
		while(line[i] == ' ')
			i++;
		if (line[i] == DOUBLE_QUOTES)
		{
			i++;
			while (line[i] && line[i] != 34 && i <= end)
				i++;
			if (line[i] != 34)
				return (EXIT_FAILURE);
			i++;
			if (basic_checker(&line[i], end - i))
				return (EXIT_FAILURE);
		}
		else if (line[i] == 39) /* 39 == '*/
		{
			i++;
			while (line[i] && line[i] != 39 && i <= end)
				i++;
			if (line[i] != 39)
				return (EXIT_FAILURE);
			i++;
			if (basic_checker(&line[i], end - i))
			{
				printf("40\n");
				return (EXIT_FAILURE);
			}
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