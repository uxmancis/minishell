/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   02_boxes_4_infile.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uxmancis <uxmancis@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 19:13:15 by uxmancis          #+#    #+#             */
/*   Updated: 2024/05/19 15:11:00 by uxmancis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../inc/minishell.h"

/*ft_infiles
*
*   Returns nothing. Used for exiting ft_infiles function when needed.
*/
int ft_infiles(t_box **box, t_red_type red_type)
{
    //printf("WE ARE IN ft_infile :)\n");
    if (!is_red_type(box, red_type))
        return(0);
    (*box)->is_infile = 1;
    (*box)->nb_of_infile = ft_get_numof_red_type(box, red_type);
    printf("     02_boxes_4_infile.c - "BLUE"ft_infiles"RESET_COLOR"|nb_of_infile = "BLUE"%d\n"RESET_COLOR, (*box)->nb_of_infile);
    ft_check_first_word(box, red_type);
    return (0);
}