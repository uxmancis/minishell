/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   02_boxes_5_outfile_append.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uxmancis <uxmancis@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 13:35:05 by uxmancis          #+#    #+#             */
/*   Updated: 2024/05/19 15:11:06 by uxmancis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../inc/minishell.h"

/*ft_get_numof_infile
*
*   Returns: counter
*       Counter = number of infile type redirecciones found along
*                 dict_red_index_type (box).
*/
int ft_get_numof_red_type(t_box **box, t_red_type red_type)
{
    int tmp_nb_of_redir;
    int i;
    int counter;

    tmp_nb_of_redir = (*box)->nb_of_redir;
    i = 0;
    counter = 0;
    while (tmp_nb_of_redir > 0)
    {
        if ((*box)->dict_red_index_type[i][1] == (int)red_type)
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
int is_red_type(t_box **box, t_red_type red_type)
{
    int tmp_nb_of_redir;
    int i;

    tmp_nb_of_redir = (*box)->nb_of_redir;
    i = 0;
    while (tmp_nb_of_redir > 0)
    {
        if ((*box)->dict_red_index_type[i][1] == (int)red_type)
        {
            //printf(GREEN"yes - infile was found\n"RESET_COLOR);
            return (1);
        }
            
        tmp_nb_of_redir--;
        i++;
    }
    //printf(RED"no - infile was not found\n"RESET_COLOR);
    return (0);
}


/*ft_infiles
*
*   Returns nothing. Used for exiting ft_infiles function when needed.
*/
int ft_outfile_append(t_box **box, t_red_type red_type)
{
    //printf("WE ARE IN ft_outfile_append :)\n");
    if (!is_red_type(box, red_type))
        return(0);
    (*box)->is_outfile_append = 1;
    (*box)->nb_of_outfile_append = ft_get_numof_red_type(box, red_type);
    printf("     02_boxes_5_outfile_append.c - "BLUE"ft_outfile_append"RESET_COLOR"| nb_of_outfile_append = "BLUE"%d\n"RESET_COLOR, (*box)->nb_of_outfile_append);
    ft_check_first_word(box, red_type);
    return (0);
}