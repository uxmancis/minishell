/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   09_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbonilla <dbonilla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 15:02:42 by dbonilla          #+#    #+#             */
/*   Updated: 2024/06/23 21:26:26 by dbonilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

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

void	cleanup_command(char **cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
	{
		free(cmd[i]);
		i++;
	}
	free(cmd);
}

void	ft_free_input(t_prompt *data)
{
	int	i;

	i = 0;
	free(data->input);
	data->input = NULL;
	free(data->prompt);
	data->prompt = NULL;
	free(data->dict_quotes);
	data->dict_quotes = NULL;
	ft_free_char(data->total_substr_input, data->nb_of_substr);
	data->total_substr_input = NULL;
	free(data->arr_index_pipes);
	data->arr_index_pipes = NULL;
	if (data->arr_boxes != NULL)
	{
		while (data->arr_boxes[i] != NULL)
		{
			ft_free_box(data->arr_boxes[i]);
			free(data->arr_boxes[i]);
			data->arr_boxes[i] = NULL;
			i++;
		}
	}
}
