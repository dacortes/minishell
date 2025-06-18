/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacortes <dacortes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 12:57:10 by dacortes          #+#    #+#             */
/*   Updated: 2024/08/19 13:13:37 by frankgar         ###   ########.fr       */
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

t_basic	*connect(t_minishell *mini, t_basic *node, t_basic *new, t_basic **init)
{
	t_basic	*last;

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

t_basic	*wordspliting(t_minishell *mini, t_basic *node, t_basic **init)
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
	return (connect(mini, node, new, init));
}

void	do_wordsplit(t_minishell *mini, t_basic **iter, t_basic **init, \
														t_basic **first)
{
	static short	flag;

	if (!mini)
	{
		flag = FALSE;
		return ;
	}
	*iter = wordspliting(mini, *iter, init);
	if (flag == FALSE)
		*first = *init;
	flag = TRUE;
}

int	expand_token(t_minishell *mini, t_basic **start, t_basic *end)
{
	t_token	*token;
	t_basic	*init;
	t_basic	*iter;
	t_basic	*first;

	init = NULL;
	iter = *start;
	do_wordsplit(NULL, NULL, NULL, NULL);
	while (iter != end)
	{
		token = iter->data.token;
		if (token->type == EXPAN && token->is_quote == DOUBLE_QUOTES)
			token->content = expansion(mini, token->content);
		else if (token->type == EXPAN && token->is_quote == FALSE)
			do_wordsplit(mini, &iter, &init, &first);
		if (!iter)
			break ;
		iter = iter->next;
	}
	if (init && init->prev)
		*start = first;
	else if (init && !init->prev)
		*start = init;
	return (EXIT_SUCCESS);
}
