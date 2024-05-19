/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   03_initialize_cmd.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbonilla <dbonilla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 10:02:43 by dbonilla          #+#    #+#             */
/*   Updated: 2024/05/19 16:13:59 by dbonilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int initialize_cmd(t_box *box, t_prompt *data, int substr_id)
{
    int tmp_nb_boxes = data->nb_of_substr;

    printf(YELLOW"initialize_cmd\n"RESET_COLOR);
    while (tmp_nb_boxes > 0)  
    {
        //write(1, "initialize_cmd\n", 15);      
        if (!(handle_child_process(box, data , substr_id)))
            return(1);
        if (!(handle_parent_process(box)))
            return(1);
        write(1, "End initialize_cmd\n", 20);
        tmp_nb_boxes--;
    }

    return 0;
}















































