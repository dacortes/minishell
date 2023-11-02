/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_mini.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacortes <dacortes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 11:34:53 by dacortes          #+#    #+#             */
/*   Updated: 2023/11/02 11:13:01 by dacortes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELL_MINI_H
# define SHELL_MINI_H

/******************************************************************************/
/*                            INCLUDES                                        */
/******************************************************************************/

# include "../lib/libft/libft.h"
# include "../lib/libft/ft_printf.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <stdio.h>
# include <limits.h>
# include <errno.h>

/******************************************************************************/
/*                            MACROS                                          */
/******************************************************************************/

/* Utils */
# define FTH	0
# define CHD	1
# define INP	0
# define OUT	1
# define DQU	34
# define QUO	39
# define NOT	"\0"
/* Outputs */
# define SUCCESS 0
# define FALSE	 0
# define TRUE	 1
# define ERROR 	-1
# define E_EXIT  1
/* tokens types */
# define T_CMD 0
# define T_EXP 1
# define T_TXT 2
/* standard input ouput */
# define T_SIR 3
# define T_SOR 4
# define T_RDHD 5
# define T_RDAP 6
/* file descriptor */
# define T_FD 7
/* Inputs */
# define KEY 1
# define VAL 2
/* Error */
# define E_ISD -3
# define E_SPC -2
# define E_ARG 1
# define E_MEM 2
# define E_NSF 3
# define E_PRR 4
# define E_PNF 5
# define E_EXP 6
# define E_BADINT 7
# define E_PRM 126 
# define E_CNF 127
# define E_SNT 258
# define EX 255

/******************************************************************************/
/*                            COLORS                                          */
/******************************************************************************/

# define E "\033[m"        //end
# define R "\033[1;31m"    //red
# define G "\033[1;32m"    //green
# define Y "\033[1;33m"    //yellow
# define B "\033[1;34m"    //blue
# define T "\033[1;35m"	   //Turquesa
# define C "\033[1;36m"    //Cyan
# define O "\033[38;5;208m" //orange
# define F "\033[38;5;128m"  //purple

/******************************************************************************/
/*                            STRUCTURES                                      */
/******************************************************************************/

typedef struct s_aux
{
	int		i;
	int		j;
	int		k;
	int		c;
	int		key;
	int		val;
	int		eql;
	int		in_qu;
	char	*e;
	char	*tmp;
	char	*_key;
	char	*_val;
	char	**arr;
}	t_aux;

/* 
	************ Token arrays ***************
	type[0] = is_quotes, type[1] = is_expand
	type[2] = num_space, type[3] = type_rdct
*/
typedef struct s_token
{
	int				type[4];
	char			*arg;
	struct s_token	*next;
}	t_token;

/* line to pipe */
typedef struct s_line
{
	char			*line;
	t_token			*tk;
	struct s_line	*next;
}	t_line;

typedef struct s_get
{
	char			**arg;
	int				fd[2];
	int				tb[2];
	struct s_get	*next;
}	t_get;

typedef struct s_exe
{
	int		stt;
	int		pipe;
	char	*inp;
	char	*cmd;
	char	*arg;
	char	**env;
	char	**pth;
}	t_exe;

typedef struct s_env
{
	char			*key;
	char			*val;
	int				eql;
	struct s_env	*next;
}	t_env;

typedef struct s_mini
{
	int		size;
	char	*user;
	char	*old;
	char	*dir;
	t_env	*env;
}	t_mini;

/******************************************************************************/
/*                            FUNCTIONS                                       */
/******************************************************************************/

/* src/built-ins/cd.c */
int		cd(char *path, t_mini **sh);
int		ft_cd(t_mini **sh, t_get *g, int n_cmd);
/* src/built-ins/echo.c */
int		ft_echo(char **argv, int argc);
/* src/built-ins/env.c */
char	**env_to_array(t_mini *sh);
int		_env(t_env *env, int n_cmd);
int		init_env(t_mini *sh, char **env);
int		add_key(t_mini *sh, char *key, char *val, int eql);
/* src/built-ins/execute.c */
int		is_built_ins(t_line **ln, t_get **g);
int		exe_built_ins(t_mini **sh, t_line **ln, t_get **g, int *chk);
/* src/built-ins/exit.c */
int		ft_exit(t_mini *sh, t_line **ln, t_get **g, int n_cmd);
/* src/built-ins/export.c */
void	show_export(t_env *env);
int		_export(t_mini *sh, char *inp);
/* src/built-ins/pwd.c */
int		pwd(void);
/* src/built-ins/unset.c*/
int		unset(int *size, t_env **env, char *key);

/* src/execute/clear */
int		clear(t_mini *sh);
int		is_null(t_mini **sh, t_line **ln, t_get **g, char *inp);
int		clear_cmd(t_exe *ex, int stt);
int		clear_pross(t_line **ln, t_get **g, t_exe ex);
/* src/execute/no_pipe.c */
int		no_pipe(t_mini **sh, t_line **ln, t_get **g, t_exe *ex);
/* src/execute/pipe.c */
int		create_childs(t_mini **sh, t_line **ln, t_get **g, t_exe *ex);
/* src/execute/redirection.c */
int		rdc_stdinp(t_get **g, int mode);
int		rdc_stdout(t_get **g, int mode);

/* src/get/get_path.c */
int		get_path(t_exe *ex, t_get *g, char *path);
/* scr/get/get.c */
int		clear_get(t_get **g);
/* src/get/heredoc.c */
int		is_heredoc(t_token **tk, int *fd, int *stt);
int		add_get(t_get **g, char **arg, int len, int *fd);
int		get_init(t_line **ln, t_get **g, int *stt);
/* src/get/type_rdc.c */
int		open_rdc(t_token **tk, int *fd, int *stt); // test
/* src/get/utils.c*/
int		clear_dptr(void **ptr);
int		len_no_rd(t_token *tk);
void	show_arg(t_get *g);
void	get_add_back(t_get **g, t_get *new);
/* src/get/utils2.c */
int		count_tk(t_token *tk);
int		is_bin(t_exe *ex);

/* src/parse/analize.c */
int		identify(t_token **tk);
int		analize_space(char *inp, int count);
int		error_unexpected(int rep, char cut, char **fr);
int		type_expand(char *inp, t_aux *a, t_token **tk, int type);
/* src/parse/copy.c */
int		copy_unquo(char	*inp, t_aux *a, t_token **tk);
int		copy_redic(char *inp, t_aux *a, t_token **tk, char rdc);
int		copy_quotes(char *inp, t_aux *a, t_token **tk, t_env *env);
/* src/parse/expand_tk */
int		expand_tk(t_token **tk, t_env *env);
/* src/parse/line.c */
int		ft_line(char *inp, t_line **ln, t_env *env, int *pipe);
/*  src/parse/parse.c */
int		parse(t_line **ln);
/* src/parse/token.c test */
void	show_tokens(t_line *ln);
int		clear_tk(t_token **tk);
int		add_token(t_token **tk, char *arg, int *type, int *count);
/* src/parse/utils.c */
int		clear_ln(t_line **ln);
int		add_line(t_line **ln, t_token *tk, char	*line);
/* */
int		clear(t_mini *sh);
int		msg_error(int e, int exit_, char *cm);
/* src/utils.c */
char	*search_env(t_env *env, char *key, int type);
char	*ft_strdup_exit(const char *s1);
char	*ft_strrep(const char *inp, size_t start, size_t end, char *rep);
char	*ft_strndup(const char *src, size_t n);
char	*ft_strjoin_max(char **need);
#endif