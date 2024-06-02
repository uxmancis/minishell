/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   02_boxes_7_dollar_8.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uxmancis <uxmancis@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 16:47:33 by uxmancis          #+#    #+#             */
/*   Updated: 2024/06/02 16:49:37 by uxmancis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../inc/minishell.h"

int next_is_question(t_box **box, t_x_y_rest_info x_y)
{
    int len_word;

    //printf("next_is_sec_dollar | rest_info_potential_cmd[%d][%d] = %c\n", x_y.index_x, x_y.index_x, (*box)->rest_info_potential_cmd[x_y.index_x][x_y.index_y]);
    len_word = ft_strlen((*box)->rest_info_potential_cmd[x_y.index_x]);
    if ((x_y.index_y + 1) < len_word) //a way to prevent overflow
    {
        if ((*box)->rest_info_potential_cmd[x_y.index_x][x_y.index_y + 1] == '?')
        {
            //printf("                         second dollar identified!\n");
            return (1);
        }
    }
    //printf("                         no second dollar\n");
    return (0);
}