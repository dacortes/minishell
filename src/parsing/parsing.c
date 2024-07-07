/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacortes <dacortes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 12:09:24 by dacortes          #+#    #+#             */
/*   Updated: 2024/07/07 18:25:24 by dacortes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <minishell.h>

int recursive_check(t_minishell *mini, char *line, int *iter, int *count)
{
	if (line[*iter] == '(')
	{
		int	pos = *iter;
		int	check = 0;
		while (line[pos] && line[pos] == '(')
		{
			if  (check >= 1)
				return (EXIT_FAILURE);
			pos++;
			check++;
		}
		(*iter)++;
		while (line[*iter] && line[*iter] != '(' && line[*iter] != ')')//guardar el  str
			(*iter)++;
		(*count)++;
		recursive_check(mini, line, iter, count);
	}
	else if(line[*iter] == ')')
	{
		(*iter)++;
		while (line[*iter] && line[*iter] != '(' && line[*iter] != ')')
			(*iter)++;
		(*count)--;
		recursive_check(mini, line, iter, count);
	}
	if (*count != 0)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	basic_checker(char *line, int end)
{
	int i = -1;
	int	tmp = 0;

	while (line[++i] && i <= end)
	{
		/* "=34 '=39 */
		if (line[i] == 34)
		{
			while (line[++i] != '\0' && line[i] != 34 && i <= end)
				;
			if (line[i] == '\0')
				return (EXIT_FAILURE);
		}
		else if (line[i] == 39)
		{
			while (line[++i] != '\0' && line[i] != 39 && i <= end)
				;
			if (line[i] == '\0')
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
			if (analyse_line(&line[i], count[1]))
				return (EXIT_FAILURE);
			i = tmp;
		}
		else if (line[i] == ' ')
			i++;
	}
	return (EXIT_SUCCESS);
}

int pre_token(char *line, int end)
{
	int i = -1;
	int	tmp = 0;
	t_token	*token;
	t_token	*new;

	token = NULL;
	while (line[++i] && i <= end)
	{
		new = ft_calloc(sizeof(t_token), 1);
		/* "=34 '=39 */
		if (line[i] == 34)
		{
			while (line[++i] != '\0' && line[i] != 34 && i <= end)
				;
		}
		else if (line[i] == 39)
		{
			while (line[++i] != '\0' && line[i] != 39 && i <= end)
				;
		}
		else if (line[i] == '(' || line[i] == ')')
		{
			int count[2] = {1, -2};
			i++;
			tmp = i;
			new->type = ;
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
			if (analyse_line(&line[i], count[1]))
				return (EXIT_FAILURE);
			i = tmp;
		}
		else if (line[i] == ' ')
			i++;
	}
	return (EXIT_SUCCESS);
}

int parsing(t_minishell *mini)
{
	char	*line;
	int		len;

	line = mini->get_line.read_line;
	len = ft_strlen(line);
	if (basic_checker(line, ft_strlen(line)))
		return (EXIT_FAILURE);
	if (pre_token(line, len))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}