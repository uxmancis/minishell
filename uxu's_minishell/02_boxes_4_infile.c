/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   02_boxes_4_infile.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uxmancis <uxmancis@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 19:13:15 by uxmancis          #+#    #+#             */
/*   Updated: 2024/05/11 21:04:21 by uxmancis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*ft_get_numof_infile
*
*   Returns: counter
*       Counter = number of infile type redirecciones found along
*                 dict_red_index_type (box).
*/
int ft_get_numof_infile(t_box **box)
{
    int tmp_nb_of_redir;
    int i;
    int counter;

    tmp_nb_of_redir = (*box)->nb_of_redir;
    i = 0;
    counter = 0;
    while (tmp_nb_of_redir > 0)
    {
        if ((*box)->dict_red_index_type[i][1] == INFILE)
            counter++;
        tmp_nb_of_redir--;
        i++;
    }
    return (counter);
}

/*is_infile
*
*   Returns:
*       1: YES, min. 1 infile type redirección was found in
*          dict_red_index_type (box)
*       0: NO infile type redirección was found along dict_red_index_type
*
*/
int is_infile(t_box **box)
{
    int tmp_nb_of_redir;
    int i;

    tmp_nb_of_redir = (*box)->nb_of_redir;
    i = 0;
    while (tmp_nb_of_redir > 0)
    {
        if ((*box)->dict_red_index_type[i][1] == INFILE)
            return (1);
        tmp_nb_of_redir--;
        i++;
    }
    return (0);
}

/*ft_infiles
*
*   Returns nothing. Used for exiting ft_infiles function when needed.
*/
int ft_infiles(t_box **box, t_red_type red_type)
{
    if (is_infile(box))
    {
        (*box)->is_infile = 1;
        return(0);
    }
    (*box)->nb_of_infile = ft_get_numof_infile(box);
    (void)red_type;
    //check_delimiter (pasarle e_red_type)
    return (0);
}