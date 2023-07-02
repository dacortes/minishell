/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_mini.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacortes <dacortes@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 11:34:53 by dacortes          #+#    #+#             */
/*   Updated: 2023/07/02 13:24:05 by dacortes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELL_MINI_H
# define SHELL_MINI_H

# include "../lib/libft/libft.h"
# include "../lib/libft/ft_printf.h"

// ================================= MACROS ================================= //
/* Outputs */
# define SUCCESS 0
# define FALSE	 0
# define TRUE	 1
# define ERROR 	-1
# define E_EXIT  1

typedef struct s_tokens
{
	int	q2;
	int	q1;
	int	et;
	int	pip;
}	t_tokens;

#endif