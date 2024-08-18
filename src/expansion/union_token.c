/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   union_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacortes <dacortes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 12:57:10 by dacortes          #+#    #+#             */
/*   Updated: 2024/08/18 19:04:25 by frankgar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	funsion_token(t_basic **prev, t_basic *current)
{
	t_token	*cur_token;
	t_token	*pre_token;
	char	*content;

	cur_token = current->data.token;
	pre_token = (*prev)->data.token;
	content = protected(ft_strjoin(pre_token->content, cur_token->content), "");
	ft_free(&(*prev)->data.token->content, NULL);
	(*prev)->data.token->content = content;
	(*prev)->data.token->type = cur_token->type;
	(*prev)->data.token->is_quote = cur_token->is_quote;
}

t_basic	*coppy_token(t_basic *src)
{
	t_basic	*new_node;

	new_node = protected(ft_calloc(sizeof(t_basic), 1), "new_node");
	new_node->data.token = protected
		(ft_calloc(sizeof(t_token), 1), "new_node token");
	new_node->data.token->type = src->data.token->type;
	new_node->data.token->is_quote = src->data.token->is_quote;
	new_node->data.token->has_space = src->data.token->has_space;
	new_node->data.token->content = protected
		(ft_strdup(src->data.token->content), "token content");
	return (new_node);
}

t_basic	*union_token(t_basic *start, t_basic *end)
{
	t_basic	*new_list;
	t_basic	*new_node;
	t_basic	*prev_node;

	new_list = NULL;
	new_node = NULL;
	prev_node = NULL;
	while (start != end)
	{
		if (prev_node && !start->data.token->has_space)
			funsion_token(&prev_node, start);
		else if (start->data.token->type != S_SHELL)
		{
			new_node = coppy_token(start);
			add_back(&new_list, new_node);
			prev_node = new_node;
		}
		start = start->next;
	}
	add_prev(&new_list, TRUE);
	return (new_list);
}
