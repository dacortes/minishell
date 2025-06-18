/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 14:13:54 by dacortes          #+#    #+#             */
/*   Updated: 2024/08/18 20:41:24 by frankgar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	is_metacharacters(char c)
{
	return (c != ' ' && c != SIMP_QUOTES && c != DOUBLE_QUOTES && c != '('
		&& c != ')' && c != '&' && c != '|' && c != '<' && c != '>');
}

short	get_type(char *flag, char *content)
{
	if (ft_strlen(flag) == 1 && flag[0] == ')')
		return (S_SHELL);
	if (ft_strlen(flag) == 3 && flag[0] != SIMP_QUOTES)
	{
		if (ft_strlen(content) == 1 && content[0] == '|')
			return (PIPE);
		else if (ft_strlen(content) == 1 && content[0] == '<')
			return (R_IN);
		else if (ft_strlen(content) == 1 && content[0] == '>')
			return (R_OUT);
		else if (ft_strlen(content) == 2 && !ft_strncmp("<<", content, 2))
			return (R_HER);
		else if (ft_strlen(content) == 2 && !ft_strncmp(">>", content, 2))
			return (R_APP);
		else if (ft_strlen(content) == 2 && !ft_strncmp("||", content, 2))
			return (OR);
		else if (ft_strlen(content) == 2 && !ft_strncmp("&&", content, 2))
			return (AND);
	}
	return (ARG);
}

int	set_space(char *line, int *pos, char *del)
{
	int	i;
	int	space;

	i = *pos;
	space = 0;
	if (!line || !line[0])
		return (space);
	if (*pos >= 1)
	{
		i -= (del[0] == ' ') * 1;
		i -= (del[0] != ' ') * 2;
		while (i >= 0 && line[i] && (line[i] == ' ' || line[i] == '\t'))
		{
			--i;
			++space;
		}
	}
	return (space);
}

int	get_end_not_metacharacters(char *str)
{
	int	pos;

	pos = 0;
	if (!str)
		return (pos);
	while (str[pos] && is_metacharacters(str[pos]))
		pos++;
	return (pos);
}

int	get_end_token(char *str, char *del, int *pos, int size_del)
{
	int	len;

	len = ft_strlen(&str[*pos]);
	if (size_del > 1)
	{
		len = 1;
		if ((str[*pos] && str[*pos] == del[1])
			|| (str[*pos] && str[*pos] == del[2]))
		{
			if (((str[(*pos)] && str[(*pos)] == del[1])
					&& (str[(*pos) + 1] && str[(*pos) + 1] == del[1]))
				|| ((str[(*pos)] && str[(*pos)] == del[2])
					&& (str[(*pos) + 1] && str[(*pos) + 1] == del[2])))
				len = 2;
		}
	}
	return (len);
}
