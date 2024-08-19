/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacortes <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 18:20:09 by dacortes          #+#    #+#             */
/*   Updated: 2024/08/19 18:54:28 by dacortes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h> 

int	count_arg(void *node, void *count)
{
	t_token	*tmp;
	t_token	*next;
	t_basic	*cast;
	int		*ptr;

	cast = (t_basic *)node;
	ptr = (int *)count;
	while (cast && cast->next)
	{
		tmp = cast->data.token;
		next = cast->next->data.token;
		if ((tmp->type == ARG || tmp->type == EXPAN)
			&& !next->has_space && next->type == ARG)
			cast = cast->next;
		else
			break ;
	}
	if (cast)
	{
		tmp = cast->data.token;
		if (tmp->type & EXPAN)
			(*ptr)++;
		node = cast;
	}
	return (tmp->type == PIPE || tmp->type & L_OPERAND || tmp->type == S_SHELL);
}

void	add_item_array(t_basic **start, t_token *next, char **tmp)
{
	
}


char	**add_array(t_basic *start, t_basic *end, int count)
{
	char	**array;
	char	*temp;
	t_token	*curr;
	t_token	*next;
	int		i;

	array = protected(ft_calloc(count + 1, sizeof(char *)), "add_array: array");
	i = 0;
	while (start)
	{
		curr = start->data.token;
		if (curr->type & ARG && (!start->prev
				|| !(start->prev->data.token->type & REDIR)))
		{
			array[i] = protected(ft_strdup(curr->content), "add_array: array");
			while (start->next && (start->next->data.token->type == ARG
					|| start->next->data.token->type == EXPAN)
				&& !start->next->data.token->has_space)
			{
				start = start->next;
				next = start->data.token;
				temp = array[i];
				array[i] = protected(ft_strjoin(temp, next->content), "array");
				free(temp);
			}
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
