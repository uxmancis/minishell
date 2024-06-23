/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   01_input_pipe_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uxmancis <uxmancis@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/16 13:15:43 by uxmancis          #+#    #+#             */
/*   Updated: 2024/06/18 22:20:11 by uxmancis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	ft_check_nb_of_pipes(t_prompt **prompt)
{
	if ((*prompt)->nb_of_pipes == -1)
	{
		ft_puterror("syntax error near unexpected token `|'\n");
		return (-1);
	}
	return (0);
}

/*ft_where_r_pipes
*   1. ft_is_pipe: Tells us whether if there are any pipes
*   on valid position of input
*   2. If yes pipes in valid location --> cretes array with
*   indexes of found pipes
*
*   Returns:
*       -1: Error: syntax error near unexpected token `|'
*       0: Success
*
*	p = prompt (for shorter lines, norminette)
*/
int	ft_where_r_pipes(t_prompt **p)
{
	int	aux_para_imprimir_nb_of_pipes;
	int	i_to_debug;

	(*p)->nb_of_pipes = ft_is_pipe(p);
	//printf(MAGENTA"01_input_pipe.c - ft_where_r_pipes: nb_of_pipes = %d\n"RESET_COLOR, (*p)->nb_of_pipes);
	i_to_debug = 0;
	if (ft_check_nb_of_pipes(p) == -1)
		return (-1);
	else if ((*p)->nb_of_pipes > 0)
	{
		(*p)->arr_index_pipes = malloc(sizeof(int) * ((*p)->nb_of_pipes));
		if (!(*p)->arr_index_pipes)
			ft_puterror("malloc error\n");
		set_index_pipe(p);
		aux_para_imprimir_nb_of_pipes = (*p)->nb_of_pipes;
		while ((aux_para_imprimir_nb_of_pipes) > 0)
		{
			//printf(MAGENTA"arr_index_pipes[%d] = %d\n"RESET_COLOR, i_to_debug, (*p)->arr_index_pipes[i_to_debug]);
			i_to_debug++;
			aux_para_imprimir_nb_of_pipes--;
		}
	}
	return (0);
}
