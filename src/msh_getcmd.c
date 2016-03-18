/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_getcmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-monc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/15 16:03:53 by fde-monc          #+#    #+#             */
/*   Updated: 2016/03/18 20:55:25 by fde-monc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//TO DO
//put print_tab to lib
//coder getenvpos ==> RENVOIT INDEX DANS char **ENV
//coder getenv ==> sub from (len de arg + 1), jusqua la fin
//coder modifenv ==> modif valeur de (getenvpos(arg));
//montrer le bug a francis

int	main(int ac, char **av, char **env)
{
	char *line;
	char **cmd;
	int i;

	i = 0;
	line = NULL;
	msh_genvinit();
	if (ac && av)
	{
		PROMPT;
		while (ft_gnl(0, &line) == 1)
		{
			cmd = msh_splitargs(line);
			while (env[i] != NULL)
			{
				msh_getenv(env[i]);
				i++;
			}
			if (line[0] && msh_checkbuilt(cmd) == -1)
			{
				return(0);
				/*
				if (msh_execbin(cmd) == -1)
				{
					ft_sdebug("minishell: command not found: %", cmd[0]);
					exit(EXIT_SUCCESS);
				}
				*/
			}
			free(line);
			PROMPT;
		}
		return(0);
	}
	return (-1);
}

void	msh_genvinit(void)
{
	g_env.var = NULL;
	g_env.val= NULL;
	g_env.next = NULL;
}

void	msh_getenv(char *envi)
{
	t_env *curs;
	t_env *ptr;
	int split;

	split = ft_charindex(envi, '=');
	curs = &g_env;
	//maillon creer
	ptr = malloc(sizeof(t_env));
	ptr->var = ft_strsub(envi, 0, split);
	ptr->val = ft_strsub(envi, split + 1, ft_strlen(envi));
	ptr->next = NULL;
	//parcours chaine
	if (g_env.var == NULL)
	{
		g_env = *ptr;
		return;
	}
	while (curs->next != NULL)
		curs = curs->next;
	//place maillon;
	curs->next = ptr;
}

int msh_checkbuilt(char **cmd)
{
	//pour compil
	char **environ = NULL;
	
	if (ft_strcmp(cmd[0], "exit") == 0)
		exit(EXIT_SUCCESS);
	if (ft_strcmp(cmd[0], "env") == 0)
	{
		msh_env(cmd);
		return (0);
	}
	else if (ft_strcmp(cmd[0], "cd") == 0)
	{
		msh_chdir(cmd, environ);
		return(0);
	}
	else if (ft_strcmp(cmd[0], "setenv") == 0)
	{
		//msh_setenv(environ, cmd);
		return(0);
	}
	//debug
	else if (ft_strcmp(cmd[0], "getenv") == 0)
	{
		//msh_getenv(environ, cmd[1]);
		return(0);
	}
	//EOdebug
	else if (ft_strcmp(cmd[0], "unsetenv") == 0)
		return(0);
	return (-1);
}
