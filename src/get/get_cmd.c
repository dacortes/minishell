/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacortes <dacortes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 11:09:06 by dacortes          #+#    #+#             */
/*   Updated: 2023/09/27 14:10:43 by dacortes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/shell_mini.h"

 #include <string.h>
int	search_cmd(t_line **ln, t_get *g)
{
	t_line	*tmp;
	t_token	*tk;
	char	**argv;
	int		num;

	(void)g;
	tmp = *ln;
	num = 0;
	if (!*ln)
		return (SUCCESS);
	while (tmp)
	{
		tk = tmp->tk;
		ft_printf(Y"line\n"E);
		while (tk)
		{
			if ((tk->type[3] >= 3 && tk->type[3] <= 6) || tk->type[3] == T_FD)
				num++;
			tk = tk->next;
		}
		tmp = tmp->next;
	}
	ft_printf("estoy aqui\n");
	tmp = *ln;
	argv = ft_calloc(sizeof(char *), ((*ln)->argc - num));
	if (!argv)
		exit (msg_error(E_MEM, 1, NULL));
	num = 0;
	while (tmp)
	{
		tk = tmp->tk;
		if ((tk->type[3] >= 3 && tk->type[3] <= 6) || tk->type[3] == T_FD)
		{
			if (tmp->next)
				tmp = tmp->next;
		}
		else
			argv[num++] = ft_strdup_exit(tmp->tk->arg);
		tmp = tmp->next;
	}
	num = 0;
	while (argv[num])
	{
		if (argv[num])
			free(argv[num]);
		num++;
	}
	free(argv);
	return (SUCCESS);
}

/*line -- env -- t_get*/
int	get_cmd(t_line **ln, t_env *env, t_get g)
{
	(void)ln;
	(void)env;
	(void)g;
	return (SUCCESS);
}