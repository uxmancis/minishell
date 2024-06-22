/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   02_boxes_7_dollar_4.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uxmancis <uxmancis@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 17:58:01 by uxmancis          #+#    #+#             */
/*   Updated: 2024/06/19 23:21:31 by uxmancis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/*get_len_word
*   Returns: len of substr to delete from particular word in rest_info_...(box)
*/
int	get_len_word_2(char *old_word_2_check_before_free, t_x_y_word x_y)
{
	int	counter;
	int	len_old_word;

	len_old_word = ft_strlen(old_word_2_check_before_free);
	counter = 0;
	x_y.index_y++;
	while (x_y.index_y < len_old_word
		&& ft_isalnum(old_word_2_check_before_free[x_y.index_y]))
	{
		counter++;
		x_y.index_y++;
	}
	return (counter);
}

/*
*   str_src = tmp_old_word_before_free 
*	wtu: word_to_be_updated
*/
void	replace_delete(char **wtu, char *str_src, t_x_y_word x_y, int len_new_total_word)
{
	int	len_to_delete;
	int	ind_src;
	int	index_dollar;

	len_to_delete = get_len_word(str_src, x_y); 
	ind_src = 0;
	index_dollar = x_y.index_y;
	x_y.index_y = 0;
	while (len_new_total_word > 0)
	{
		if (ind_src == index_dollar)
		{
			ind_src++;
			while (len_to_delete > 0)
			{
				ind_src++;
				len_to_delete--;
			}
		}
		(*wtu)[x_y.index_y] = str_src[ind_src];
		ind_src++;
		len_new_total_word--;
		x_y.index_y++;
	}
}

size_t	tmp_ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	printf("ft_strlen, str = '%s'\n", str);
	while (str[i] != '\0')
	{
		printf(">>> str[%d] = %c\n", (int)i, str[i]);
		i++;
	}
	printf("ft_strlen result, counter = %d\n", (int)i);
	return (i);
}

/* mng_to_replace_delete
*
*	1st, keep original content in tmp_rest_info_before_free
*	2nd, free old memory
*	3rd, allocate new memory
*/
void	mng_to_replace_delete(char **word_to_be_updated, t_x_y_word x_y)
{
	int		len_old_total_word;
	char	*tmp_rest_info_before_free;
	int		new_len;
	int		len_word;

	len_old_total_word = tmp_ft_strlen((*word_to_be_updated));
	tmp_rest_info_before_free = malloc(sizeof(char) * (len_old_total_word + 1));
	tmp_rest_info_before_free[len_old_total_word] = '\0';
	cpy_word(*word_to_be_updated, &tmp_rest_info_before_free);
	ft_free(*word_to_be_updated);
	len_word = get_len_word_2(tmp_rest_info_before_free, x_y);
	new_len = len_old_total_word - 1 - len_word;
	*word_to_be_updated = malloc(sizeof(char) * (new_len + 1));
	(*word_to_be_updated)[new_len] = '\0';
	replace_delete(word_to_be_updated, tmp_rest_info_before_free, x_y, new_len);
	free (tmp_rest_info_before_free);
}

/*
*   
*/
void	cpy_arr_with_len(int *arr_src, int *arr_dst, int len)
{
	int	i;
	int	two_times;

	i = 0;
	two_times = 0;
	while (len > 0)
	{
		if (arr_src[i] == '$' && two_times != 2)
		{
			i++;
			two_times++;
		}
		arr_dst[i] = arr_src[i];
		i++;
		len--;
	}
}
