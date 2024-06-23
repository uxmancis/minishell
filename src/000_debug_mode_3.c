/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   000_debug_mode_3.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uxmancis <uxmancis@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 13:53:19 by uxmancis          #+#    #+#             */
/*   Updated: 2024/06/23 21:45:48 by uxmancis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	put_parsing_box_numof_redir_4(t_box **box, int index_of_arr)
{
	if (DEBUG_MODE == 0)
		return ;
	printf(GREEN "               redirection %d assigned:",
		index_of_arr + 1);
	printf("     [0]_INDEX: %d  ",
		(*box)->dictred_i_t[index_of_arr][0]);
	printf("[1]_TYPE: %s\n"RESET_COLOR,
		ft_enum_to_str((*box)->dictred_i_t[index_of_arr][1]));
}

/*
* 	b: box
*	r: red_type
*	y_n: array_yes_no
*/
void	put_parsing_box_words(t_box **b, t_red_type r, int	*y_n)
{
	int	tmp_nb_of_red_type;
	int	i;

	if (DEBUG_MODE == 0)
		return ;
	tmp_nb_of_red_type = get_nb_of_red_type(b, r);
	i = 0;
	while (tmp_nb_of_red_type > 0)
	{
		printf("           is WORD after red_type? YES-NO[%d]", i);
		printf(" = "BLUE"%d\n"RESET_COLOR, y_n[i]);
		tmp_nb_of_red_type--;
		i++;
	}
}

void	put_parsing_box_words_hrdc(t_box **box, t_red_type red_type)
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
		printf("%s"RESET_COLOR"]\n", (*box)->words_hrdc[i]);
		tmp_nb_of_red_type--;
		i++;
	}
	printf("     02_boxes_rest.c - get_word_hrdc| "BLUE);
	printf("char **words_hrdc"RESET_COLOR" generated✅\n");
	printf("     -----------------------------------------------\n\n");
}

void	put_parsing_box_words_inf(t_box **box, t_red_type red_type)
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
		printf("%s"RESET_COLOR"]\n", (*box)->words_infile[i]);
		tmp_nb_of_red_type--;
		i++;
	}
	printf("     02_boxes_rest.c - get_word_infile | "BLUE);
	printf("char **words_hrdc"RESET_COLOR" generated✅\n");
	printf("     -----------------------------------------------\n\n");
}

void	put_parsing_box_words_outf_strong(t_box **box, t_red_type red_type)
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
		printf("%s"RESET_COLOR"]\n", (*box)->words_outfile_strong[i]);
		tmp_nb_of_red_type--;
		i++;
	}
	printf("     02_boxes_rest.c - get_word_outf_strong | "BLUE);
	printf("char **words_hrdc"RESET_COLOR" generated✅\n");
	printf("     -----------------------------------------------\n\n");
}
