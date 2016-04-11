/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_main.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-monc <fde-monc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/08 16:29:03 by fde-monc          #+#    #+#             */
/*   Updated: 2016/04/11 19:54:36 by fde-monc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		main(int ac, char **av, char **env)
{
	t_env	*env_list;
	int		i;

	i = 0;
	env_list = NULL;
	while (env[i] != NULL)
	{
		if (env[i][0] != '\0')//degueu
			msh_makeenv(env[i], &env_list);
		i++;
	}
	if (ac && av)
	{
		PROMPT;
		msh_readline(&env_list);
	}
	return (0);
}

void	msh_makeenv(char *envi, t_env **env)
{
	t_env	*curs;
	t_env	*ptr;
	int		split;

	split = ft_charindex(envi, '=');
	curs = *env;
	ptr = malloc(sizeof(t_env));
	ptr->var = ft_strsub(envi, 0, split);
	ptr->val = ft_strsub(envi, split + 1, ft_strlen(envi));
	ptr->next = NULL;
	if (*env == NULL)
	{
		*env = ptr;
		return ;
	}
	while (curs->next != NULL)
		curs = curs->next;
	curs->next = ptr;
}

void	msh_readline(t_env **env_list)
{
	char	*line;
	char	**cmd;

	line = NULL;
	while (ft_gnl(0, &line) == 1)
	{
		if (line[0])
		{
			if ((cmd = msh_splitargs(line)) != NULL)
				msh_getcmd(cmd, env_list);
			free(line);
		}
		PROMPT;
	}
}
