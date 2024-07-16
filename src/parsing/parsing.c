/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacortes <dacortes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 12:09:24 by dacortes          #+#    #+#             */
/*   Updated: 2024/07/16 17:40:46 by dacortes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	set_space(char *line, int *pos, char *del)
{
	int	i;
	int	space;

	i = *pos;
	space = 0;
	if (!line || !line[0])
		return (space);
	if (*pos >= 1)
	{
		i -= (del[0] == ' ') * 1;
		i -= (del[0] != ' ') * 2;
		while (i >= 0 && line[i] && (line[i] == ' ' || line[i] == '\t'))
		{
			--i;
			++space;
		}
	}
	return (space);
}

short	get_type(char *flag, char *content)
{
	if (ft_strlen(flag) == 3 && flag[0] != SIMP_QUOTES)
	{
		if (ft_strlen(content) == 1 && content[0] == '|')
			return (PIPE);
		else if (ft_strlen(content) == 1 && content[0] == '<')
			return (R_IN);
		else if (ft_strlen(content) == 1 && content[0] == '>')
			return (R_OUT);
		else if (ft_strlen(content) == 2 && !ft_strncmp("<<", content, 2))
			return (R_HER);
		else if (ft_strlen(content) == 2 && !ft_strncmp(">>", content, 2))
			return (R_APP);
		else if (ft_strlen(content) == 2 && !ft_strncmp("||", content, 2))
			return (OR);
		else if (ft_strlen(content) == 2 && !ft_strncmp("&&", content, 2))
			return(AND);
		else
			return (EXPAN);
	}
	return (ARG);
}

int	init_token(t_token **token, char *content, char *del, int space)
{
	t_token	*new;

	new = ft_calloc(sizeof(t_token), 1);
	if (!new)
		exit (error_msg(MALLOC, 1, "valiable: new"));
	new->content = content;
	if (!new->content)
		exit (EXIT_FAILURE);
	new->is_quote = 0;
	new->is_quote += (del[0] == SIMP_QUOTES) * SIMP_QUOTES;
	new->is_quote += (del[0] == DOUBLE_QUOTES) * DOUBLE_QUOTES;
	new->type = get_type(del, new->content);
	new->has_space = space;
	new->next = NULL;
	add_back((void **)token, new, sizeof(t_token));
	return (EXIT_SUCCESS);
}

int	metacharacters(t_token **token, char *line, char *del, int *pos)
{
	int		end;
	int		space;

	space = 0;
	if (line[*pos] && del[0] != ' ')
		(*pos)++;
	end = ft_strchrpos(&line[*pos], del[0]);
	if (end == ERROR && del[0] != ' ')
		return (error_msg(SYNTAX, 2, del));
	space = set_space(line, pos, del);
	if (end == ERROR)
		end = ft_strlen(&line[*pos]);
	init_token(token, ft_strndup(&line[*pos], end), del, space);
	(*pos) += end;
	if (del[0] != ' ' && line[*pos] == del[0])
		++(*pos);
	return (EXIT_SUCCESS);
}

int	basic_checker(t_token **token, char *line, int end)
{
	int i = 0;
	int	tmp = 0;
	int	status = 0;

	*token = NULL;
	if (!end || !line[0])
		return (EXIT_SUCCESS);
	while (i <= end && line[i])
	{
		while(line[i] == ' ')
			i++;
		if (line[i] == DOUBLE_QUOTES || line[i] == SIMP_QUOTES)
		{
			status = metacharacters(token, line, &line[i], &i);
			if (status)
				return (status);
		}
		else if (line[i] == '&' || line[i] == '|')
		{
			status =  metacharacters(token, line, " &|", &i);
			if (status)
				return (status);
		}
		else if (line[i] == '<' || line[i] == '>')
		{
			status =  metacharacters(token, line, " <>", &i);
			if (status)
				return (status);
		}
		else if (line[i] == '(' || line[i] == ')')
		{
			
			if  (line[i] == ')')
				return (EXIT_FAILURE);
			int count[2] = {1, -2};
			i++;
			tmp = i;
			while (line[tmp] && tmp <= end)
			{
				if (line[tmp] == '(')
					count[0]++;
				else if (line[tmp] == ')')
					count[0]--;
				if(count[0] == 0 && count[1] == -1)
					count[1] =  end - tmp - 1;
				tmp++;
			}
			if (count[0] != 0)
				return(error_msg(SYNTAX, 2, error_normalization("(")));
			if (basic_checker(token, &line[i], count[1]))
				return (2);
			i = tmp;
		}
		else if (line[i])
		{
			status = metacharacters(token, line, " ", &i);
			if (status)
				return (status);
		}
	}
	return (EXIT_SUCCESS);
}

int	check_tokens(t_token **token)
{
	t_token	*iter;

	iter = *token;
	while (iter)
	{
		if (iter->content && ft_strlen(iter->content) == 2)
		{
			ft_printf("soy una patata: %s\n", iter->content);
		}
		iter = iter->next;
	}
	return (EXIT_SUCCESS);
}

int parsing(t_minishell *mini)
{
	char	*line;
	int		len;

	line = mini->get_line.read_line;
	if (!line)
		exit (EXIT_SUCCESS);
	len = ft_strlen(line);
	mini->status = basic_checker(&mini->token, line, len);
	if (mini->status)
		return (mini->status);
	// mini->status = check_tokens(&mini->token);
	printf_token(mini->token);
	return (EXIT_SUCCESS);
}