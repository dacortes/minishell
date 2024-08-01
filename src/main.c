/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 16:35:42 by frankgar          #+#    #+#             */
/*   Updated: 2024/08/01 10:55:15 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <minishell.h>

char	*printf_type(int type)
{
	char	*result;

	result = "no type";
	if (type == OR)
		result = "OR";
	else if (type == AND)
		result = "AND";
	else if (type == ARG)
		result = "arg";
	else if (type == PIPE)
		result = "PIPE";
	else if (type == R_IN)
		result = "Redirection in";
	else if (type == R_OUT)
		result = "Redirection out";
	else if (type == R_APP)
		result = "Redirection append";
	else if (type == R_HER)
		result = "Redirection her doc";
	else if (type == EXPAN)
		result = "Expansion";
	else if (type == S_SHELL)
		result = "Sub shell";
	else if (type == WILD_CARD)
		result = "Wild card";
	return (result);
}

void	printf_content_token(void *content)
{
	char			*quote;
	t_token			*token;
	t_token			*prev_token;
	t_basic_list	*prev;

	token = ((t_basic_list *)content)->list_content.token;
	prev = ((t_basic_list *)content)->prev;
	quote = BLUE"false"END;
	ft_printf("%s%s%s\n", TUR"Content: *"END, token->content, TUR"*"END);
	if (token->is_quote == SIMP_QUOTES || token->is_quote == DOUBLE_QUOTES)
	{
		ft_printf("%s\n", TUR" Type quote: "END, token->is_quote);
		quote = BLUE"true"END;
	}
	ft_printf("%s%s\n", TUR" Is quote: "END, quote);
	ft_printf("%s%d\n", TUR" Has space: "END, token->has_space);
	ft_printf("%s%s\n", TUR" Type: "END, printf_type(token->type));
	if (prev)
	{
		prev_token = ((t_basic_list *)content)->prev->list_content.token;
		if (prev_token)
			ft_printf("%s%s\n", TUR" PREV: "END, prev_token->content);
	}
}

void	printf_token(t_basic_list *token)
{
	ft_printf("%s\n", ORANGE"Print Tokens"END);
	iter_list_list_content(token, printf_content_token);
}


int	iter_list_list_content(t_basic_list *node, void (*f)(void *))
{
	t_basic_list	*iter;


	if (!node)
		return (EXIT_SUCCESS);
	iter = node;
	while(iter)
	{
		f(&(iter->list_content));
		iter = iter->next;
	}
	return (EXIT_SUCCESS);
}

int	mini_rush_plus(int argc, char **argv, char **env)
{
	t_minishell	mini;
	
	(void)argc;
	(void)argv;

	ft_bzero(&mini, sizeof(t_minishell));
	mini.env = init_env(env);
	_env(mini.env, 1);
	while ("The stupid evaluator is testing")
	{
		mini.get_line = readline("patata: ");
		parsing(&mini);
		printf_token(mini.token);
		if (mini.get_line && *mini.get_line)
			add_history(mini.get_line);
		if (!mini.get_line)
			break ;
		if (mini.get_line)
		{
			// free_list(mini.token, free_token);
			free(mini.get_line);
			mini.get_line = NULL;
		}
	}
	free_minishell(&mini, FALSE);
	return (EXIT_SUCCESS);
}

int main(int argc, char **argv, char **env)
{
	return mini_rush_plus(argc, argv, env);
}