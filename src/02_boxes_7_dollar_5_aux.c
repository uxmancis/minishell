/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   02_boxes_7_dollar_5_aux.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbonilla <dbonilla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 17:58:45 by uxmancis          #+#    #+#             */
/*   Updated: 2024/06/23 22:37:46 by dbonilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/*get_len_word
*   Returns: len of substr to delete from particular word in rest_info_...(box)
*/
int	get_len_word(char *old_word_before_free, t_x_y_word x_y)
{
	int	counter;
	int	len_old_word;

	counter = 0;
	len_old_word = ft_strlen(old_word_before_free);
	x_y.index_y++;
	while (x_y.index_y < len_old_word)
	{
		if (!is_special_char(old_word_before_free[x_y.index_y]))
			counter++;
		else
			return (counter);
		if (x_y.index_y == len_old_word)
			break ;
		x_y.index_y++;
	}
	return (counter);
}

/*get_len_word_3
*   
*   Same as get_len_word, but instead of tmp_before_free, we use word in
*	(*box)->rest
*   Returns: len of substr to delete from particular word in rest_info_...(box)
*/
int	get_len_word_3(char *word_to_be_updated, t_x_y_word x_y)
{
	int	counter;
	int	len_old_word;

	counter = 0;
	len_old_word = ft_strlen(word_to_be_updated);
	x_y.index_y++;
	while (x_y.index_y < len_old_word)
	{
		if (!is_special_char(word_to_be_updated[x_y.index_y]))
			counter++;
		else
			return (counter);
		if (x_y.index_y == len_old_word)
			break ;
		x_y.index_y++;
	}
	return (counter);
}

void	replace_pid_aux(t_w_d **w_d, int len_pid_str, char *tmp)
{
	while (len_pid_str > 0)
	{
		(*w_d)->w2update[(*w_d)->y] = tmp[(*w_d)->ind_pid_str];
		(*w_d)->dict_q_to_update[(*w_d)->y] = 0;
		(*w_d)->ind_pid_str++;
		len_pid_str--;
		(*w_d)->y++;
	}
}
