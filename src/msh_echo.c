#include "minishell.h"

int	msh_echo(char **cmd, t_env **env_list)
{
	char	*line;

	if (!env_list)
		return (-1);
	if (!cmd[1])
	{
		ft_putendl("");
		return (1);
	}
	line = echo_makeline(cmd);
	echo_getstring(line);
	return (0);
}

char *echo_makeline(char **cmd) //CHECKED OK
{
	int		i;
	char	*ret;
	char	*ret2;

	ret = ft_strdup(cmd[1]);
	i = 2;
	while (cmd[i])
	{
		ret2 = ft_strdup(ret);
		free(ret);
		ret = ft_joinjoin(ret2, " ", cmd[i]);
		free(ret2);
		i++;
	}
	return (ret);
}


char	*echo_getstring(char *line)
{
	int	dq;
	int	sq;

	dq = 0;
	sq = 0;
	if ((dq = ft_charindex('"', line)) != -1)
		echo_closequote(line, dq, 0);
	if ((sq = ft_charindex(39, line)) != -1)
		echo_closequote(line, sq, 1);
	return (NULL);
}

int	echo_hasquotes(char **cmd)
{
	int i;
	//int dq;
	//int sq;

	if (cmd)
		i = 1;
	/*
	while (cmd[i])
	{
		if ((dq = ft_charindex(cmd[i], '"')) != -1)
			ft_putstr(echo_getstring(cmd[i], dq));
	}
	*/
	return (1);
}
