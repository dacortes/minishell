/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacortes <dacortes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/30 10:52:19 by dacortes          #+#    #+#             */
/*   Updated: 2023/07/30 11:28:26 by dacortes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../inc/shell_mini.h"

int	ft_is_space(int c)
{
	if (c && (c == ' ' || (c >= 9 && c <= 13)))
		return (TRUE);
	return (FALSE);
}

int	ignore_sp(char *str)
{
	int i;

	i = 0;
	if (!str)
		return (ERROR);
	while (str[i] && ft_is_space(str[i]))
		i++;
	return (i);
}
