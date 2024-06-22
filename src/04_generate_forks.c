/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   04_generate_forks.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uxmancis <uxmancis@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 20:53:18 by dbonilla          #+#    #+#             */
/*   Updated: 2024/06/23 01:15:58 by uxmancis         ###   ########.fr       */
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

int	create_child_process(t_box *box, t_prompt *data, int box_id)
{
	int		exit_code;
	pid_t	pid;

	exit_code = 0;
	box->envp = ft_gen_envp(data);
	if (box->rest_info_potential_cmd && box->rest_info_potential_cmd[0] != NULL
		&& ft_strlen(box->rest_info_potential_cmd[0]) > 0)
	{
		if (ft_strcmp_2(box->rest_info_potential_cmd[0], "export"))
		{
			ft_export_builtin(data, box->rest_info_potential_cmd);
			return (exit_code);
		}
		if (ft_strcmp_2(box->rest_info_potential_cmd[0], "unset")
			&& box->rest_info_potential_cmd[0] != NULL)
		{
			ft_unset_builtin(&data, box->rest_info_potential_cmd);
			return (exit_code);
		}
		if (ft_strcmp_2(box->rest_info_potential_cmd[0], "cd"))
		{
			exit_code = ft_cd_builtin(&data, box->rest_info_potential_cmd);
			return (exit_code);
		}
		if (ft_strcmp_2(box->rest_info_potential_cmd[0], "exit"))
		{
			ft_exit_builtin(box, data, exit_code);
			return (exit_code);
		}
	}
	if (!box->rest_info_potential_cmd)
		exit(exit_code);
	if (box->heredoc_fd) {
		box->heredoc_fd = data->tmp_in;
		data->tmp_in = open("/tmp/heredoc.tmp", O_RDONLY, 0644);
	}
	pipe_manager(data, box, box_id);
	pid = fork();
	if (box->heredoc_fd) {
		data->tmp_in = box->heredoc_fd;
		box->heredoc_fd = 0;
	}
	data->pid = pid;
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
		exit(EXIT_SUCCESS);
	}
	dup2(data->pipefd[1], STDOUT_FILENO);
	close(data->pipefd[1]);
	return (exit_code);
}
