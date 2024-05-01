/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   02_boxes.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uxmancis <uxmancis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 20:22:45 by uxmancis          #+#    #+#             */
/*   Updated: 2024/05/01 10:31:47 by uxmancis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void ft_strcpy (char *str_src, char **str_dst)
{
    int len;
    int i; 
    
    len = ft_strlen(str_src);
    i = 0;
    while (len > 0)
    {
        (*str_dst)[i] = str_src[i];
        i++;
        len--;
    }
}

void generate_substr(t_prompt *prompt, int substr_id, t_box *box)
{
    int len;

    len = (int)ft_strlen(prompt->total_substr_input[substr_id]);
    //printf("len substr = %d\n", len);
    box->input_substr = malloc(sizeof(char) * (len + 1)); //+1: valor nulo final
    box->input_substr[len] = '\0';
    ft_strcpy(prompt->total_substr_input[substr_id], &box->input_substr);
    printf("Copied! :) BOX: substr = %s\n", box->input_substr);
}

/*  ft_boxes_init, Initializes following variables in 
*   t_box structure:
*       · input_substr: substr (input divided based on splits)
*/
void ft_boxes_init(t_prompt *prompt, int substr_id)
{
    t_box box;
    //int tmp_len;

    //tmp_len = ft_strlen(prompt->total_substr_input[substr_id] + 1);
    //printf("tmp_len = %d\n", tmp_len);
    generate_substr(prompt, substr_id, &box);
    get_redirections(&box);
}

void ft_analyse_boxes(t_prompt *prompt)
{
    int tmp_nb_boxes;
    int substr_id; //¿Qué substr es? ¿Es el n.º 0? ¿El número 1?

    printf(BLUE"FT_ANALYSE_BOXES\n"RESET_COLOR);
    tmp_nb_boxes = prompt->nb_of_substr;
    printf("nb_boxes = %d\n", prompt->nb_of_substr);
    substr_id = 0;
    while (tmp_nb_boxes > 0)
    {
        ft_boxes_init(prompt, substr_id);
        tmp_nb_boxes--;
        substr_id++;
    }
}
