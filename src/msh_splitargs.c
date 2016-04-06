/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-monc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/02 12:13:34 by fde-monc          #+#    #+#             */
/*   Updated: 2016/04/06 22:15:36 by fde-monc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_wordscount(char const *s)
{
	int	i;
	int	word;

	i = 0;
	word = 0;
	while (s[i])
	{
		while (s[i] && (s[i] == ' ' || s[i] == '\t'))
			i++;
		if (s[i] && (s[i] != ' ' && s[i] != '\t'))
		{
			word++;
			while (s[i] && (s[i] != ' ' && s[i] != '\t'))
				i++;
		}
	}
	return (word);
}

char		**msh_splitargs(char const *s)
{
	int		i;
	int		strt;
	int		len;
	char	**tab;
	int		words;

	words = ft_wordscount(s);
	i = 0;
	tab = (char **)malloc(sizeof(char*) * (words + 1));
	if (!tab)
	{
		msh_error("", "split_arg : malloc failed");
		return (NULL);
	}
	strt = 0;
	while (i < words)
	{
		while (s[strt] && (s[strt] == ' ' || s[strt] == '\t'))
			strt++;
		len = 0;
		while (s[strt + len] != '\0' && s[strt + len] != ' ' && s[strt + len] != '\t')
			len++;
		tab[i] = ft_strsub(s, strt, len);
		strt = strt + len;
		i++;
	}
	tab[words] = NULL;
	return (tab);
}
