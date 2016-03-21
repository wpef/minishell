/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_getcmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-monc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/15 16:03:53 by fde-monc          #+#    #+#             */
/*   Updated: 2016/03/21 15:23:57 by fde-monc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av, char **env)
{
	char *line;
	char **cmd;

	line = NULL;
	if (ac && av)
	{
		PROMPT;
		while (ft_gnl(0, &line) == 1)
		{
			cmd = msh_splitargs(line);
			msh_getcmd(cmd, env);
			PROMPT;
			free(line);
		}
		return(0);
	}
	return (-1);
}

void	msh_getcmd(char **cmd, char **env)
{
	t_env *env_list;
	int i;

	i = 0;
	env_list = NULL;
	ft_putendl("+++ IN GET CMD +++");
	while (env[i] != NULL)
	{
		if (env[i][0] != '\0') //degueu
			msh_makeenv(env[i], &env_list);
		i++;
	}
	ft_putendl("env_list created");
	if (msh_checkbuilt(cmd, &env_list) == -1)
	{
		ft_putendl("cmd not a env cmd");
		if (msh_exec(cmd, &env_list) == -1)
			ft_sdebug("minishell: command not found: %", cmd[0]);
	}
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

int msh_checkbuilt(char **cmd, t_env **env_list)
{
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
		return(0);
	}
	else if (ft_strcmp(cmd[0], "setenv") == 0)
	{
		msh_setenv(cmd[1], cmd[2], env_list);
		return(0);
	}
	//debug
	else if (ft_strcmp(cmd[0], "unsetenv") == 0)
	{
		msh_unsetenv(cmd[1], env_list);
		return(0);
	}
	//EOdebug
	else if (ft_strcmp(cmd[0], "unsetenv") == 0)
		return(0);
	return (-1);
}
