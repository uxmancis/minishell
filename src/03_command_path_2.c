/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   03_command_path_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbonilla <dbonilla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/22 19:02:19 by dbonilla          #+#    #+#             */
/*   Updated: 2024/06/22 19:11:57 by dbonilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	**ft_gen_envp(t_prompt *data)
{
	t_vars	*tmp;
	int		i;
	int		len;
	char	**custom_envp;

	len = ft_vars_size(data);
	custom_envp = (char **)malloc(sizeof(char *) * (len + 1));
	if (custom_envp == NULL)
		return (NULL);
	i = 0;
	tmp = data->vars;
	while (tmp)
	{
		*(custom_envp + i) = ft_lst_to_str(tmp);
		i++;
		tmp = tmp->next;
	}
	*(custom_envp + i) = NULL;
	return (custom_envp);
}

int	execute_command(t_box **box)
{
	if (execve((*box)->cmd_path, (*box)->rest_info_potential_cmd,
			(*box)->envp) == -1)
	{
		perror("execve");
		exit(127);
	}
	return (0);
}

char	*determine_command_path(t_box **box, t_prompt *data)
{
	int	exit_code;

	(void)exit_code;
	// CHANGED hemos cambiado esto, cuando el input es una ruta abs ejecutable
	if (access((*box)->rest_info_potential_cmd[0], X_OK) == 0)
		(*box)->cmd_path = ft_strdup((*box)->rest_info_potential_cmd[0]);
	else
		(*box)->cmd_path = ft_get_path((*box)->rest_info_potential_cmd[0], \
				data);
	if ((*box)->cmd_path == NULL)
	{
		return (NULL);
	}
	return ((*box)->cmd_path);
}

char	**split_command(t_box **box)
{
	if ((*box)->rest_info_potential_cmd[0] == NULL)
	{
		return (NULL);
	}
	(*box)->command = ft_split((*box)->rest_info_potential_cmd[0], ' ');
	if ((*box)->command == NULL)
	{
		perror("Failed to split command");
	}
	return ((*box)->command);
}

int	ft_run_command(t_box **box, t_prompt *data)
{
	int		exit_code;
	char	*tmp;
	char	*tmp2;

	tmp = "/";
	tmp2 = ".";
	(*box)->command = split_command(box);
	if ((*box)->command == NULL)
		return (-1);
	if ((*box)->command[0] == tmp || (*box)->command[0] == tmp2)
	{
		(*box)->cmd_path = (*box)->command[0];
		(*box)->cmd_path++;
	}
	else
		(*box)->cmd_path = determine_command_path(box, data);
	if ((*box)->cmd_path == NULL || execute_command(box) == -1)
		exit_code = -1;
	cleanup_command((*box)->command);
	if (exit_code == -1)
	{
		exit(127);
		free((*box)->cmd_path);
	}
	return (exit_code);
}
