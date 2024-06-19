/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   02_boxes_7_dollar_5.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uxmancis <uxmancis@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 17:58:45 by uxmancis          #+#    #+#             */
/*   Updated: 2024/06/19 23:03:03 by uxmancis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/*replace_pid_1_cpy
*
*	When content before dollar, it's stored.
*
*	k_old_w = keep_old_word
*	k_old_d = keep_old_d
*	dict_q_to_update = dictionary of quotes to be updated
*	
*/
void	replace_pid_1_cpy_before_d(t_w_d **w_d, char *k_old_w, int *k_old_d)
{
	while ((*w_d)->ind_pid_str != (*w_d)->ind_dollar)
	{
		(*w_d)->w2update[(*w_d)->y] = k_old_w[(*w_d)->ind_old_word];
		(*w_d)->dict_q_to_update[(*w_d)->y] = k_old_d[(*w_d)->ind_old_word];
		(*w_d)->ind_pid_str++;
		(*w_d)->ind_old_word++;
		(*w_d)->y++;
	}
}

/*replace_pid_2_replace_dollar
*
*	Once $$ is found, it's substituted by pid.
*
*	Additional explanatory comments:
*		while (two_times != 2...) //so as to skip and not cpy 2
*		dollars && safety to prevent overflow
*/
void	replace_pid_2_replace_dollar(t_w_d **w_d, char *keep_old_word)
{
	int	len_pid_str;
	int	two_times;
	char *tmp;

	tmp = ft_get_pid_str();
	len_pid_str = ft_strlen(tmp);
	two_times = 0;
	if ((*w_d)->ind_pid_str == (*w_d)->ind_dollar)
	{
		(*w_d)->ind_pid_str = 0;
		while (len_pid_str > 0)
		{
			(*w_d)->w2update[(*w_d)->y] = tmp[(*w_d)->ind_pid_str];
			(*w_d)->dict_q_to_update[(*w_d)->y] = 0;
			(*w_d)->ind_pid_str++;
			len_pid_str--;
			(*w_d)->y++;
		}
		two_times = 0;
		while (two_times != 2
			&& (*w_d)->ind_old_word < (*w_d)->keep_new_len_word
			&& keep_old_word[(*w_d)->ind_old_word] == '$')
		{
			(*w_d)->ind_old_word++;
			two_times++;
		}
	}
	free(tmp);
}

/*replace_pid_3_after_dollar
*
*	If still more content after $$, it's copied.
*
*	k_old_w = keep_old_word
*	k_old_d = keep_old_d
*	nlw = new_len_word
*/
void	rep_pid_3_after_dollar(t_w_d **w_d, char *k_o_w, int *k_o_d, int nlw)
{
	while ((*w_d)->y < (*w_d)->keep_new_len_word)
	{
		(*w_d)->w2update[(*w_d)->y] = k_o_w[(*w_d)->ind_old_word];
		(*w_d)->dict_q_to_update[(*w_d)->y] = k_o_d[(*w_d)->ind_old_word];
		(*w_d)->ind_old_word++;
		(*w_d)->ind_pid_str++;
		nlw--;
		(*w_d)->y++;
	}
}

/* replace with pid
*
*   Also new dict_quotes is generated (so than we can use it to
*	check if no_more_dollars)
*
*	k_old_w = keep_old_word
*	k_old_d = keep_old_d
*	nlw = new_len_word
*/
void	replace_pid_sec_dollar(t_w_d **w_d, char *kow, int *kod, int nlw)
{
	(*w_d)->ind_pid_str = 0;
	(*w_d)->ind_old_word = 0;
	(*w_d)->ind_dollar = (*w_d)->y;
	(*w_d)->y = 0;
	(*w_d)->keep_new_len_word = nlw;
	replace_pid_1_cpy_before_d(w_d, kow, kod);
	if ((*w_d)->ind_pid_str == (*w_d)->ind_dollar)
		replace_pid_2_replace_dollar(w_d, kow); //malloc pid de itoa
	if (nlw != 0)
		rep_pid_3_after_dollar(w_d, kow, kod, nlw);
}

/*
*   Special chars include: 
*       $ : 36 (decimal)
*/
int	is_special_char(char c)
{
	if ((c >= 0 && c <= 47) || (c >= 58 && c <= 64))
		return (1);
	return (0);
}

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
