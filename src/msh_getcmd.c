/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_getcmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-monc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/15 16:03:53 by fde-monc          #+#    #+#             */
/*   Updated: 2016/03/15 18:44:59 by fde-monc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(void)
{
	char *line;
	char **cmd;
	
	PROMPT;
	while (ft_gnl(0, &line) == 1)
	{
		cmd = msh_splitargs(line);
		free(line);
		if (ft_strcmp(cmd[0], "exit") == 0)
			exit(EXIT_SUCCESS);
		else if (msh_checkcmd(cmd) == -1)
		{
			ft_sdebug("minishell: command not found: %", cmd[0]);
			exit(EXIT_SUCCESS);
		}
	}
	return (0);
}

int	msh_checkcmd(char **cmd)
{
	//envoyer av[0] dans execv /bin/cmd
	//SI DIFFERENT DES BUILTIN
	if (cmd[0])
		return(msh_execbin(cmd));
	return(0);
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
	PROMPT;
	return(1);
}
