/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   02_boxes_6_cmd_5.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uxmancis <uxmancis@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 15:30:36 by uxmancis          #+#    #+#             */
/*   Updated: 2024/06/23 15:42:05 by uxmancis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	update_variables_3(int *start, int *len)
{
	*start = *start + 1;
	*len = *len + 1;
}

/*
*	n: nb_of_word
*	k: keep_start
*/
void	cpy_1_word_2(int len, int n, t_box **box, int k)
{
	int	x;

	x = 0;
	while (len > 0)
	{
		(*box)->rest_info_potential_cmd[n][x] = (*box)->input_substr[k];
		len--;
		x++;
		k++;
	}
}

/*cpy_1_word
*
*   Variables:
*       nb_of_word: zenbagarren rest-eko hitza dan 
				(posición en index_beginning_words_rest)
*       start: index of beginning of word.
*			Already precise. No need to go spaces++
*/
void	cpy_1_word(t_box **box, int nb_of_word)
{
	int	len;
	int	start;
	int	keep_start;

	start = (*box)->index_beginning_words_rest[nb_of_word];
	keep_start = start;
	len = 0;
	while (possible_cases(box, start)
		&& (start < (int)ft_strlen((*box)->input_substr))
		&& !is_red(box, start))
		update_variables_3(&start, &len);
	(*box)->rest_info_potential_cmd[nb_of_word] = malloc(sizeof(char)
			* (len + 1));
	(*box)->rest_info_potential_cmd[nb_of_word][len] = '\0';
	cpy_1_word_2(len, nb_of_word, box, keep_start);
	if (DEBUG_MODE != 0)
	{
		printf("                      rest_info_potential_cmd");
		printf("[%d] = ["MAGENTA, nb_of_word);
		printf("%s"RESET_COLOR"]\n",
			(*box)->rest_info_potential_cmd[nb_of_word]);
	}
}
