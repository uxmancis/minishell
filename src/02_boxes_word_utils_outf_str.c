/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   02_boxes_word_utils_outf_str.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uxmancis <uxmancis@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 21:14:19 by uxmancis          #+#    #+#             */
/*   Updated: 2024/05/19 15:11:40 by uxmancis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/*get_word_infile_1
*
*/
void	get_word_outf_str_1(t_box **box, int *arr_ind_red_type)
{
	int	tmp_nb_of_red_type;
	int	keep_nb_of_red_type;
	int	total_red_nb_x;
	int	red_type_nb_x;
	int	i;

	tmp_nb_of_red_type = get_nb_of_red_type(box, OUTFILE_STRONG);
	keep_nb_of_red_type = tmp_nb_of_red_type;
	if (keep_nb_of_red_type <= 0)
		return;
	(*box)->words_outfile_strong = malloc(sizeof(char *) * tmp_nb_of_red_type);
	red_type_nb_x = 0;
	total_red_nb_x = 0;
	i = 0;
	while (tmp_nb_of_red_type > 0)
	{
		if (is_last_redir(box, arr_ind_red_type[i]))
		{
			if ((*box)->dict_red_index_type[get_ind(arr_ind_red_type[i], box)][1] == OUTFILE_STRONG)
				get_word_outf_str_2(arr_ind_red_type[red_type_nb_x] + 1, (int)ft_strlen((*box)->input_substr) - 1, box, red_type_nb_x);
			break ;
		}
		if ((*box)->dict_red_index_type[get_ind(arr_ind_red_type[i], box)][1] == OUTFILE_STRONG)
		{
			get_word_outf_str_2(arr_ind_red_type[red_type_nb_x] + 1, (*box)->dict_red_index_type[get_ind(arr_ind_red_type[i], box) + 1][0] - 1, box, red_type_nb_x);
			tmp_nb_of_red_type--;
			red_type_nb_x++;
			i++;
		}
		if (i == keep_nb_of_red_type)
			break ;
		total_red_nb_x++;
	}
	tmp_nb_of_red_type = get_nb_of_red_type(box, OUTFILE_STRONG);
	i = 0;
	while (tmp_nb_of_red_type > 0)
	{
		printf("                   word[%d] = ["BLUE"%s"RESET_COLOR"]\n", i, (*box)->words_outfile_strong[i]);
		tmp_nb_of_red_type--;
		i++;
	}
	(*box)->words_outfile_strong_tmp = (*box)->words_outfile_strong;
	printf("     02_boxes_rest.c - get_word_hrdc| "BLUE"char **words_outfile_strong"RESET_COLOR" generated✅\n");
	printf("     -----------------------------------------------\n\n");
}

/* 
*   Puts each delimiter word in corresponding space
*   inside char **heredoc_delimiters variable (box structure).
*
*   This get_word function will be called nb_of_heredoc times.
*
*   Simply gets first word and ignores rest of possible words
*   that might exist after it. It doesn't care whether if there is
*   a single word or not between redirecciones.
*
*   It might be necessary to add end jeje #segfault (:
*/
void	get_word_outf_str_2(int start, int end, t_box **box, int red_type_nb_x)
{
	int	len_delimiter;
	int	keep_start_word;
	int	i;
	int	len_input_str;

	len_delimiter = 0;
	len_input_str = ft_strlen((*box)->input_substr);
	while (!possible_cases(box, start) && start < len_input_str)
		start++;
	keep_start_word = start;
	while (possible_cases(box, start) && start <= end)
	{
		start++;
		len_delimiter++;
	}
	(*box)->words_outfile_strong[red_type_nb_x] = malloc(sizeof(char) * (len_delimiter + 1));
	(*box)->words_outfile_strong[red_type_nb_x][len_delimiter] = '\0';
	i = 0;
	while (len_delimiter > 0)
	{
		(*box)->words_outfile_strong[red_type_nb_x][i] = (*box)->input_substr[keep_start_word];
		i++;
		keep_start_word++;
		len_delimiter--;
	}
}
