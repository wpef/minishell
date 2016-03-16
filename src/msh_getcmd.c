/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_getcmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-monc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/15 16:03:53 by fde-monc          #+#    #+#             */
/*   Updated: 2016/03/16 16:06:52 by fde-monc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//TO DO
//put print_tab to lib
//coder getenvpos ==> RENVOIT INDEX DANS char **ENV
//coder getenv ==> sub from (len de arg + 1), jusqua la fin
//coder modifenv ==> modif valeur de (getenvpos(arg));
//montrer le bug a francis

void ft_print_tab(char **tab) //go to lib
{
	int i;

	i = 0;
	while (tab[i] != NULL)
	{
		ft_putendl(tab[i]);
			i++;
	}
}

int	main(int ac, char **av, char **environ)
{
	char *line;
	char **cmd;

	if (ac && av)
	{
		PROMPT;
		line = NULL;
		while (ft_gnl(0, &line) == 1)
		{
			cmd = msh_splitargs(line);
			if (line[0] && msh_checkbuilt(cmd, environ) == -1)
			{ //enlever ces crochets pour le pb d'env
				if (msh_execbin(cmd) == -1)
				{
					ft_sdebug("minishell: command not found: %", cmd[0]);
					exit(EXIT_SUCCESS);
				}
			} //idem
			free(line);
			PROMPT;
		}
		return(0);
	}
	return (-1);
}

int	msh_execbin(char **cmd)
{
	char	*path;
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		path = ft_strjoin("/bin/", cmd[0]);
		return(execv(path, cmd));
	}
	else
		wait (&pid);
	return(1);
}

int msh_checkbuilt(char **cmd, char **environ)
{
	if (ft_strcmp(cmd[0], "exit") == 0)
		exit(EXIT_SUCCESS);
	if (ft_strcmp(cmd[0], "env") == 0)
	{
		ft_print_tab(environ);
		return (0);
	}
	else if (ft_strcmp(cmd[0], "cd") == 0)
	{
		msh_chdir(cmd, environ);
		return(0);
	}
	else if (ft_strcmp(cmd[0], "setenv") == 0)
	{
		msh_setenv(environ, cmd);
		return(0);
	}
	//debug
	else if (ft_strcmp(cmd[0], "getenv") == 0)
	{
		msh_getenv(environ, cmd[1]);
		return(0);
	}
	//EOdebug
	else if (ft_strcmp(cmd[0], "unsetenv") == 0)
		return(0);
	return (-1);
}
