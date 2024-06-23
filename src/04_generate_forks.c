/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   04_generate_forks.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbonilla <dbonilla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 20:53:18 by dbonilla          #+#    #+#             */
/*   Updated: 2024/06/23 19:47:26 by dbonilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static void	pipe_manager(t_prompt *data, t_box *box, int id)
{
	int	fd_out;

	if (box->fd_in >= 3)
		data->fd_aux = box->fd_in;
	else
	{
		if (id == 0)
			data->fd_aux = dup(data->tmp_in);
	}
	fd_out = 0;
	dup2(data->fd_aux, STDIN_FILENO);
	close(data->fd_aux);
	if (id == data->nb_of_pipes)
		fd_out = dup(data->tmp_out);
	else
	{
		pipe(data->pipefd);
		fd_out = data->pipefd[1];
	}
	if (box->fd_out >= 3)
		fd_out = box->fd_out;
	dup2(fd_out, 1);
	close(fd_out);
}

static int	handle_builtin_commands(t_box *box, t_prompt *data)
{
	int	exit_code;

	exit_code = 0;
	if (ft_strcmp_2(box->rest_info_potential_cmd[0], "export"))
	{
		exit_code = ft_export_builtin(data, box->rest_info_potential_cmd);
		ft_free_tab(box->envp);
		free(box->pids);
		box->pids = NULL;
		return (exit_code);
	}
	else if (ft_strcmp_2(box->rest_info_potential_cmd[0], "unset")
		&& box->rest_info_potential_cmd[0] != NULL)
	{
		exit_code = ft_unset_builtin(&data, box->rest_info_potential_cmd);
		ft_free_tab(box->envp);
		free(box->pids);
		box->pids = NULL;
		return (exit_code);
	}
	return (0);
}

static int	handle_builtin_commands_2(t_box *box, t_prompt *data)
{
	int	exit_code;

	exit_code = 0;
	if (ft_strcmp_2(box->rest_info_potential_cmd[0], "cd"))
	{
		exit_code = ft_cd_builtin(&data, box->rest_info_potential_cmd);
		ft_free_tab(box->envp);
		free(box->pids);
		box->pids = NULL;
		return (exit_code);
	}
	else if (ft_strcmp_2(box->rest_info_potential_cmd[0], "exit"))
	{
		if (box->nb_pipes == 0)
			ft_exit_builtin(data, exit_code);
	}
	else if (ft_strcmp_2(box->rest_info_potential_cmd[0], "$?"))
	{
		ft_free_tab(box->envp);
		free(box->pids);
		box->pids = NULL;
		return (exit_code);
	}
	return (0);
}

static int	childs(t_box *box, t_prompt *data)
{
	pid_t	pid;
	int		exit_code;

	pid = fork();
	data->pid = pid;
	exit_code = 0;
	if (pid == -1)
	{
		perror("fork");
		return (-1);
	}
	if (pid == 0)
	{
		if (is_builtin_command(box->rest_info_potential_cmd[0]) == 1
			&& !box->rest_info_potential_cmd)
			exit_code = which_cmd(box, &data);
		else
			exit_code = ft_run_command(&box, data);
		ft_free_tab(box->envp);
		free(box->pids);
		box->pids = NULL;
		exit(exit_code);
	}
	return (exit_code);
}

int	create_child_process(t_box *box, t_prompt *data, int box_id)
{
	int	exit_code;

	exit_code = 0;
	if (box->rest_info_potential_cmd && box->rest_info_potential_cmd[0] != NULL
		&& ft_strlen(box->rest_info_potential_cmd[0]) > 0)
	{
		if (handle_builtin_commands(box, data) == -1)
			return (exit_code);
		if (handle_builtin_commands_2(box, data) == -1)
			return (exit_code);
	}
	box->envp = ft_gen_envp(data);
	if (!box->rest_info_potential_cmd)
		return (exit_code);
	pipe_manager(data, box, box_id);
	childs(box, data);
	dup2(data->pipefd[1], STDOUT_FILENO);
	close(data->pipefd[1]);
	ft_free_tab(box->envp);
	box->envp = NULL;
	free(box->pids);
	box->pids = NULL;
	return (exit_code);
}
