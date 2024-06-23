/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   02_boxes_7_dollar_3.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbonilla <dbonilla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 17:55:40 by uxmancis          #+#    #+#             */
/*   Updated: 2024/06/23 22:22:13 by dbonilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	put_arr(int *arr, int len)
{
	int	i;

	i = 0;
	while (len > 0)
	{
		printf(YELLOW "%d", arr[i]);
		i++;
		len--;
	}
	printf(RESET_COLOR);
}

/*ft_free_word_and_dict
 *
 * w2p: word_to_be_updated
 *
 *
 *
 */
void	ft_free_word_and_dict(char **w2p, int **tmp_dict_quotes_word)
{
	if (*w2p)
	{
		free(*w2p);
		*w2p = NULL;
	}
	if (*tmp_dict_quotes_word)
	{
		free(*tmp_dict_quotes_word);
		*tmp_dict_quotes_word = NULL;
	}
}

void	ft_malloc_and_set(char **str, int len_plus_one)
{
	int	len;

	len = len_plus_one - 1;
	*str = malloc(sizeof(char) * len_plus_one);
	(*str)[len] = '\0';
}

void	assign_values(t_w_d **w_d, char **word_src, int **dict_q, int y)
{
	(*w_d)->w2update = *word_src;
	(*w_d)->dict_q_to_update = *dict_q;
	(*w_d)->y = y;
}

/*mng_to_replace_sec_dollar
 *
 *   particular word in (*box)->rest_info_potencial_cmd is updated
 *   tmp_dict_quotes_word is updated
 *
 *	keep_dict_q: keep_dict_quotes_word
 */
void	mng_to_replace_sec_dollar(char **word_to_be_updated, t_x_y_word x_y,
		int **tmp_dict_quotes_word)
{
	int		len_old_word;
	char	*keep_rest_info;
	int		*keep_dict_q;
	t_w_d	*w_d;
	char	*tmp;

	tmp = ft_get_pid_str();
	w_d = malloc(sizeof(t_w_d) * 1);
	w_d->w2update = NULL;
	w_d->dict_q_to_update = NULL;
	w_d->tmp_val = NULL;
	len_old_word = ft_strlen(*word_to_be_updated);
	ft_malloc_and_set(&keep_rest_info, len_old_word + 1);
	cpy_word(*word_to_be_updated, &keep_rest_info);
	keep_dict_q = malloc(sizeof(int) * len_old_word);
	cpy_arr_with_len_2(*tmp_dict_quotes_word, &keep_dict_q, len_old_word);
	ft_free_word_and_dict(word_to_be_updated, tmp_dict_quotes_word);
	w_d->new_len = len_old_word - 2 + ft_strlen(tmp);
	*tmp_dict_quotes_word = malloc(sizeof(int) * w_d->new_len);
	*word_to_be_updated = ft_calloc(w_d->new_len + 1, sizeof(char));
	assign_values(&w_d, word_to_be_updated, tmp_dict_quotes_word, x_y.index_y);
	replace_pid_sec_dollar(&w_d, keep_rest_info, keep_dict_q, w_d->new_len);
	finish2up_dq(tmp_dict_quotes_word, w_d->new_len, keep_dict_q, len_old_word);
	free_mng_to_replace_sec_dollar(keep_dict_q, keep_rest_info, w_d, tmp);
}
