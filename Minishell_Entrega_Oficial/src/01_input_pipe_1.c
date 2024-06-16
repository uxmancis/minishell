/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   01_input_pipe.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uxmancis <uxmancis@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 12:55:10 by uxmancis          #+#    #+#             */
/*   Updated: 2024/05/19 15:10:31 by uxmancis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/*  ft_pipe_last
*
*   Checks whether if pipe is in last position of input.
*   Returns:
*       1: YES, pipe in last position (will be managed as error)
*       0: NO, other character in last position
*/
int	ft_pipe_last(char *input)
{
	int	i;

	i = ft_strlen(input) - 1;
	while (i > 0)
	{
		while (ft_isspace(input[i]))
			i--;
		if (input[i] == '|')
		{
			return (1);
		}
		else
			break ;
	}
	return (0);
}

/*  ft_pipe_first
*
*   Checks whether if pipe is in first position of input.
*   Returns:
*       1: YES, pipe in first position (will be managed as error)
*       0: NO, other character in first position
*/
int	ft_pipe_first(char *input)
{
	int	i;

	i = 0;
	while (input[i] != '\0')
	{
		while (ft_isspace(input[i]))
			i++;
		if (input[i] == '|')
			return (1);
		else
			break ;
	}
	return (0);
}

/*ft_pipe_first_or_last
*   
*   Returns:
*       1: Error found (pipe in first or last position)
*       O: Everything ok, no pipes found in invalid position (first or last)
*/
int	ft_pipe_first_or_last(char *input)
{
	if (ft_pipe_first(input) == 1 || ft_pipe_last(input) == 1)
		return (-1);
	return (0);
}

/*ft_is_there_pipe
*
*   1. Checks whether if pipes are found or not. Returns: -1, 0, >0  
*       -1: Error: pipe found in incorrect position, [0] or last position.
*       0: No pipes found
*       >0: number of found pipes
*
*   2. arr_index_pipes:
*       Index of real pipes (out of quotes) will be stored in array, for
*       future split. Information in char *dictionary is used to know
*       location of pipe (0: out of quotes, 1: inside single or 2. inside
*       double quotes).
*/
int	ft_is_pipe(t_prompt **prompt)
{
	int	i;
	int	counter;

	counter = 0;
	i = 0;
	while ((*prompt)->input[i] != '\0')
	{
		if ((*prompt)->input[i] == '|' && (*prompt)->dict_quotes[i] == 0)
		{
			if (ft_pipe_first_or_last((*prompt)->input) == -1)
				return (-1);
			counter++;
		}
		i++;
	}
	if (counter == 0)
		return (0);
	return (counter);
}

/*DESCRIPTION:
*   Returns:
*       0: No index found
*       >0: Number of found indexes
*
*   Additionally, array is created with indexes of input
*   where pipes are located.
*/
void	set_index_pipe(t_prompt **prompt)
{
	int	i;
	int	y;

	i = 0;
	y = 0;
	while ((*prompt)->input[i] != '\0')
	{
		if ((*prompt)->input[i] == '|')
		{
			if ((*prompt)->dict_quotes[i] == 0)
			{
				(*prompt)->arr_index_pipes[y] = i;
				y++;
			}
		}
		i++;
	}
}
