/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   02_boxes_utils_nav.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uxmancis <uxmancis@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 14:23:03 by uxmancis          #+#    #+#             */
/*   Updated: 2024/05/19 15:11:30 by uxmancis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/*Contains following functions:
1. int has_end_last_check(int start, int end, t_box **box)
2. int is_last_redir(t_box **box, int index_current_heredoc)
3. int has_end_word(int index_hrdc_in_substr, t_box **box, int red_nb_x)
*/

/*is_end_word
 *   Checks whether if any word is found between start
 *   and end positions (index) in input_substr.
 *
 *   Returns:
 *       1: YES, word was found (different to spaces and tabs)
 *       0: NO, no word was found
 */
int	has_end_last_check(int start, int end, t_box **box)
{
	while (start < end)
	{
		while (ft_isspace((*box)->input_substr[start]))
			start++;
		if (!ft_isspace((*box)->input_substr[start]))
			return (1);
	}
	return (0);
}

/*Checks if current redirección is the last one or not.
 *       Return:
 *           1: YES, last redir
 *           0: NO, there are more redirs along input_substr
 *
 *   Parameters:
 *       int index_current_heredoc: position (index) of current heredoc
 *                                  in input_substr (t_box box)
 */
int	is_last_redir(t_box **box, int index_current_redir)
{
	int	tmp_total_nb_of_redir;
	int	redir_position;
	int	counter_position;

	tmp_total_nb_of_redir = (*box)->nb_of_redir;
	counter_position = 1;
	redir_position = 0;
	while (tmp_total_nb_of_redir > 0)
	{
		if (index_current_redir == \
			(*box)->dictred_i_t[redir_position][0])
			break ;
		tmp_total_nb_of_redir--;
		counter_position++;
		redir_position++;
	}
	if (counter_position == (*box)->nb_of_redir)
		return (1);
	return (0);
}

/*
 *   Parameters:
 *       index_hrdc_in_substr: index of heredoc in substr.
 *       red_nb_x: redirección number X. Zenbagarren redirekziñua da.
 *                 Adib.: baldin badare guztira Y redirekziño, hau da
 *                        X.a
 *
 *   Returns:
 *       1: YES has delimiter
 *       0: NO no delimiter
 */
int	has_end_word(int index_red_in_substr, t_box **box, int red_nb_x)
{
	if (is_last_redir(box, index_red_in_substr))
	{
		if (index_red_in_substr + 1 == (int)ft_strlen((*box)->input_substr))
			return (0);
		if (has_end_last_check(index_red_in_substr + 1,
				(int)ft_strlen((*box)->input_substr), box))
			return (1);
		return (0);
	}
	if (has_end_last_check(index_red_in_substr + 1,
			(*box)->dictred_i_t[red_nb_x + 1][0] - 1, box))
		return (1);
	return (0);
}

/* get_word_mgmt
 *
 *   Function called when 100% of heredocs do have a delimiter.
 *
 *   Gets delimiter words and puts them in char **heredoc_delimiters
 *   variable in box structure.
 */
void	get_word_mgmt(int *arr_ind_red_type, t_box **box, t_red_type red_type)
{
	if ((int)red_type == HEREDOC)
		get_word_hrdc_1(box, arr_ind_red_type);
	else if ((int)red_type == INFILE)
		get_word_infile_1(box, arr_ind_red_type);
	else if ((int)red_type == OUTFILE_APPEND)
		get_word_outf_app_1(box, arr_ind_red_type);
	else if ((int)red_type == OUTFILE_STRONG)
		get_word_outf_str_1(box, arr_ind_red_type);
}
