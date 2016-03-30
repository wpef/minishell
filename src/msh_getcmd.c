/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_getcmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-monc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/15 16:03:53 by fde-monc          #+#    #+#             */
/*   Updated: 2016/03/22 00:40:36 by fde-monc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av, char **env)
{
	char *line;
	t_env *env_list;
	char **cmd;
	int i;

	i = 0;
	line = NULL;
	env_list = NULL;
	while (env[i] != NULL)
	{
		if (env[i][0] != '\0') //degueu
			msh_makeenv(env[i], &env_list);
		i++;
	}
	if (ac && av)
	{
		PROMPT;
		while (ft_gnl(0, &line) == 1)
		{
			cmd = msh_splitargs(line);
			msh_getcmd(cmd, &env_list);
			PROMPT;
			free(line);
		}
		return (0);
	}
	return (-1);
}

void	msh_getcmd(char **cmd, t_env **env_list)
{
	int i;

	i = 0;
	if (msh_checkbuilt(cmd, env_list) == -1)
	{
		if (msh_exec(cmd, env_list) == -1)
			ft_sdebug("minishell: command not found: %", cmd[0]);
	}
}

int msh_checkbuilt(char **cmd, t_env **env_list)
{
	int i;
	if (ft_strcmp(cmd[0], "exit") == 0)
	{
		exit(EXIT_SUCCESS);
		return (0);
	}
	if (ft_strcmp(cmd[0], "env") == 0)
	{
		msh_env(cmd, *env_list);
		return (0);
	}
	else if (ft_strcmp(cmd[0], "cd") == 0)
	{
		msh_chdir(cmd, env_list);
		return (0);
	}
	else if (ft_strcmp(cmd[0], "setenv") == 0)
	{
		msh_setenv(cmd[1], cmd[2], env_list);
		return (0);
	}
	//debug
	else if (ft_strcmp(cmd[0], "unsetenv") == 0)
	{
		i = 1;
		if (cmd[i] == NULL)
		{
			msh_error("few", "unsetenv");
			return (0);
		}
		while (cmd[i] != NULL && cmd[i][0] != '\0')
		{
			msh_unsetenv(cmd[i], env_list);
			i++;
		}
		return (0);
	}
	//EOdebug
	else if (ft_strcmp(cmd[0], "unsetenv") == 0)
		return (0);
	return (-1);
}

void	msh_makeenv(char *envi, t_env **env)
{
	t_env *curs;
	t_env *ptr;
	int split;

	split = ft_charindex(envi, '=');
	curs = *env;
	//maillon creer;
	ptr = malloc(sizeof(t_env));
	ptr->var = ft_strsub(envi, 0, split);
	ptr->val = ft_strsub(envi, split + 1, ft_strlen(envi));
	ptr->next = NULL;
	//parcours chaine
	if (*env == NULL)
	{
		*env = ptr;
		return;
	}
	while (curs->next != NULL)
		curs = curs->next;
	//place maillon;
	curs->next = ptr;
}
