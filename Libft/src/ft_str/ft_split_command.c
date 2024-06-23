/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_command.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbonilla <dbonilla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 16:23:08 by codespace         #+#    #+#             */
/*   Updated: 2024/06/19 02:02:30 by dbonilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"


static size_t	get_tab_size(const char *s, char c)
{
	size_t	cnt;

	cnt = 0;
	while (*s && s++)
	{
		while (*s != c && *s)
		s++;
		cnt++;
		while (*s == c && *s)
		s++;
	}
	return (cnt);
}

static int	fill_tab(char const *s, char c, char **tab)
{
	size_t	i;
	size_t	len;

	i = 0;
	while (s[i])
	{
		len = 0;
		while (s[i] != c && s[i] && ++s)
		len++;
		tab[i] = malloc(len + 1);
		if (!tab[i])
		{
			while (i)
				free(tab[--i]);
			free(tab);
			return (1);
		}
		ft_strlcpy(tab[i++], s - len, len + 1);
		while (s[i] == c && s[i])
		i++;
	}
	tab[i] = 0;
	return (0);
}

char	**ft_split_command(const char *s, char c)
{
	char	**tab;

	if (!s)
		return (NULL);
	while (*s == c && *s)
		s++;
	tab = (char **)malloc(sizeof(char *) * (get_tab_size(s, c) + 1));
	if (!tab)
		return (NULL);
	if (fill_tab(s, c, tab))
		return (NULL);
	return (tab);
}