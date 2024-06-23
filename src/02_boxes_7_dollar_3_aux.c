/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   02_boxes_7_dollar_3_aux.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbonilla <dbonilla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 22:16:00 by dbonilla          #+#    #+#             */
/*   Updated: 2024/06/23 22:21:54 by dbonilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/*  is_in_env
 *
 *   Checks whether if WORD is found along variables in environment (list).
 *
 *   ft_get_env_local(xxx, str_to_find)
 *       E.g.: ft_get_env_local(data->vars, "USER")
 */
int	is_in_env(char *old_word_before_free, t_x_y_word x_y, t_prompt **prompt)
{
	char	*tmp;

	tmp = NULL;
	tmp = get_word_2(old_word_before_free, x_y);
	if (ft_getenv_local((*prompt)->vars, tmp))
	{
		if (tmp)
		{
			free(tmp);
			tmp = NULL;
		}
		return (1);
	}
	if (tmp)
	{
		free(tmp);
		tmp = NULL;
	}
	return (0);
}

void	get_old_word(char *str_src, char **str_dst)
{
	int	len_src;
	int	i;

	len_src = ft_strlen(str_src);
	i = 0;
	while (len_src > 0)
	{
		(*str_dst)[i] = str_src[i];
		len_src--;
		i++;
	}
}

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
void	finish2up_dq(int **tdqw, int new_len, int *ttdqw, int len_old_word)
{
	int	i;
	int	index_old_dict;

	i = 0;
	index_old_dict = 0;
	while (new_len > 0)
	{
		if ((*tdqw)[i] == 9)
		{
			(*tdqw)[i] = ttdqw[index_old_dict];
			index_old_dict++;
		}
		i++;
		len_old_word--;
		new_len--;
	}
}

void	free_mng_to_replace_sec_dollar(int *keep_dict_q, char *keep_rest_info,
		t_w_d *w_d, char *tmp)
{
	free(keep_dict_q);
	free(keep_rest_info);
	free(w_d);
	free(tmp);
}
