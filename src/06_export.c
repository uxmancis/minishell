/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   06_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbonilla <dbonilla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 21:09:52 by dbonilla          #+#    #+#             */
/*   Updated: 2024/06/22 19:15:35 by dbonilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static char	**ft_trim_str(char *str)
{
	char	**str_arr;
	int		i;
	int		j;

	str_arr = malloc(sizeof(char *) * 2);
	i = 0;
	j = 0;
	str_arr[0] = malloc(sizeof(char) * strlen(str));
	str_arr[1] = malloc(sizeof(char) * strlen(str));
	while (str[i] != '=')
	{
		str_arr[0][i] = str[i];
		i++;
	}
	str_arr[0][i] = '\0';
	i++;
	while (str[i])
	{
		str_arr[1][j] = str[i];
		i++;
		j++;
	}
	str_arr[1][j] = '\0';
	return (str_arr);
}

static int	ft_export_list(t_vars *env)
{
	while (env)
	{
		if (ft_strcmp_2(env->name, "_") && ft_strcmp_2(env->name, "?"))
		{
			if (env->val != NULL)
			{
				printf("declare -x %s=\"%s\"\n", env->name, env->val);
			}
			else
			{
				printf("declare -x %s\n", env->name);
			}
		}
		env = env->next;
	}
	return (0);
}

int	ft_export_builtin(t_prompt *data, char **cmd)
{
	int		i;
	char	**variable;

	i = 0;
	if (ft_strcmp(cmd[0], "export"))
		return (!printf("Undefined error.\n"));
	if (!cmd[1])
		ft_export_list(data->vars);
	// CHANGE cambio asignacion y evaluacion de i en while
	while (cmd[++i])
	{
		if (!ft_strchr(cmd[i], '='))
			continue ;
		else if (ft_strlen(cmd[i]) > 1)
		{
			variable = ft_trim_str(cmd[i]);
			ft_setenv_local(data->vars, variable[0], variable[1], 1);
			free(variable[0]);
			free(variable[1]);
			free(variable);
		}
		else
			return (printf("export: '%s': not valid ident\n", cmd[i]), -1);
	}
	return (0);
}
