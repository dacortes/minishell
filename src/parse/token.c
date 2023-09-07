/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacortes <dacortes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 10:56:02 by dacortes          #+#    #+#             */
/*   Updated: 2023/09/07 16:41:16 by dacortes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/shell_mini.h"

/* test */

// int	add_token(t_line **ln, t_token **tk, char *arg, int type)
// {
// 	t_token	*new;

// 	new = ft_calloc(sizeof(t_token), 1);
// 	if (!new)
// 		exit (msg_error(E_MEM, 1, NULL));
// 	new->arg = ft_strdup(arg);
// 	if (!new->arg)
// 		exit (msg_error(E_MEM, 1, NULL));
// 	new->type = type;
// 	new->next = *tk;
// 	*tk = new;
// 	(*ln)->argc++;
// 	return (SUCCESS);
// }

int clear_tk(t_token **tk)
{
	t_token *rm = *tk;
	t_token	*tmp;
	
	while (rm)
	{
        if (rm->arg)
            free(rm->arg);
        tmp = rm;
        rm = rm->next;
        free(tmp);
	}
	*tk = NULL;
	return (SUCCESS);
}

int	add_token(t_token **tk, char *arg, int type, int *count)
{
	t_token *new;

	new = ft_calloc(sizeof(t_token), 1);
	if (!new)
		exit (msg_error(E_MEM, 1, NULL));
	new->arg = ft_strdup(arg);
	if (!new->arg)
		exit (msg_error(E_MEM, 1, NULL));
	new->type = type;
	new->next = NULL;
	if (!(*tk))
		*tk = new;
	else
	{
		new->next = *tk;
		(*tk) = new;
	}
	(*count)++;
	return (SUCCESS);
}
