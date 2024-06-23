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

int	get_word_str_part_2(t_box **box, int *tmp_nb_of_red_type,
	int *keep_nb_of_red_type, int *i)
{
	*tmp_nb_of_red_type = get_nb_of_red_type(box, OUTFILE_STRONG);
	*keep_nb_of_red_type = *tmp_nb_of_red_type;
	*i = 0;
	if (*keep_nb_of_red_type > 0)
		(*box)->words_outfile_strong = malloc(sizeof(char *)
				* (*tmp_nb_of_red_type));
	return (*keep_nb_of_red_type);
}

void	update_variables_5(int *t, int *i)
{
	*t = *t - 1;
	*i = *i + 1;
}

/*get_word_infile_1
*
*	i: red_type_nb_x
*	t: tmp_nb_of_red_type
*	k: keep_nb_of_red_type
*	a: arr_ind_red_type
*/
void	get_word_outf_str_1(t_box **box, int *a)
{
	int	t;
	int	k;
	int	i;

	if (get_word_str_part_2(box, &t, &k, &i) <= 0)
		return ;
	while (t > 0)
	{
		if (is_last_redir(box, a[i]))
		{
			if ((*box)->dict_red_index_type[get_ind(a[i], box)][1] == OUTFILE_STRONG)
				g2(a[i] + 1, (int)ft_strlen((*box)->input_substr) - 1, box, i);
			break ;
		}
		if ((*box)->dict_red_index_type[get_ind(a[i], box)][1] == OUTFILE_STRONG)
		{
			g2(a[i] + 1, (*box)->dict_red_index_type[get_ind(a[i], box) + 1][0] - 1, box, i);
			update_variables_5(t, i);
		}
		if (i == k)
			break ;
	}
	put_parsing_box_words_outf_strong(box, OUTFILE_STRONG);
	(*box)->words_outfile_strong_tmp = (*box)->words_outfile_strong;
}

/* g2: get_word_outf_str_2
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
void	g2(int start, int end, t_box **box, int red_type_nb_x)
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
