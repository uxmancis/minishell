/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   06_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbonilla <dbonilla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/22 13:28:38 by dbonilla          #+#    #+#             */
/*   Updated: 2024/06/23 19:37:22 by dbonilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	ft_delete_node(t_vars **env, char *name)
{
	t_vars	*temp;
	t_vars	*prev;

	prev = NULL;
	temp = *env;
	while (temp != NULL)
	{
		if (ft_strcmp_2(temp->name, name) == 1)
		{
			break ;
		}
		prev = temp;
		temp = temp->next;
	}
	if (temp == NULL)
		return (-1);
	if (prev == NULL)
		*env = temp->next;
	else
		prev->next = temp->next;
	free(temp->name);
	free(temp->val);
	free(temp);
	return (0);
}

int	ft_unset_builtin(t_prompt **prompt, char **cmd)
{
	int	i;
	int	status;

	if (cmd == NULL && cmd[1] == NULL)
		return (-1);
	i = 1;
	status = 0;
	while (cmd[i])
	{
		status += ft_delete_node(&(*prompt)->vars, cmd[i]);
		i++;
	}
	return (status);
}
