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
void	g2h(int start, int end, t_box **box, int r)
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

int	get_word_hrd(t_box **box, int *tmp_nb_of_red_type,
	int *keep_nb_of_red_type, int *i)
{
	*tmp_nb_of_red_type = get_nb_of_red_type(box, HEREDOC);
	*keep_nb_of_red_type = *tmp_nb_of_red_type;
	*i = 0;
	if (*keep_nb_of_red_type > 0)
		(*box)->words_hrdc = malloc(sizeof(char *)
				* (*tmp_nb_of_red_type));
	return (*keep_nb_of_red_type);
}

void	update_variables_11(int *t, int *i)
{
	*t = *t - 1;
	*i = *i + 1;
}

void	get_word_hrdc_1(t_box **box, int *a)
{
	int	t;
	int	k;
	int	i;

	if (get_word_hrd(box, &t, &k, &i) <= 0)
		return ;
	while (t > 0)
	{
		if (is_last_redir(box, a[i]))
		{
			if ((*box)->dictred_i_t[get_ind(a[i], box)][1] == HEREDOC)
				g2h(a[i] + 2, (int)ft_strlen((*box)->input_substr) - 1, box, i);
			break ;
		}
		if ((*box)->dictred_i_t[get_ind(a[i], box)][1] == HEREDOC)
		{
			g2h(a[i] + 2,
				(*box)->dictred_i_t[get_ind(a[i], box) + 1][0] - 1, box, i);
			update_variables_11(&t, &i);
		}
		if (i == k)
			break ;
	}
	put_parsing_box_words_hrdc(box, HEREDOC);
	(*box)->words_hrdc_tmp = (*box)->words_hrdc;
}
