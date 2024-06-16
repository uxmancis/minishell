/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   02_boxes_6_cmd_1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uxmancis <uxmancis@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 10:46:55 by uxmancis          #+#    #+#             */
/*   Updated: 2024/05/24 18:24:44 by uxmancis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/*cpy_rest_words
*
*	tmp_nb: Number of rest of words
*/
void	cpy_rest_words(t_box **box)
{
	int	tmp_nb;
	int	i;

	tmp_nb = (*box)->nb_of_words_rest;
	printf("     cpy_rest_words, nb_of_words_rest = %d\n", tmp_nb);
	(*box)->rest_info_potential_cmd = malloc(sizeof(char *) * (tmp_nb + 1));
	(*box)->rest_info_potential_cmd[tmp_nb] = malloc(sizeof(char) * 1);
	(*box)->rest_info_potential_cmd[tmp_nb][0] = '\0';
	i = 0;
	while (tmp_nb > 0)
	{
		cpy_1_word(box, i);
		tmp_nb--;
		i++;
	}
}

void	ft_get_only_needed(t_box **box)
{
	(*box)->nb_of_words_rest = rest_numof_words(box);
	if ((*box)->nb_of_words_rest == 0)
		return ;
	printf("               rest_numof_words | counter = "MAGENTA"%d\n"RESET_COLOR, (*box)->nb_of_words_rest);
	rest_get_ind_beginning_words(box);
	cpy_rest_words(box);
}

/*ft_get_cmd_args
*
*	Returns:
*		-1: error management
*		0: Success
*
*	Comment: we'll only check dollars if there is min. 1 word to analyse
*/
int	ft_get_cmd_args(t_box **box, t_prompt **prompt)
{
	if (ft_get_what_to_take(box) == -1)
		return (-1);
	printf(MAGENTA"     char *what_to_take"RESET_COLOR" generated✅\n");
	ft_get_only_needed(box);
	check_dollars_expansion(box, prompt);
	return (0);
}

/*ft_cmd_args
*
*	Returns:
*		-1: Error management
*		0: Success
*/
int	ft_cmd_args(t_box **box, t_prompt **prompt)
{
	printf("     02_boxes_6_cmd.c - "MAGENTA"ft_cmd_args\n"RESET_COLOR);
	if (ft_get_cmd_args(box, prompt) == -1)
		return (-1);
	return (0);
}
