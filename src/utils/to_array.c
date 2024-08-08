/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   to_array.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 16:35:42 by frankgar          #+#    #+#             */
/*   Updated: 2024/08/08 08:27:13 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include<minishell.h> 

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
		if (token->type == ARG && !next->has_space && next->type == ARG)
			cast = cast->next;
		else
			break ;
	}
	if (cast)
	{
		token = cast->data.token;
		if (token->type == ARG)
			(*ptr)++;
		node = cast;
	}
	return (token->type == PIPE || token->type == AND
		|| token->type == OR || token->type == S_SHELL);
}

char **add_array(t_basic *iter, int count)
{
    char	**array;
	char	*temp;
    t_token	*curr;
    t_token	*next;
    int		i;

    array = protected(ft_calloc(count + 1, sizeof(char *)), "add_array: array");
    i = 0;
    while (iter)
    {
        curr = iter->data.token;
        if (curr->type == ARG)
        {
            array[i] = protected(ft_strdup(curr->content), "add_array: array");
            while (iter->next && iter->next->data.token->type == ARG
				&& !iter->next->data.token->has_space)
            {
                iter = iter->next;
                next = iter->data.token;
                temp = array[i];
                array[i] = protected(ft_strjoin(temp, next->content), "array");
                free(temp);
            }
            i++;
        }
        if (curr->type == PIPE || curr->type == AND
			|| curr->type == OR || curr->type == S_SHELL) // el end que nos pasa frank
            break;
        iter = iter->next;
    }
    return (array);
}

char	**to_array(t_minishell *mini)
{
	char	**array;
	int		count;

	count = 0;
	bool_loop_void(mini->token, count_arg, &count);
	ft_printf("count [%d]\n", count);
	array = add_array(mini->token, count);
	int i = 0;
	while (array[i])
	{
		ft_printf("*%s*\n", array[i]);
		free(array[i++]);
	}
	free(array);
	array = NULL;
	return (array);
}
