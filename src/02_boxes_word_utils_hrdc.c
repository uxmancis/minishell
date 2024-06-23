/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   02_boxes_word_utils_hrdc.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uxmancis <uxmancis@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 20:43:19 by uxmancis          #+#    #+#             */
/*   Updated: 2024/05/19 15:11:32 by uxmancis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	get_word_hrdc_1(t_box **box, int *arr_ind_red_type)
{
	int	tmp_nb_of_red_type;
	int	keep_nb_of_red_type;
	int	total_red_nb_x;
	int	red_type_nb_x;
	int	i;

	tmp_nb_of_red_type = get_nb_of_red_type(box, HEREDOC);
	keep_nb_of_red_type = tmp_nb_of_red_type;
	(*box)->words_hrdc = malloc(sizeof(char *) * tmp_nb_of_red_type);
	if (!(*box)->words_hrdc)
		perror("\n\nmalloc error: words_hrdc\n");
	red_type_nb_x = 0;
	i = 0;
	total_red_nb_x = 0;
	while (tmp_nb_of_red_type > 0)
	{
		if (is_last_redir(box, arr_ind_red_type[i]))
		{
			if ((*box)->dict_red_index_type[get_ind(arr_ind_red_type[i], box)][1] == HEREDOC)
				get_word_hrdc_2(arr_ind_red_type[red_type_nb_x] + 2, (int)ft_strlen((*box)->input_substr) - 1, box, red_type_nb_x);
			break ;
		}
		if ((*box)->dict_red_index_type[get_ind(arr_ind_red_type[i], box)][1] == HEREDOC)
		{
			get_word_hrdc_2(arr_ind_red_type[red_type_nb_x] + 2, (*box)->dict_red_index_type[get_ind(arr_ind_red_type[i], box) + 1][0] - 1, box, red_type_nb_x);
			tmp_nb_of_red_type--;
			red_type_nb_x++;
			i++;
		}
		if (i == keep_nb_of_red_type)
			break ;
		total_red_nb_x++;
	}
	put_parsing_box_words_hrdc(box, HEREDOC);
}

void	update_variables_4(int *start, int *len_delimiter)
{
	*start = *start + 1;
	*len_delimiter = *len_delimiter + 1;
}

/* 
*   Puts each word in corresponding space inside 
*   char **words_infile variable (box structure).
*
*   This get_word function will be called nb_of_red_type times.
*
*   Simply gets first word and ignores rest of possible words
*   that might exist after it. It doesn't care whether if there is
*   a single word or not between redirecciones.
*
*	r: red_type_nb_x
*	k: keep_start_word
*
*/
void	get_word_hrdc_2(int start, int end, t_box **box, int r)
{
	int	len_delimiter;
	int	k;
	int	i;
	int	len_input_str;

	len_delimiter = 0;
	len_input_str = ft_strlen((*box)->input_substr);
	while (!possible_cases(box, start) && start < len_input_str)
		start++;
	k = start;
	while (possible_cases(box, start) && start <= end)
		update_variables_4(&start, &len_delimiter);
	(*box)->words_hrdc[r] = malloc(sizeof(char)
			* (len_delimiter + 1));
	(*box)->words_hrdc[r][len_delimiter] = '\0';
	i = 0;
	while (len_delimiter > 0)
	{
		(*box)->words_hrdc[r][i] = (*box)->input_substr[k];
		i++;
		k++;
		len_delimiter--;
	}
}
