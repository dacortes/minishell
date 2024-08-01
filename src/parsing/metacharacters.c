/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   metacharacters.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 13:25:51 by codespace         #+#    #+#             */
/*   Updated: 2024/08/01 13:26:43 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	metacharacters(t_basic_list **token, char *line, char *del, int *pos)
{
	int		end;
	int		len;
	int		space;
	char	delimiter[1];
	int		status;

	space = 0;
	delimiter[0] = del[0];
	len = ft_strlen(del);
	if (line[*pos] && del[0] != ' ' && len > 1)
		(*pos)++;
	end = ft_strchrpos(&line[*pos], del[0]);
	if (end == ERROR && del[0] != ' ')
		return (error_msg(SYNTAX, 2, delimiter));
	space = set_space(line, pos, del);
	if (end == ERROR)
		end = get_end_token(line, del, pos, len);
	status = init_token(token, ft_strndup(&line[*pos], end), del, space);
	(*pos) += end;
	if (del[0] != ' ' && line[*pos] == del[0])
		++(*pos);
	if (status)
		return (status);
	return (EXIT_SUCCESS);
}

int	not_metacharacters(t_basic_list **token, char *line, char *del, int *pos)
{
	int	end;
	int	space;

	end = get_end_not_metacharacters(&line[*pos]);
	space = set_space(line, pos, del);
	init_token(token, ft_strndup(&line[*pos], end), del, space);
	(*pos) += end;
	return (EXIT_SUCCESS);
}

int	metacharacters_sub(t_basic_list **token, char *line, int start, int end)
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

int	check_subshell(t_basic_list **token, char *line, int *pos, int end)
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
