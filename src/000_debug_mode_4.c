/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   000_debug_mode_4.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uxmancis <uxmancis@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 14:30:23 by uxmancis          #+#    #+#             */
/*   Updated: 2024/06/23 14:31:27 by uxmancis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	put_parsing_box_words_outf_app(t_box **box, t_red_type red_type)
{
	int	tmp_nb_of_red_type;
	int	i;

	if (DEBUG_MODE == 0)
		return ;
	tmp_nb_of_red_type = get_nb_of_red_type(box, red_type);
	i = 0;
	while (tmp_nb_of_red_type > 0)
	{
		printf("                   word[%d] = ["BLUE, i);
		printf("%s"RESET_COLOR"]\n",(*box)->words_outfile_append[i]);
		tmp_nb_of_red_type--;
		i++;
	}
	printf("     02_boxes_rest.c - get_word_outf_app| "BLUE);
	printf("char **words_hrdc"RESET_COLOR" generated✅\n");
	printf("     -----------------------------------------------\n\n");
}
