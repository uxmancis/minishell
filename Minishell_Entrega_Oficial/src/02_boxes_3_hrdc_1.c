/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   02_boxes_3_hrdc_1.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uxmancis <uxmancis@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 14:28:28 by uxmancis          #+#    #+#             */
/*   Updated: 2024/05/19 15:10:54 by uxmancis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../inc/minishell.h"

/*Contains following functions: 
1. void ft_heredocs(t_box **box)
2. int ft_get_numof_heredocs(t_box **box)
3. void ft_check_delimiter(t_box **box)
4. void get_arr_heredoc(int **arr_ind_heredoc, t_box **box)
5. void get_end_arr(int **arr_end, t_box **box, int *arr_ind_heredoc)
*/

/* ft_heredocs
*       Checks whether if 100% heredocs have end delimiter.
*       
*       If heredocs is found with no end delimiter, then error message is printed
+       and minishell program finishes its execution.
*/
void ft_heredocs(t_box **box, t_red_type red_type)
{
    (*box)->nb_of_heredocs = ft_get_numof_red_type(box, red_type);
    printf("     02_boxes_3_hrdc_1.c - "BLUE"ft_heredocs"RESET_COLOR"| numof_heredocs = "BLUE"%d"RESET_COLOR".\n", (*box)->nb_of_heredocs);
    //printf("              do heredocs have" BLUE" delimiter"RESET_COLOR"? yes[1] / no[0]\n");
    //ft_check_delimiter(box); //if 1 heredoc has no delimiter, program finishes
    ft_check_first_word(box, red_type);
    //printf(MAGENTA"<<<<<<<<<<<<    check_delimiter completed     >>>>>>>>>>>>>\n"RESET_COLOR);
}

void get_arr_heredoc(int **arr_ind_heredoc, t_box **box)
{
    int tmp_nb_of_heredocs;
    int i;
    int x; //ze indice-tan gordeta dauan redirekziñua. Es decir, se trata de la redirección en dict_red_index_type[0], o la [1], [2], ...

    tmp_nb_of_heredocs = (*box)->nb_of_redir;
    i = 0;
    x = 0;
    //printf(MAGENTA"nb_of_heredocs = %d\n"RESET_COLOR, tmp_nb_of_heredocs);
    while (tmp_nb_of_heredocs > 0)
    {
        //printf(YELLOW"dict_red_index_type[%d][1] = %s\n"RESET_COLOR, x, ft_enum_to_str((*box)->dict_red_index_type[x][1]));
        if ((*box)->dict_red_index_type[x][1] == HEREDOC)
        {
            //printf("YES HEREDOC WAS FOUND, x = %d\n", x);
            (*arr_ind_heredoc)[i] = (*box)->dict_red_index_type[x][0];
            //printf("x = %d, [0]_INDEX: %d   [1]_TYPE: %s\n", x, (*box)->dict_red_index_type[x][0], ft_enum_to_str((*box)->dict_red_index_type[x][1]));
            i++;
        }
        x++;
        tmp_nb_of_heredocs--;
        //printf(BLUE"BAI: x = %d, tmp_nb_of_heredocs = %d\n"RESET_COLOR, x, tmp_nb_of_heredocs);
    }
    //para comprobaciones:
    /*tmp_nb_of_heredocs = (*box)->nb_of_heredocs;
    i = 0;
    while (tmp_nb_of_heredocs > 0)
    {
        printf(MAGENTA"arr_ind_heredoc[%d] = %d\n"RESET_COLOR, i, (*arr_ind_heredoc)[i]);
        tmp_nb_of_heredocs--;
        i++;
    }*/
}

/*get_end_arr: Informes arr_end variable: filled with 0 and 1.
*      1: YES end delimiter
*      0: NO end delimiter
*
* Variables:
*       int *arr_ind_heredoc: specific array which contains indexes of
*                             total heredocs found along input_substr.
*                             (based on nb_of_heredocs).
*       int red_nb_x: zenbagarren redirekziñua dan
*
*/
void get_end_arr(int **arr_end, t_box **box, int *arr_ind_heredoc)
{
    int tmp_nb_of_heredocs;
    int i;
    //int ind_red_total; //ze posiziñotan dauan redirekziñua en dict_red_index_type --> ezta bihar ya, soluzionatzen dou get_ind-ekin
    //int tmp_to_debug_nb_of_heredocs;
    //int tmp_to_debug_i;

    tmp_nb_of_heredocs = (*box)->nb_of_heredocs;
    //tmp_to_debug_nb_of_heredocs = tmp_nb_of_heredocs;
    //red_nb_x = 1; //empieza en 1 porque indica zenbagarrena. Gero konparaukou con el número total. Hemen behinguagaitxik ez gara 0tik hasten. Uste dot hau obsoleto gelditxu dala.
    i = 0;
    //ind_red_total = 0;
    while (tmp_nb_of_heredocs > 0)
    {
        /*if ((*box)->dict_red_index_type[ind_red_total][1] == HEREDOC)
        {*/
        (*arr_end)[i] = has_end_word(arr_ind_heredoc[i], box, get_ind(arr_ind_heredoc[i], box));
        tmp_nb_of_heredocs--;
        i++;
        //}
        //ind_red_total++;
        //printf("tmp_nb_of_heredocs = %d\n", tmp_nb_of_heredocs);
        //printf(BLUE"arr_ind_heredoc[%d] = %d\n"RESET_COLOR, i, arr_ind_heredoc[i]);
        
    }
    /*printf(YELLOW"tmp_to_debug_nb_of_heredocs = %d\n", tmp_to_debug_nb_of_heredocs);
    tmp_to_debug_i = 0;
    while (tmp_to_debug_nb_of_heredocs > 0)
    {
        printf("end delimiter YES-NO[%d] = %d\n", tmp_to_debug_i, (*arr_end)[tmp_to_debug_i]);
        tmp_to_debug_nb_of_heredocs--;
    }*/
}