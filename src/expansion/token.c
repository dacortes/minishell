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

void	*get_last_expand(t_basic *list)
{
	int	i;

	if (!list)
		return (NULL);
	i = 0;
	while (list->next)
	{
		if (i == 0)
		{
			list->data.token->type = EXPAN;
			list->data.token->expanded = FALSE;
		}
		else
			list->data.token->expanded = TRUE;
		list = list->next;
		i++;
	}
	list->data.token->expanded = TRUE;
	if (i == 0)
	{
		list->data.token->type = EXPAN;
		list->data.token->expanded = FALSE;
	}
	return (list);
}

t_basic	*connect_lists(t_minishell *mini, t_basic *node, t_basic *new, t_basic **init)
{
	t_basic *last;

	(void)init;
	if (mini->token == node)
	{
		mini->token = new;
		*init = new;
	}
	else
	{
		new->prev = node->prev;
		node->prev->next = new;
		new->data.token->has_space = node->data.token->has_space;
		*init = new;
	}
	last = get_last_expand(new);
	if (last)
	{
		last->next = node->next;
		if (last->next)
			node->next->prev = last;
	}
	free(node->data.token->content);
    free(node->data.token);
    free(node);
	return (last);
}

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

t_basic *wordspliting(t_minishell *mini, t_basic *node, t_basic **init)
{
	char	*line;
	int		end;
	int		i;
	t_basic	*new;

	line = protected(ft_strdup(node->data.token->content), "line");
	line = expansion(mini, line);
	end = ft_strlen(line);
	i = 0;
	new = NULL;
	while (i <= end && line[i])
	{
		while (line[i] == ' ')
			i++;
		mini->status = split_space(&new, line, " zz", &i);
	}
	if (line && !*line)
		mini->status = split_space(&new, line, " zz", &i);
	free(line);
	return (connect_lists(mini, node, new, init));
}

int	search_node(void *src, void *node)
{
	return (src == node);
}

int	expand_token(t_minishell *mini, t_basic **start, t_basic *end)
{
	t_token	*token;
	t_basic *init;
	t_basic *iter;
	
	init = NULL;
	iter = *start;
	while (iter != end)
	{
		token = iter->data.token;
		if (token->type == EXPAN && token->is_quote == DOUBLE_QUOTES)
			token->content = expansion(mini, token->content);
		else if (token->type == EXPAN && token->is_quote == FALSE)
			iter = wordspliting(mini, iter, &init);
		if (!iter)
			break ;
		iter = iter->next;
	}
	if (init && init->prev)
		*start = init->prev;
	else
		*start = init;
	return (EXIT_SUCCESS);
}
