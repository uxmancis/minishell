/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   09_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbonilla <dbonilla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 03:19:28 by dbonilla          #+#    #+#             */
/*   Updated: 2024/06/22 20:02:08 by dbonilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ft_exit_builtin(t_box *box, t_prompt *prompt, int status)
{
	int	i;

	(void)prompt;
	i = 0;
	// Free dynamically allocated memory in box
	if (box)
	{
		if (box->rest_info_potential_cmd)
			free(box->rest_info_potential_cmd);
		if (box->words_hrdc)
			free(box->words_hrdc);
		if (box->words_infile)
			free(box->words_infile);
		if (box->words_outfile_append)
			free(box->words_outfile_append);
		if (box->words_outfile_strong)
			free(box->words_outfile_strong);
		// if (box->pipefd)
		//     free(box->pipefd);
		if (box->pids)
			free(box->pids);
		if (box->cmd_options)
			free(box->cmd_options);
		if (box->cmd_path)
			free(box->cmd_path);
		if (box->envp)
		{
			while (box->envp[i])
			{
				free(box->envp[i]);
				i++;
			}
			free(box->envp);
		}
		free(box);
	}
	exit(status);
}


void	*ft_free_null(void *ptr)
{
	free(ptr);
	return (NULL);
}

void	ft_free_envp(t_prompt *data)
{
	int	i;

	if (data->envp != NULL)
	{
		i = 0;
		while (data->envp[i])
		{
			free(data->envp[i]);
			i++;
		}
		free(data->envp);
		data->envp = NULL;
	}
}

void	ft_free_vars(t_prompt *data)
{
	t_vars	*tmp;
	t_vars	*current;

	tmp = data->vars;
	while (tmp)
	{
		current = tmp;
		tmp = tmp->next;
		free(current->name);
		free(current->val);
		free(current);
	}
	data->vars = NULL;
}

void	free_strs(char *str, char **strs)
{
	int	i;

	if (str != NULL)
	{
		free(str);
		str = NULL;
	}
	if (strs != NULL)
	{
		i = 0;
		while (strs[i])
		{
			free(strs[i]);
			i++;
		}
		free(strs);
		strs = NULL;
	}
}

void	cleanup_command(char **cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
	{
		free(cmd[i]);
		i++;
	}
	// free(cmd);
}
