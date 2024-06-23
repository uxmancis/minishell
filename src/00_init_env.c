/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   00_init_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbonilla <dbonilla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 23:31:55 by dbonilla          #+#    #+#             */
/*   Updated: 2024/06/20 11:17:32 by dbonilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

t_prompt	*ft_init_data(char **envp)
{
	t_prompt	*data;

	data = (t_prompt *)malloc(sizeof(t_prompt));
	if (!data)
		return (NULL);
	data->vars = ft_varsnew(ft_strdup("?"), ft_strdup("0"));
	if (!data->vars)
		ft_free_vars(data);
	ft_import_envp(data, envp);
	data->input = NULL;
	data->prompt = NULL;
    data->dict_quotes = 0;
    data->nb_of_pipes = 0;
    data->nb_of_substr = 0;
    data->total_substr_input = 0;
    data->arr_index_pipes = 0;
    data->fd_aux = 0;
    data->pid = 0;
    data->tmp_in = 0;
    data->tmp_out = 0;
    data->envp = 0;
    data->arr_boxes = NULL;
	//printf("Data Initialized\n");
	return (data);
}

t_vars	*ft_varsnew(char *name, char *value)
{
	t_vars	*new;

	new = (t_vars *)malloc(sizeof(t_vars));
	if (!new)
		return (NULL);
	new->name = name;
	new->val = value;
	new->is_exp = 0;
	new->next = NULL;
	return (new);
}

t_vars	*ft_getenv_local(t_vars *line, char *name)
{
	if (line == NULL)
	{
		perror("Error: No  or pwd\n");
		return (NULL);
	}
	while (line)
	{
		if (line->name && !strcmp(line->name, name))
		{
			return (line);
		}
		line = line->next;
	}
	return (NULL);
}
