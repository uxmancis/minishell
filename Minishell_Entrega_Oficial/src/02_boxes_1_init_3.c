/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   02_boxes_1_init_3.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uxmancis <uxmancis@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/16 13:26:26 by uxmancis          #+#    #+#             */
/*   Updated: 2024/06/19 23:19:11 by uxmancis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/*
*   Generates boxes based on nb_of_substr indicated in prompt
*   structure.
*
*	substr_id: Tells us which substr / which box are we referring to.
*
*	I could also..
*	while (arr_boxes[i])
	{
		ft_free_box(arr_boxes[i]);
		i++;
	}
	
*/
int	ft_gen_boxes(t_prompt *prompt)
{
	t_box	**arr_boxes;
	int		tmp_nb_boxes;
	int		keep_nb_boxes;
	int		substr_id;
	int		i;

	i = 0;
	tmp_nb_boxes = prompt->nb_of_substr;
	keep_nb_boxes = prompt->nb_of_substr;
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
	//David ejecuta
	//printf("palabra: %s\n", )
	
	//Liberamos
	i = 0;
	while (arr_boxes[i] && keep_nb_boxes > 0)
	{
		printf("yes\n");
		ft_free_box(arr_boxes[i]);
		free(arr_boxes[i]);
		i++;
		keep_nb_boxes--;
	}
	free(arr_boxes);
	return (0);
}
