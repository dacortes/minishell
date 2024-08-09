/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 16:35:42 by frankgar          #+#    #+#             */
/*   Updated: 2024/08/09 08:31:47 by codespace        ###   ########.fr       */
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
	while (cast->next)
	{
		token = cast->data.token;
		next = cast->next->data.token;
		if ((token->type == ARG || token->type == EXPAN) && !next->has_space && next->type == ARG)
			cast = cast->next;
		else
			break ;
	}
	if (cast)
	{
		token = cast->data.token;
		if (token->type == ARG || token->type == EXPAN)
			(*ptr)++;
		node = cast;
	}
	return (token->type == PIPE || token->type == AND
		|| token->type == OR || token->type == S_SHELL);
}

char **add_array(t_basic *start, t_basic *end, int count)
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
        if (curr->type == ARG || curr->type == EXPAN)
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
            break;
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
	int i = 0;
	while (array[i])	
		ft_printf("[%s]\n", array[i++]);
	return (array); // librerar doble array despues de usarlo
}
