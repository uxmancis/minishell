/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   06_exec_builting.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uxmancis <uxmancis@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 11:45:31 by uxmancis          #+#    #+#             */
/*   Updated: 2024/06/23 22:58:47 by uxmancis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	ft_env_builtin(t_prompt **prompt, char **cmd)
{
	t_vars	*tmp;
	t_vars	*env_var;

	(void)cmd;
	if (cmd[1] != NULL)
	{
		perror("Usage: env\n");
		return (-1);
	}
	tmp = (*prompt)->vars;
	while (tmp)
	{
		if (ft_strcmp(tmp->name, "?") != 0)
		{
			env_var = ft_getenv_local((*prompt)->vars, tmp->name);
			if (env_var != NULL && env_var->val != NULL)
			{
				printf("%s=%s\n", tmp->name, env_var->val);
			}
		}
		tmp = tmp->next;
	}
	return (0);
}

/*ft_strcmp_2
 *
 *   Returns:
 *       1: yes str are exactly the same
 *       0: not same str
 */

int	ft_strcmp_2(char *str_2_check, char *cmd)
{
	int		i;
	int		len_str_2_check;
	int		len_cmd;

	len_str_2_check = ft_strlen(str_2_check);
	len_cmd = ft_strlen(cmd);
	i = 0;
	if (len_str_2_check != len_cmd)
		return (0);
	else if (len_str_2_check == len_cmd)
	{
		while (len_cmd > 0)
		{
			if (str_2_check[i] != cmd[i])
				return (0);
			i++;
			len_cmd--;
		}
	}
	return (1);
}

/*ft_builtin_pwd
 *
 *   pwd is a command required to build by 42 cursus Minishell project.
 *
 *   pwd command prints the name of current/working directory.
 *   Information is taken from environment. We've implemented it using
 *   linked list.
 */
int	ft_builtin_pwd(t_prompt **prompt)
{
	ft_putstr_fd(ft_getenv_local((*prompt)->vars, "PWD")->val, 1);
	return (0);
}
