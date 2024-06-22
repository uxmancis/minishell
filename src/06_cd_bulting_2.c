/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   06_cd_bulting_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbonilla <dbonilla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/22 13:15:34 by dbonilla          #+#    #+#             */
/*   Updated: 2024/06/22 13:17:50 by dbonilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ft_set_pwd(t_prompt **data, char *path)
{
	if (ft_getenv_local((*data)->vars, "PWD") != NULL)
		ft_setenv_local((*data)->vars, "OLDPWD", \
			ft_getenv_local((*data)->vars, "PWD")->val, 1);
	ft_setenv_local((*data)->vars, "PWD", path, 1);
}

char	*ft_route_parser(char *route)
{
	char	**split;
	char	*full_route;
	char	*temp_route;
	int		i;

	i = 0;
	split = ft_split(route, '/');
	while (split[i])
	{
		if (!ft_strcmp(split[i], "."))
			split[i] = ft_free_null(split[i]);
		else if (!ft_strcmp(split[i], ".."))
		{
			split[i] = ft_free_null(split[i]);
			if (i > 0)
				split[i - 1] = ft_free_null(split[i - 1]);
		}
		i++;
	}
	if (!split[0])
		return (free(split), free(route), ft_strdup("/"));
	temp_route = ft_strjoin_arr(split, "/", i);
	full_route = ft_strjoin("/", temp_route);
	return (free(temp_route), free(split), free(route), full_route);
}

char	*ft_strjoin_arr(char **arr, char *del, int length)
{
	char	*str;
	int		i;
	int		len;

	len = 0;
	if (!arr[0])
		return (malloc(1));
	i = -1;
	while (arr[++i])
		len += ft_strlen(arr[i]);
	str = ft_calloc(1, sizeof(char) * (len + (length * 2) + 1));
	i = 0;
	while (length--)
	{
		if (arr[i])
			ft_strcat(str, arr[i]);
		if (arr[i])
			free(arr[i]);
		if (arr[i + 1])
			ft_strcat(str, del);
		i++;
	}
	return (str);
}
