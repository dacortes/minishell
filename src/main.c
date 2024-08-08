/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 16:35:42 by frankgar          #+#    #+#             */
/*   Updated: 2024/08/08 08:13:46 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	test_heredoc(t_minishell *mini)
{
	pid_t	redir[2];
	t_basic	*iter;
	t_basic	*env;

	redir[0] = 0;
	redir[1] = 0;
	env = mini->env;
	iter = mini->token;
	while (iter && iter->data.token->type != SYN_ERROR && mini->status == 0)
	{
		is_heredoc(env, iter, redir, &mini->status);
		iter = iter->next;
	}
	return (EXIT_SUCCESS);
}

int	init_mini_rush_plus(t_minishell *mini, char **env)
{
	term_init();
	ft_bzero(mini, sizeof(t_minishell));
	mini->env = init_env(env);
	mini->user = protected(ft_strdup(search_env(mini->env, "USER", VALUE)),
		"init_mini_rush_plus: user");
	if (mini->user && !*mini->user)
	{
		free(mini->user);
		mini->user = ft_strdup("UWU");
	}
	mini->cur_dir = get_pwd();
	mini->old_dir = protected(ft_strdup(search_env(mini->env, "OLDPWD", VALUE)),
		"init_mini_rush_plus: old_dir");
	return (EXIT_SUCCESS);
}


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

int	mini_rush_plus(int argc, char **argv, char **env)
{
	t_minishell	mini;
	
	(void)argc;
	(void)argv;

	init_mini_rush_plus(&mini, env);
	while ("The stupid evaluator is testing")
	{
		signal(SIGINT, _sigint);
		signal(SIGQUIT, SIG_IGN);
		prompt(&mini);
		parsing(&mini);
		test_heredoc(&mini);
		printf_token(mini.token);
		to_array(&mini);
		if (mini.get_line && *mini.get_line)
			add_history(mini.get_line);
		if (!mini.get_line)
			break ;
		if (mini.get_line)
		{
			free_list(mini.token, free_token);
			free(mini.get_line);
			mini.get_line = NULL;
		}
		ft_printf("%s [%d]\n", BLUE"status:"END, mini.status);
	}
	free_minishell(&mini, FALSE);
	return (EXIT_SUCCESS);
}

int main(int argc, char **argv, char **env)
{
	return (mini_rush_plus(argc, argv, env));
}
