/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   02_boxes_7_dollar_8.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uxmancis <uxmancis@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 16:47:33 by uxmancis          #+#    #+#             */
/*   Updated: 2024/06/16 15:00:03 by uxmancis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	next_is_question(char *word_to_be_updated, t_x_y_word x_y)
{
	int	len_word;

	len_word = ft_strlen(word_to_be_updated);
	if ((x_y.index_y + 1) < len_word)
	{
		if (word_to_be_updated[x_y.index_y + 1] == '?')
			return (1);
	}
	return (0);
}
