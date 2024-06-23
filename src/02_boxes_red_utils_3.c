/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   02_boxes_red_utils_3.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbonilla <dbonilla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 22:10:53 by dbonilla          #+#    #+#             */
/*   Updated: 2024/06/23 22:43:14 by dbonilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

// int	ft_check_first_word(t_box **box, t_red_type red_type)
// {
// 	int	*specif_arr_ind_red_type;
// 	int	*arr_word_yes_no;
// 	int	tmp_to_debug_nb_of_red_type;
// 	int	tmp_to_debug_i;
// 	int	nb_of_red_type;

// 	nb_of_red_type = get_nb_of_red_type(box, red_type);
// 	specif_arr_ind_red_type = malloc(sizeof(int) * nb_of_red_type);
// 	if (!specif_arr_ind_red_type)
// 		ft_puterror("malloc error\n");
// 	get_specif_index_red(&specif_arr_ind_red_type, box, red_type);
// 	arr_word_yes_no = malloc(sizeof(int) * nb_of_red_type);
// 	is_word_red(&arr_word_yes_no, box, specif_arr_ind_red_type, red_type);
// 	tmp_to_debug_nb_of_red_type = nb_of_red_type;
// 	tmp_to_debug_i = 0;
// 	while (tmp_to_debug_nb_of_red_type > 0)
// 	{
// 		tmp_to_debug_nb_of_red_type--;
// 		tmp_to_debug_i++;
// 	}
// 	if (!are_all_delimiters(arr_word_yes_no, box, red_type))
// 		if (put_error_red_type(red_type) == -1)
// 			return (-1);
// 	get_word_mgmt(specif_arr_ind_red_type, box, red_type);
// 	return (free(arr_word_yes_no), free(specif_arr_ind_red_type), 0);
// }
