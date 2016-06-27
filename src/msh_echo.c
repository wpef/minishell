#include "minishell.h"

int	msh_echo(char **cmd, t_env **env_list)
{
	int	i;

	if (!env_list)
		return (-1);
	if (!cmd[1])
	{
		ft_putendl("");
		return (1);
	}
	i = 1;
	while (cmd[i])
	{
		if (cmd[i][0] != '"')
			ft_putstr(cmd[i]);
		return (1);
	}
	return (0);
}
