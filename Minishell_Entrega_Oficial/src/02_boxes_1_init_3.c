/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   02_boxes_1_init_3.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uxmancis <uxmancis@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/16 13:26:26 by uxmancis          #+#    #+#             */
/*   Updated: 2024/06/18 21:52:11 by uxmancis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/*
*   Generates boxes based on nb_of_substr indicated in prompt
*   structure.
*
*	substr_id: Tells us which substr / which box are we referring to.
*/
int	ft_gen_boxes(t_prompt *prompt)
{
	t_box	**arr_boxes;
	int		tmp_nb_boxes;
	int		substr_id;
	int		i;

	i = 0;
	tmp_nb_boxes = prompt->nb_of_substr;
	printf("     02_boxes.c - ft_gen_boxes| nb_boxes = %d\n", prompt->nb_of_substr);
	substr_id = 1;
	arr_boxes = malloc(sizeof(t_box) * tmp_nb_boxes);
	while (tmp_nb_boxes > 0)
	{
		if (ft_boxes_init(&arr_boxes[i], prompt, substr_id) == -1)
			return (-1);
		tmp_nb_boxes--;
		substr_id++;
		i++;
	}
	return (0);
}
