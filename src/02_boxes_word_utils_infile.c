/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   02_boxes_word_utils_infile.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uxmancis <uxmancis@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 21:10:19 by uxmancis          #+#    #+#             */
/*   Updated: 2024/05/19 15:11:34 by uxmancis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	update_variables_10(int *start, int *len_delimiter)
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
*	g2i: get_word_infile_2
*
*/
void	g2i(int start, int end, t_box **box, int red_type_nb_x)
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
		update_variables_10(&start, &len_delimiter);
	(*box)->words_infile[red_type_nb_x]
		= malloc(sizeof(char) * (len_delimiter + 1));
	(*box)->words_infile[red_type_nb_x][len_delimiter] = '\0';
	i = 0;
	while (len_delimiter > 0)
	{
		(*box)->words_infile[red_type_nb_x][i]
			= (*box)->input_substr[keep_start_word];
		i++;
		keep_start_word++;
		len_delimiter--;
	}
}

int	get_word_inf(t_box **box, int *tmp_nb_of_red_type,
	int *keep_nb_of_red_type, int *i)
{
	*tmp_nb_of_red_type = get_nb_of_red_type(box, INFILE);
	*keep_nb_of_red_type = *tmp_nb_of_red_type;
	*i = 0;
	if (*keep_nb_of_red_type > 0)
		(*box)->words_infile = malloc(sizeof(char *)
				* (*tmp_nb_of_red_type));
	return (*keep_nb_of_red_type);
}

void	update_variables_9(int *t, int *i)
{
	*t = *t - 1;
	*i = *i + 1;
}

/*
*	a: arr_ind_red_type
*	k: keep_nb_of_red_type
*/
void	get_word_infile_1(t_box **box, int *a)
{
	int	t;
	int	k;
	int	i;

	if (get_word_inf(box, &t, &k, &i) <= 0)
		return ;
	while (t > 0)
	{
		if (is_last_redir(box, a[i]))
		{
			if ((*box)->dictred_i_t[get_ind(a[i], box)][1] == INFILE)
				g2i(a[i] + 1, (int)ft_strlen((*box)->input_substr) - 1, box, i);
			break ;
		}
		if ((*box)->dictred_i_t[get_ind(a[i], box)][1] == INFILE)
		{
			g2i(a[i] + 1,
				(*box)->dictred_i_t[get_ind(a[i], box) + 1][0] - 1, box, i);
			update_variables_9(&t, &i);
		}
		if (i == k)
			break ;
	}
	put_parsing_box_words_inf(box, INFILE);
	(*box)->words_infile_tmp = (*box)->words_infile;
}
