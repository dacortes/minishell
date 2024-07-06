/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minish.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacortes <dacortes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 12:42:35 by dacortes          #+#    #+#             */
/*   Updated: 2024/07/06 11:09:28 by dacortes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <libft.h>
# include <ft_printf.h>
# include <get_next_line.h>


typedef struct s_get_line t_get_line;
typedef struct s_command_lines t_command_lines;
typedef struct s_token t_token;

enum tokens_types
{
    OR,
	ARG,
    AND,
    PIPE,
    R_IN,
    R_OUT,
    R_APP,
    R_HER,
    EXPAN,
    S_SHELL,
};

struct s_get_line
{
    char *read_line;
    char **split_line;
};

struct s_command_lines
{
    short    pre;
    char    *line;
    t_token *token;
};

struct s_token
{
    short type;
	short is_quote;
    char *content;
};

struct s_env // array to array char **
{
	char	*key;
	char	*value;
	short	eql;
};


#endif