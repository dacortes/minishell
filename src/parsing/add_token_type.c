/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_token_type.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacortes <dacortes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 14:28:08 by dacortes          #+#    #+#             */
/*   Updated: 2024/07/20 17:01:16 by dacortes         ###   ########.fr       */
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
	// add_back((void **)token, new, sizeof(t_token));
	add_back((void **)token, new, T_TOKEN);
	return (EXIT_SUCCESS);
}

int	metacharacters(t_token **token, char *line, char *del, int *pos)
{
	int		end;
	int		len;
	int		space;

	space = 0;
	len =  ft_strlen(del);
	if (line[*pos] && del[0] != ' ' && len > 1)
		(*pos)++;
	end = ft_strchrpos(&line[*pos], del[0]);
	if (end == ERROR && del[0] != ' ')
		return (error_msg(SYNTAX, 2, del));
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
