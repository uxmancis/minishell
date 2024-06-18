/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   02_boxes_7_dollar_3.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uxmancis <uxmancis@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 17:55:40 by uxmancis          #+#    #+#             */
/*   Updated: 2024/06/18 23:14:06 by uxmancis         ###   ########.fr       */
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

void	put_arr(int *arr, int len)
{
	int	i;

	i = 0;
	while (len > 0)
	{
		printf(YELLOW"%d", arr[i]);
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
		free (*w2p);
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
void	mng_to_replace_sec_dollar(char  **word_to_be_updated, t_x_y_word x_y, int **tmp_dict_quotes_word)
{
	int		len_old_word;
	char	*keep_rest_info;
	int		new_len;
	int		*keep_dict_q;
    t_w_d   *w_d;

	w_d = malloc(sizeof(t_w_d) * 1);
	len_old_word = ft_strlen(*word_to_be_updated);
	ft_malloc_and_set(&keep_rest_info, len_old_word + 1);
	cpy_word(*word_to_be_updated, &keep_rest_info);
	keep_dict_q = malloc(sizeof(int) * len_old_word);
	cpy_arr_with_len_2(*tmp_dict_quotes_word, &keep_dict_q, len_old_word);
	ft_free_word_and_dict(word_to_be_updated, tmp_dict_quotes_word);
	new_len = len_old_word - 2 + ft_strlen(ft_get_pid_str());
	*tmp_dict_quotes_word = malloc(sizeof(int) * new_len);
	*word_to_be_updated = ft_calloc(new_len + 1, sizeof(char));
	(*word_to_be_updated)[new_len] = '\0';
	assign_values (&w_d, word_to_be_updated, tmp_dict_quotes_word, x_y.index_y);
	replace_pid_sec_dollar(&w_d, keep_rest_info, keep_dict_q, new_len);
	finish2up_dq(tmp_dict_quotes_word, new_len, keep_dict_q, len_old_word);
}

/*  is_in_env
*
*   Checks whether if WORD is found along variables in environment (list).
*
*   ft_get_env_local(xxx, str_to_find)
*       E.g.: ft_get_env_local(data->vars, "USER")
*/
int	is_in_env(char *old_word_before_free, t_x_y_word x_y, t_prompt **prompt)
{
	if (ft_getenv_local((*prompt)->vars, get_word_2(old_word_before_free, x_y)))
		return (1);
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
