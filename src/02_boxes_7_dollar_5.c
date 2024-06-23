/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   02_boxes_7_dollar_5.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbonilla <dbonilla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 17:58:45 by uxmancis          #+#    #+#             */
/*   Updated: 2024/06/23 22:37:42 by dbonilla         ###   ########.fr       */
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
	int		len_pid_str;
	int		two_times;
	char	*tmp;

	tmp = ft_get_pid_str();
	len_pid_str = ft_strlen(tmp);
	two_times = 0;
	if ((*w_d)->ind_pid_str == (*w_d)->ind_dollar)
	{
		(*w_d)->ind_pid_str = 0;
		replace_pid_aux(w_d, len_pid_str, tmp);
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
		replace_pid_2_replace_dollar(w_d, kow);
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
