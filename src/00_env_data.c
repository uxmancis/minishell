/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   00_env_data.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+
	+:+     */
/*   By: uxmancis <uxmancis@student.42urduliz.co    +#+  +:+
	+#+        */
/*                                                +#+#+#+#+#+
	+#+           */
/*   Created: 2024/04/13 10:45:53 by codespace         #+#    #+#             */
/*   Updated: 2024/05/26 12:47:55 by uxmancis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static void	ft_export_all(t_vars *list)
{
	t_vars	*tmp;

	tmp = list;
	while (tmp)
	{
		if (ft_strcmp(tmp->name, "?"))
			tmp->is_exp = 1;
		tmp = tmp->next;
	}
}

int	ft_write_val(t_vars *new, char *value)
{
	if (!value)
		free(new->val);
	if (value)
		new->val = ft_strdup(value);
	return (0);
}

int	ft_setenv_local(t_vars *list, char *name, char *value, int overwrite)
{
	t_vars	*new;

	if (!list)
		return (-1);
	new = ft_getenv_local(list, name);
	if (!new)
	{
		if (value == NULL)
			new = ft_varsnew(ft_strdup(name), ft_strdup(""));
		else
			new = ft_varsnew(ft_strdup(name), ft_strdup(value));
		if (!new)
			return (-1);
		while (list->next)
			list = list->next;
		list->next = new;
		list->is_exp = 0;
		return (0);
	}
	else if (overwrite && ft_strlen(value))
		return (ft_write_val(new, value));
	return (1);
}

void	ft_import_envp(t_prompt *data, char **envp)
{
	int		i;
	int		l;
	char	*name;
	char	*value;
	int		flag;

	i = -1;
	while (*(envp + (++i)))
	{
		l = ft_sstrncmp(*(envp + i), '=');
		if (l != -1 && l != 0)
		{
			name = ft_substr(*(envp + i), 0, l);
			value = ft_substr(*(envp + i), l + 1, ft_strlen(*(envp + i)) - l);
			flag = ft_setenv_local(data->vars, name, value, 0);
			free(name);
			free(value);
			if (flag == -1)
				write(1, "Error: Malloc failed.\n", 22);
		}
	}
	ft_export_all(data->vars);
}
