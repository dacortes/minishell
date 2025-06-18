/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacortes <dacortes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 16:35:42 by frankgar          #+#    #+#             */
/*   Updated: 2024/08/20 15:38:24 by frankgar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h> 

int	count_arg(void *node, void *count)
{
	t_token	*token;
	t_token	*next;
	t_basic	*cast;
	int		*ptr;

	cast = (t_basic *)node;
	ptr = (int *)count;
	while (cast && cast->next)
	{
		token = cast->data.token;
		next = cast->next->data.token;
		if ((token->type == ARG || token->type == EXPAN)
			&& !next->has_space && next->type == ARG)
			cast = cast->next;
		else
			break ;
	}
	if (cast)
	{
		token = cast->data.token;
		if (token->type & EXPAN)
			(*ptr)++;
		node = cast;
	}
	return (token->type & (PIPE | L_OPERAND | S_SHELL));
}

void	add_to_array(t_basic **start, char ***array, int i)
{
	char	*temp;
	t_token	*next;

	*start = (*start)->next;
	next = (*start)->data.token;
	temp = *array[i];
	*array[i] = protected(ft_strjoin(temp, next->content), "array");
	free(temp);
}

char	**add_array(t_basic *start, t_basic *end, int count)
{
	char	**array;
	t_token	*curr;
	int		i;

	array = protected(ft_calloc(count + 1, sizeof(char *)), "add_array: array");
	i = 0;
	while (start)
	{
		curr = start->data.token;
		if (curr->type & ARG
			&& (!start->prev || !(start->prev->data.token->type & REDIR)))
		{
			array[i] = protected(ft_strdup(curr->content), "add_array: array");
			while (start->next && (start->next->data.token->type == ARG
					|| start->next->data.token->type == EXPAN)
				&& !start->next->data.token->has_space)
				add_to_array(&start, &array, i);
			i++;
		}
		if (start == end)
			break ;
		start = start->next;
	}
	return (array);
}

char	**get_cmds(t_basic *start, t_basic *end)
{
	char	**array;
	int		count;

	count = 0;
	bool_loop_void(start, count_arg, &count);
	array = add_array(start, end, count);
	if (array && !*array)
	{
		free_double_ptr(array);
		return (NULL);
	}
	return (array);
}
