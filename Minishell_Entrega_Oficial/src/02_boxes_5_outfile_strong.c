/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   02_boxes_5_outfile_strong.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uxmancis <uxmancis@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 13:39:46 by uxmancis          #+#    #+#             */
/*   Updated: 2024/05/19 15:11:02 by uxmancis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../inc/minishell.h"

/*ft_infiles
*
*   Returns nothing. Used for exiting ft_infiles function when needed.
*/
int ft_outfile_strong(t_box **box, t_red_type red_type)
{
    //printf("WE ARE IN ft_outfile_strong :)\n");
    if (!is_red_type(box, red_type))
        return(0);
    (*box)->is_outfile_strong = 1;
    (*box)->nb_of_outfile_strong = ft_get_numof_red_type(box, red_type);
    printf("     02_boxes_5_outfile_strong.c - "BLUE"ft_outfile_strong"RESET_COLOR"| nb_of_outfile_strong = "BLUE"%d\n"RESET_COLOR, (*box)->nb_of_outfile_strong);
    ft_check_first_word(box, red_type);
    return (0);
}