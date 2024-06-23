/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   02_boxes_red_utils_2.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uxmancis <uxmancis@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 14:21:22 by uxmancis          #+#    #+#             */
/*   Updated: 2024/06/24 00:08:10 by uxmancis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/*ft_check_first_word
*   Checks whether of 100% redirecciones in substr do have
*   a word after them. 
*
*       HEREDOC || INFILE: If redirección with no delimiter is found, 
*   error message is printed and program finishes its execution.
*
*       get_word_mgmt: gets first words to work as
*               HEREDOC: end delimiter word
*               INFILE: infile filename
*               OUTFILE (strong or append): outfile filename
*
*   Variables:
*       int *specif_arr_ind_red_type: specific array which
*		stores specific indexes of
*                              specified e_red_type.
*                              E.g. if HEREDOCS are going to 
+							   be analysed, array will store indexes
*								of HEREDOCS. If another type
*                                   of redirección is asked for (e_red_type), the
*                                   corresponding indexes will be stored.
*   
*       int *arr_word_yes_no: array which len is number of
*		redirecciones of X type.
*                     In each position stores 1 or 0, depending
*                     on if redirección has a word after it or not.
*
*   Returns:
*       -1: Error
*       0: Success
*
*/
int	ft_check_first_word(t_box **box, t_red_type red_type)
{
	int	*specif_arr_ind_red_type;
	int	*arr_word_yes_no;
	int	nb_of_red_type;

	nb_of_red_type = get_nb_of_red_type(box, red_type);
	specif_arr_ind_red_type = malloc(sizeof(int) * nb_of_red_type);
	if (!specif_arr_ind_red_type)
		ft_puterror ("malloc error\n");
	get_specif_index_red(&specif_arr_ind_red_type, box, red_type);
	arr_word_yes_no = malloc(sizeof(int) * nb_of_red_type);
	is_word_red(&arr_word_yes_no, box, specif_arr_ind_red_type, red_type);
	put_parsing_box_words(box, red_type, arr_word_yes_no);
	if (!are_all_delimiters(arr_word_yes_no, box, red_type))
	{
		if (put_error_red_type(red_type) == -1)
			return (-1);
	}
	get_word_mgmt(specif_arr_ind_red_type, box, red_type);
	free(arr_word_yes_no);
	free(specif_arr_ind_red_type);
	return (0);
}
