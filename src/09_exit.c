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

void	ft_exit_builtin(t_prompt *prompt, int status)
{
    ft_free_prompt(prompt);
    prompt = NULL;
    rl_clear_history();
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
