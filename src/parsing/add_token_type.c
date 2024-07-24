/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_token_type.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 14:28:08 by dacortes          #+#    #+#             */
/*   Updated: 2024/07/24 09:00:51 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	init_token(t_token **token, char *content, char *del, int space)
{
	t_token	*new;

	if (!content)
		exit (error_msg(MALLOC, 1, "init_token: content"));
	new = ft_calloc(sizeof(t_token), 1);
	if (!new)
		exit (error_msg(MALLOC, 1, "init_token: new"));
	new->content = content;
	new->is_quote = 0;
	new->is_quote += (del[0] == SIMP_QUOTES) * SIMP_QUOTES;
	new->is_quote += (del[0] == DOUBLE_QUOTES) * DOUBLE_QUOTES;
	new->type = get_type(del, new->content);
	new->has_space = space;
	new->next = NULL;
	add_back((void **)token, new, T_TOKEN);
	return (EXIT_SUCCESS);
}

int	metacharacters_sub(t_token **token, char *line, int start, int end)
{
	int	space;

	space = set_space(line, &start, "(");
	init_token(token, ft_strndup(&line[start], end - 1), ")", space);
	return (EXIT_SUCCESS);
}

int	check_subshell(t_token **token, char *line, int *pos, int end)
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
		return(error_msg(SYNTAX, 2, error_normalization("(")));
	size = tmp - *pos - 1;
	metacharacters_sub(token, line, *pos + 1, size);
	*pos = tmp;
	return (EXIT_SUCCESS);
}

int	metacharacters(t_token **token, char *line, char *del, int *pos)
{
	int		end;
	int		len;
	int		space;
	char	delimiter[2];

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
	init_token(token, ft_strndup(&line[*pos], end), del, space);
	(*pos) += end;
	if (del[0] != ' ' && line[*pos] == del[0])
		++(*pos);
	return (EXIT_SUCCESS);
}

int	not_metacharacters(t_token **token, char *line, char *del, int *pos)
{
	int	end;
	int	space;

	end = get_end_not_metacharacters(&line[*pos]);
	space = set_space(line, pos, del);
	init_token(token, ft_strndup(&line[*pos], end), del, space);
	(*pos) += end;
	return (EXIT_SUCCESS);
}
