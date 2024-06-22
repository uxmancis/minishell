/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   06_cd_bulting.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbonilla <dbonilla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 13:32:13 by dbonilla          #+#    #+#             */
/*   Updated: 2024/06/22 13:20:14 by dbonilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	ft_check_dir_permission(char *path)
{
	if (access(path, F_OK) == -1)
		return (!printf("cd: Directory does not exist\n"));
	if (access(path, R_OK) == -1)
		return (!printf("cd: Access denied\n"));
	return (1);
}

static char	*ft_rel_path(char *current, char *new)
{
	char	*pre_rel_path;
	char	*rel_path;

	pre_rel_path = ft_strjoin(current, "/");
	rel_path = ft_strjoin(pre_rel_path, new);
	pre_rel_path = ft_free_null(pre_rel_path);
	return (ft_route_parser(rel_path));
}

static int	ft_absolute_path(t_prompt **data, char **cmd)
{
	int	flag;

	flag = 0;
	flag = ft_check_dir_permission(cmd[1]);
	if (flag)
		ft_set_pwd(data, cmd[1]);
	return (flag);
}

static int	ft_cd_builtin_2(t_prompt **data, char **cmd)
{
	int		flag;
	char	*rel_path;

	flag = 0;
	if (!cmd[1])
	{
		if (!ft_getenv_local((*data)->vars, "HOME")
			|| !ft_check_dir_permission \
			(ft_getenv_local((*data)->vars, "HOME")->val))
			return (!printf("cd: Home not defined\n"));
		ft_set_pwd(data, ft_getenv_local((*data)->vars, "HOME")->val);
		flag = 1;
	}
	else if (cmd[1][0] == '/')
		flag = ft_absolute_path(data, cmd);
	else if (cmd[1][0] != '/')
	{
		rel_path = ft_rel_path \
			(ft_getenv_local((*data)->vars, "PWD")->val, cmd[1]);
		flag = ft_check_dir_permission(rel_path);
		if (flag)
			ft_set_pwd(data, rel_path);
		free(rel_path);
	}
	return (flag);
}

// Implement cd builtin
int	ft_cd_builtin(t_prompt **data, char **cmd)
{
	int		status;
	char	*rel_path;

	rel_path = getcwd(NULL, 0);
	if (ft_getenv_local((*data)->vars, "PWD") == NULL)
		ft_setenv_local((*data)->vars, "PWD", rel_path, 1);
	if (cmd[1] && cmd[2])
		return (!printf("cd: Too many arguments\n"));
	status = ft_cd_builtin_2(data, cmd);
	free(rel_path);
	chdir(ft_getenv_local((*data)->vars, "PWD")->val);
	return (!status);
}
