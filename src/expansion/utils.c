/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 12:57:10 by codespace         #+#    #+#             */
/*   Updated: 2024/08/09 10:20:22 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int is_space(char c)
{
	 return ((c >= 9 && c <= 13 )|| c == ' ');
}

int	get_end_space(char *str)
{
	int	pos;

	pos = 0;
	if (!str)
		return (pos);
	while (str[pos] && !is_space(str[pos]))
		pos++;
	return (pos);
}

int	split_space(t_basic **token, char *line, char *del, int *pos)
{
	int	end;
	int	space;

	end = get_end_space(&line[*pos]);
	space = set_space(line, pos, del);
	init_token(token, ft_strndup(&line[*pos], end), del, space);
	(*pos) += end;
	return (EXIT_SUCCESS);
}

int	search_node(void *src, void *node)
{
	return (src == node);
}
