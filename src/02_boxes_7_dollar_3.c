/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   02_boxes_7_dollar_3.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uxmancis <uxmancis@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 17:55:40 by uxmancis          #+#    #+#             */
/*   Updated: 2024/06/23 23:43:31 by uxmancis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/* finish2up_dq: finish_to_update_dict_quotes
 *   tmp_dict_quotes_word has already new_len.
 *
 *   Was initialized with 9 value in its whole new_len.
 *
 *   0s were assigned in pid value indexes.
 *
 *   Rest info (still with 9 values) we'll get it from
 *	old/previous tmptmp_dict_quotes,
 *   we used it to keep info of tmp_dict_quotes_word before it got new_len.
 *
 *   Variables:
 *       tdqw: tmp_dict_quotes_word: New arr to get updated
 *       tdqw: tmp_tmp_dict_quotes_word: New arr to get updated
 */
// void	finish2up_dq(int **tdqw, int new_len, int *ttdqw, int len_old_word)
// {
// 	int	i;
// 	int	index_old_dict;

// 	i = 0;
// 	index_old_dict = 0;
// 	while (new_len > 0)
// 	{
// 		if ((*tdqw)[i] == 9)
// 		{
// 			(*tdqw)[i] = ttdqw[index_old_dict];
// 			index_old_dict++;
// 		}
// 		i++;
// 		len_old_word--;
// 		new_len--;
// 	}
// }

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
