/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   metacharacters.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 13:25:51 by codespace         #+#    #+#             */
/*   Updated: 2024/08/13 10:21:24 by frankgar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	get_end(char *line, char *del, int *pos, char *delimiter)
{
	int end;
	int	len;

	len = ft_strlen(del);
	end = ft_strchrpos(&line[*pos], del[0]);
	if (end == NOT_FOUND && del[0] != ' ')
		return (error_msg(SYNTAX, 2, delimiter), ERROR);
	if (!(*delimiter == SIMP_QUOTES || *delimiter == DOUBLE_QUOTES)
		&& !is_metacharacters(line[*pos]) && end != ERROR)
		end = NOT_FOUND;
	if (end == NOT_FOUND)
		end = get_end_token(line, del, pos, len);
	return (end);
}

int	metacharacters(t_basic **token, char *line, char *del, int *pos)
{
	int		end;
	int		len;
	int		space;
	char	delimiter[2];
	int		status;

	space = 0;
	delimiter[0] = line[*pos];
	delimiter[1] = '\0';
	len = ft_strlen(del);
	if (line[*pos] && del[0] != ' ' && len > 1)
		(*pos)++;
	end = get_end(line, del, pos, delimiter);
	if (end == ERROR)
		return (2);
	space = set_space(line, pos, del);
	status = init_token(token, ft_strndup(&line[*pos], end), del, space);
	(*pos) += end;
	if (del[0] != ' ' && line[*pos] == del[0])
		++(*pos);
	if (status)
		return (status);
	return (EXIT_SUCCESS);
}


int	not_metacharacters(t_basic **token, char *line, char *del, int *pos)
{
	int	end;
	int	space;

	end = get_end_not_metacharacters(&line[*pos]);
	space = set_space(line, pos, del);
	init_token(token, ft_strndup(&line[*pos], end), del, space);
	(*pos) += end;
	return (EXIT_SUCCESS);
}

int	metacharacters_sub(t_basic **token, char *line, int start, int end)
{
	int	space;
	int	status;

	status = 0;
	space = set_space(line, &start, "(");
	status = init_token(token, ft_strndup(&line[start], end - 1), ")", space);
	if (status)
		return (status);
	return (EXIT_SUCCESS);
}

int	check_subshell(t_basic **token, char *line, int *pos, int end)
{
	int	count;
	int	size;
	int	tmp;

	count = 1;
	tmp = *pos + 1;
	while (tmp < end && line[tmp] && count > 0)
	{
		if (line[tmp] == '(')
			++count;
		if (line[tmp] == ')')
			--count;
		tmp++;
	}
	if (count != 0 || (line[tmp - 2] && line[tmp -2] == '('))
		return(error_msg(SYNTAX, 2, ")"));
	size = tmp - *pos - 1;
	metacharacters_sub(token, line, *pos + 1, size);
	*pos = tmp;
	return (EXIT_SUCCESS);
}
