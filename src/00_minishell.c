/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   00_minishell.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uxmancis <uxmancis@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 10:27:41 by uxmancis          #+#    #+#             */
/*   Updated: 2024/05/19 15:10:37 by uxmancis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/*ft_pipe_after_pipe
*
*   When there is no content between pipes, error is printed.
*
*   Returns: 
*       1: pipe after pipe was found
*       0: no pipe after pipe found
*/
int	ft_pipe_after_pipe(char *input, int *dict_quotes)
{
	int	i;
	int	len;

	i = 0;
	len = ft_strlen(input);
	while (input[i] != '\0')
	{
		if (input[i] == '|' && dict_quotes[i] == 0)
		{
			while (ft_isspace(input[i]))
				i++;
			if (i == len)
				return (0);
			if (input[i + 1])
			{
				if (input[i + 1] == '|' && dict_quotes[i] == 0)
					return (1);
			}
			else
				return (0);
		}
		i++;
	}
	return (0);
}

/*
*	Comentarios antiguos:
*		//Es para indicar final de array. 
*		//Al ser int *, no nos deja '\0' para finalizar array.
		//El 9 es el final. ¿Podríamos hacerlo char *?
		//Sí, pero los indicadres son 0, 1, 2, integers.
		//Podríamos hacerlo '0', '1' y '2', pero no quiero.
*		prompt->dict_quotes[ft_strlen(prompt->input)] = '0';
*
*
*	if (ft_quotes == -1) //Make sure main quotes are close
*	//Asegurar 100% comillas principales cerradas y generar
*	//dict_quotes (&: para que se actualicen los valores 
*	// = se informe por primera vez el diccionario dict_quotes).
*	//Mando &prompt, para que se actualice el diccionario de vuelta.
*/
int	ft_check_quotes_and_pipes(t_prompt *prompt)
{
	if (prompt->input == NULL)
		return (-1);
	prompt->nb_of_substr = 1;
	prompt->dict_quotes = malloc(sizeof(int) * (ft_strlen(prompt->input) + 1));
	prompt->dict_quotes[ft_strlen(prompt->input)] = '0';
	if (ft_quotes (prompt->input, &prompt->dict_quotes) == -1)
	{
		ft_puterror("syntax error: unclosed quotes\n");
		return (-1);
	}
	if (ft_pipe_after_pipe(prompt->input, prompt->dict_quotes))
	{
		ft_puterror("syntax error near unexpected token `||'\n");
		return (-1);
	}
	if (ft_strlen(prompt->input) == 0)
		return (-1);
	return (0);
}

/* ft_get_substr
*
*   Returns:
*       -1: Error
*               ft_quotes: syntax error: unclosed quotes
*               ft_where_r_pipes: syntax error near unexpected token `|'
*        0: Success
*/
int	ft_get_substr(t_prompt *prompt)
{
	if (ft_check_quotes_and_pipes(prompt) == -1)
		return (-1);
	if (DEBUG_MODE != 0)
		put_parsing_input_dict(prompt);
	if (ft_where_r_pipes(&prompt) == -1)
		return (-1);
	if (prompt->nb_of_pipes > 0)
		ft_split_input(&prompt);
	return (0);
}
