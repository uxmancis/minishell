/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   02_boxes_7_dollar_2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uxmancis <uxmancis@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 17:55:05 by uxmancis          #+#    #+#             */
/*   Updated: 2024/06/23 21:06:00 by uxmancis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	cpy_arr_with_len_2(int *arr_src, int **arr_dst, int len)
{
	int	i;

	i = 0;
	while (len > 0)
	{
		(*arr_dst)[i] = arr_src[i];
		i++;
		len--;
	}
}

/*  replace_env
*
*   When still more info after replacing content, cpy rest.
*/
void	replace_env_last(t_w_d **w_d, int keep_len_new_word,
	char *keep_old_word, int *keep_old_dict)
{
	while ((*w_d)->y < keep_len_new_word)
	{
		(*w_d)->w2update[(*w_d)->y] = keep_old_word[(*w_d)->ind_old_word];
		(*w_d)->dict_q_to_update[(*w_d)->y]
			= keep_old_dict[(*w_d)->ind_old_word];
		(*w_d)->y++;
		(*w_d)->ind_old_word++;
	}
}

void	replace_env_step_2(t_w_d **w_d, int len_str_to_find, char *tmp_val)
{
	(*w_d)->ind_old_word++;
	while (len_str_to_find > 0)
	{
		(*w_d)->ind_old_word++;
		len_str_to_find--;
	}
	while ((*w_d)->len_val > 0)
	{
		(*w_d)->w2update[(*w_d)->y] = tmp_val[(*w_d)->ind_val];
		(*w_d)->dict_q_to_update[(*w_d)->y] = 0;
		(*w_d)->ind_val++;
		(*w_d)->y++;
		(*w_d)->len_val--;
	}
}

void	replace_env_step_1(t_w_d **w_d, char *keep_old_word,
	int *keep_old_dict_quotes_word)
{
	while ((*w_d)->ind_new_word < (*w_d)->ind_dollar)
	{
		(*w_d)->w2update[(*w_d)->y] = keep_old_word[(*w_d)->ind_old_word];
		(*w_d)->dict_q_to_update[(*w_d)->y]
			= keep_old_dict_quotes_word[(*w_d)->ind_old_word];
		(*w_d)->ind_new_word++;
		(*w_d)->ind_old_word++;
		(*w_d)->y++;
		(*w_d)->new_len--;
	}
}

void	set_w_d(t_w_d **w_d, int y, char **w2up, int **tmp_dict_quotes_word)
{
	(*w_d)->ind_dollar = y;
	(*w_d)->y = 0;
	(*w_d)->w2update = *w2up;
	(*w_d)->dict_q_to_update = *tmp_dict_quotes_word;
	(*w_d)->ind_old_word = 0;
	(*w_d)->ind_new_word = 0;
	(*w_d)->ind_val = 0;
}
