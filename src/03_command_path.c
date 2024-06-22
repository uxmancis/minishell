/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   03_command_path.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbonilla <dbonilla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 18:00:19 by dbonilla          #+#    #+#             */
/*   Updated: 2024/06/22 19:08:03 by dbonilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	*ft_lst_to_str(t_vars *tmp)
{
	char	*str;
	int		i;
	int		j;

	if (*(tmp->name) == '\0')
		return (NULL);
	str = (char *)malloc(ft_strlen(tmp->name) + ft_strlen(tmp->val) + 2);
	if (str == NULL)
	{
		return (NULL);
	}
	i = 0;
	j = 0;
	while (*(tmp->name + j))
		*(str + i++) = *(tmp->name + j++);
	*(str + i++) = '=';
	j = 0;
	while (*(tmp->val + j) && *(tmp->val + j) != '\0')
		*(str + i++) = *(tmp->val + j++);
	*(str + i++) = '\0';
	return (str);
}

int	ft_vars_size(t_prompt *data)
{
	t_vars	*tmp;
	int		i;

	i = 0;
	tmp = data->vars;
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	}
	return (i);
}

char	**ft_init_get_path(int *i, char **path, t_prompt *data)
{
	t_vars	*path_env;
	char	**path_tab;

	*path = NULL;
	path_env = ft_getenv_local(data->vars, "PATH");
	if (path_env == NULL)
	{
		return (NULL);
	}
	path_tab = ft_split(path_env->val, ':');
	*i = 0;
	return (path_tab);
}

char	*ft_get_path(char *cmd, t_prompt *data)
{
	int		i;
	char	**path_tab;
	char	*path;
	char	*aux;

	i = 0;
	path_tab = ft_init_get_path(&i, &path, data);
	if (path_tab == NULL)
		return (NULL);
	while (*(path_tab + i))
	{
		aux = ft_strjoin(*(path_tab + i), "/");
		path = ft_strjoin(aux, cmd);
		free(aux);
		free(*(path_tab + i++));
		if (access(path, F_OK) == 0)
			break ;
		free(path);
		path = NULL;
	}
	while (*(path_tab + i))
		free(*(path_tab + i++));
	free(path_tab);
	return (path);
}


