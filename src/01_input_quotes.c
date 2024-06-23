/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   01_input_quotes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uxmancis <uxmancis@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 10:53:21 by uxmancis          #+#    #+#             */
/*   Updated: 2024/05/19 15:10:40 by uxmancis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

//int ft_quotes_2(t_prompt **prompt, int i)
/*ft_quotes_2
*
*	Returns:
*		-1: Erro: unclosed quotes
*
*	Additional comments:
*		(*dict_quotes)[i] = 0; //out of quotes (0) assigned to main quotes
*/
int	ft_quotes_2(char *input, int **dict_quotes, int i)
{
	(*dict_quotes)[i] = 0;
	i++;
	while (input[i] != '\0' && input[i] != '\'')
	{
		(*dict_quotes)[i] = 1;
		i++;
	}
	if (i == (int)ft_strlen(input))
		return (-1);
	else
		return (i);
}

//int ft_quotes_3(t_prompt **prompt, int i)
/*	ft_quotes_3
*
*	Returns:
*		-1: Error: unclosed quotes
*		i: 
*	
*	Comments:
*			(*dict_quotes)[i] = 0; //Main double quotes
*			(*dict_quotes)[i] = 2; //Inside double quotes
*/
int	ft_quotes_3(char *input, int **dict_quotes, int i)
{
	(*dict_quotes)[i] = 0;
	i++;
	while (input[i] != '\0' && input[i] != '\"')
	{
		(*dict_quotes)[i] = 2;
		i++;
	}
	if (i == (int)ft_strlen(input))
		return (-1);
	else
		return (i);
}

/*ft_quotes iterates through input for the 1st time.
*   Returns:
*       -1: Error: syntax error: unclosed quotes
*       0: Success (assigns value to dictionary on the way)
*
*   Dictionary refers whether if each position on input:
*       0: is out from quotes
*       1: is inside simple quotes ' '
*       2: is inside double quotes " "
*
*   Calls ft_quotes_2 and ft_quotes_3 to make function shorter 
*   (less than 25 line) because of 42 Norminette.
*
*   I want to use ft_quotes for dict_quotes in t_prompt, but also
*   dict_quotes in t_box. 
*
*	Comments:
*		if (input[i] == '\'') // Inside SINGLE quotes. Are they closed?
*		else if (input[i] == '\"') // Inside DOUBLE quotes. Are they closed?
*

--------------------------------------------------------------*/
//int ft_quotes(t_prompt **prompt) //kenduta komentarixuak
int	ft_quotes(char *input, int **dict_quotes)
{
	int	i;

	i = 0;
	//printf(RESET_COLOR);
	while (input[i] != '\0')
	{
		if (input[i] == '\'')
		{
			i = ft_quotes_2(input, dict_quotes, i);
			if (i == -1)
				return (-1);
		}
		else if (input[i] == '\"')
		{
			i = ft_quotes_3(input, dict_quotes, i);
			if (i == -1)
				return (-1);
		}
		(*dict_quotes)[i] = 0;
		i++;
	}
	return (0);
}

/*ft_where_r_u
*   Uses dictionary to tell whether if character in input
*   in position [index] is out of quotes or not.
*
*   Returns:
*       0: Out of quotes
*       1: Inside single quotes ('  ')
*       2: Inside double quotes ("  ")
*/
int	ft_where_r_u(int index, int *dictionary)
{
	return (dictionary[index]);
}
