/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   000_debug_mode_4.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uxmancis <uxmancis@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 14:30:23 by uxmancis          #+#    #+#             */
/*   Updated: 2024/06/23 15:54:20 by uxmancis         ###   ########.fr       */
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
		printf("%s"RESET_COLOR"]\n", (*box)->words_outfile_append[i]);
		tmp_nb_of_red_type--;
		i++;
	}
	printf("     02_boxes_rest.c - get_word_outf_app| "BLUE);
	printf("char **words_hrdc"RESET_COLOR" generated✅\n");
	printf("     -----------------------------------------------\n\n");
}

void	put_parsing_box_index_words(t_box **box, int x)
{
	if (DEBUG_MODE == 0)
		return ;
	printf("             index_beginning_words_rest[%d]", x);
	printf(" = %d\n", (*box)->index_beginning_words_rest[x]);
}

void	put_parsing_box_what_to_take(t_box **box)
{
	int	len;
	int	i;

	if (DEBUG_MODE == 0)
		return ;
	len = ft_strlen((*box)->input_substr);
	i = 0;
	printf("     what_to_take: len = %d\n", len);
	while (len > 0)
	{
		printf("               what_to_take[%d] = ", i);
		printf("%c\n", (*box)->what_to_take[i]);
		len--;
		i++;
	}
}

void	put_parsing_box_end(int substr_id)
{
	if (DEBUG_MODE == 0)
		return ;
	printf(BLUE"BOX GENERATION COMPLETED✅, box number = ");
	printf("%d\n"RESET_COLOR, substr_id);
	printf(BLUE"==========================================");
	printf("====================================\n\n\n"RESET_COLOR);
}
