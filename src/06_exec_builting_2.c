/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   06_exec_builting_2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbonilla <dbonilla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/22 19:25:49 by dbonilla          #+#    #+#             */
/*   Updated: 2024/06/22 19:38:03 by dbonilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/* put_without_next_line
 *
 *   Used when e.g. echo -n hola (echo with no -n flag)
 *   Prints: hola
 */
void	put_without_next_line(t_box **box)
{
	int	x;
	int	y;

	printf("put_withOUT_next_line\n");
	x = 2;
	while (x < (*box)->nb_of_words_rest)
	{
		y = 0;
		while ((*box)->rest_info_potential_cmd[x][y] != '\0')
		{
			ft_putchar((*box)->rest_info_potential_cmd[x][y]);
			y++;
		}
		x++;
	}
}

/* put_with_next_line
 *
 *   Used when e.g. echo hola (echo with no -n flag)
 *   Prints: hola\n
 */
void	put_with_next_line(t_box **box)
{
	int	x;
	int	y;

	x = 1;
	while (x < (*box)->nb_of_words_rest)
	{
		y = 0;
		while ((*box)->rest_info_potential_cmd[x][y] != '\0')
		{
			ft_putchar((*box)->rest_info_potential_cmd[x][y]);
			y++;
		}
		x++;
	}
	ft_putchar('\n');
}

/*ft_builtin_echo
 *
 *   echo is a command required to build by 42 cursus Minishell project.
 *
 *   echo command displays a line of text in standard output.
 */
int	ft_builtin_echo(t_box *box)
{
	if (ft_strcmp_2(box->rest_info_potential_cmd[1], "-n"))
	{
		printf("\n-n found\n");
		put_without_next_line(&box);
	}
	else
	{
		printf("\n-n NOT found\n");
		put_with_next_line(&box);
		return (-1);
	}
	return (0);
}

/*which_cmd
 *
 *   Return is used as a way to finish function execution.
 */
int	which_cmd(t_box *box, t_prompt **prompt)
{
	int	exit_code;

	exit_code = 0;
	if ((int)ft_strlen(box->rest_info_potential_cmd[1]) == 0)
		return (-1);
	// CHANGE devuelve -1 en caso de error
	if (!box->rest_info_potential_cmd)
	{
		ft_putstr(": command not found\n");
		return (-1);
	}
	if (ft_strcmp_2(box->rest_info_potential_cmd[0], "echo"))
		exit_code = ft_builtin_echo(box);
	else if (ft_strcmp_2(box->rest_info_potential_cmd[0], "pwd"))
		exit_code = ft_builtin_pwd(prompt);
	else if (ft_strcmp_2(box->rest_info_potential_cmd[0], "env"))
		exit_code = ft_env_builtin(prompt, box->rest_info_potential_cmd);
	return (exit_code);
}

int	is_builtin_command(char *cmd)
{
	if (ft_strcmp_2(cmd, "echo") == 0)
		return (1);
	if (ft_strcmp_2(cmd, "pwd") == 0)
		return (1);
	if (ft_strcmp_2(cmd, "cd") == 0)
		return (1);
	if (ft_strcmp_2(cmd, "env") == 0)
		return (1);
	if (ft_strcmp_2(cmd, "exit") == 0)
		return (1);
	return (-1);
}
