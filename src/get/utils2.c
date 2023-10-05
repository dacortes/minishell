/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacortes <dacortes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 09:38:12 by dacortes          #+#    #+#             */
/*   Updated: 2023/10/05 09:39:15 by dacortes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/shell_mini.h"

int	count_tk(t_token *tk)
{
	t_token	*iter;
	int		num;

	num = 0;
	if (!tk)
		return (num);
	iter = tk;
	while (iter)
	{
		num++;
		iter = iter->next;
	}
	return (num);
}
