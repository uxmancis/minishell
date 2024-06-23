/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   000_debug_mode_1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uxmancis <uxmancis@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 11:22:34 by uxmancis          #+#    #+#             */
/*   Updated: 2024/06/23 12:44:27 by uxmancis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	put_parsing_input_dict(t_prompt *prompt)
{
	int	i;
	int	len_input;

	if (DEBUG_MODE == 0)
		return ;
	i = 0;
	len_input = ft_strlen(prompt->input);
	while (len_input > 0)
	{
		printf("dictionary[%d] = %d\n"RESET_COLOR, i, prompt->dict_quotes[i]);
		len_input--;
		i++;
	}
}

void	put_parsing_input_pipes_1(t_prompt **prompt)
{
	if (DEBUG_MODE == 0)
		return ;
	printf(MAGENTA"01_input_pipe.c - ft_where_r_pipes:");
	printf(" nb_of_pipes = %d\n"RESET_COLOR, (*prompt)->nb_of_pipes);
}

void	put_parsing_input_pipes_2(t_prompt **prompt)
{
	int	tmp_nb_of_pipes;
	int	i;

	if (DEBUG_MODE == 0)
		return ;
	tmp_nb_of_pipes = (*prompt)->nb_of_pipes;
	if (tmp_nb_of_pipes == 0)
		return ;
	i = 0;
	while (tmp_nb_of_pipes > 0)
	{
		printf(MAGENTA"arr_index_pipes[%d] = ", i);
		printf("%d\n"RESET_COLOR, (*prompt)->arr_index_pipes[i]);
		i++;
		tmp_nb_of_pipes--;
	}
}

void	put_parsing_input_pipes_3(t_prompt **prompt)
{
	int	tmp_num_pipes;
	int	i;

	if (DEBUG_MODE == 0)
		return ;
	i = 0;
	tmp_num_pipes = (*prompt)->nb_of_pipes;
	while (tmp_num_pipes > 0)
	{
		printf("array_index_pipes[%d] = ", i);
		printf("%d\n", (*prompt)->arr_index_pipes[i]);
		tmp_num_pipes--;
		i++;
	}
}

void	put_parsing_input_substr(t_prompt **prompt)
{
	int	tmp_nb_of_substr;
	int	i;

	if (DEBUG_MODE == 0)
		return ;
	i = 0;
	tmp_nb_of_substr = (*prompt)->nb_of_substr;
	while (tmp_nb_of_substr > 0)
	{
		printf(YELLOW"substr %d ="RESET_COLOR, i);
		printf(" %s\n", (*prompt)->total_substr_input[i]);
		tmp_nb_of_substr--;
		i++;
	}
}
