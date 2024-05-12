/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   02_boxes_3_hrdc_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uxmancis <uxmancis@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 14:33:15 by uxmancis          #+#    #+#             */
/*   Updated: 2024/05/12 14:35:20 by uxmancis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*Contains following functions: 
1. int get_ind (int hrdc_ind_in_substr, t_box **box)
2. int are_all_delimiters(int *arr_end, t_box **box)
3. void get_delimiters(int *arr_ind_heredoc, t_box **box)
4. void get_word(int start, int end,t_box **box, int heredoc_nb)
*/

/*  get_ind
*
*   What? Gets zenbagarren redirekziñua dan, del total (not only hrdcs).
*   Baina, instead of formato 1.a, 2.a... it gives it us in index form.
*   
*   Receives as parameter hrdc_ind_in_substr: position of heredoc in
*   input_substr.
*
*   Returns:
*       Success: corresponding position's content of varibale
*   int     **dict_red_index_type[x][0].
*       -1: Failure (not expected) in any case.
*
*   How? Based on int hrdc_ind_in_substr identifies which hrdc are we
*   talking about particularly. Then, compares this index with content in
*   dict_red_index_type[x][0]. When match is found, returns x = equivalent
*   to zenbagarren redirekziñua dan = position in dict_red_index_type.
*/
int get_ind (int redir_ind_in_substr, t_box **box)
{
    int tmp_nb_of_redir;
    int x;

    tmp_nb_of_redir = (*box)->nb_of_redir;
    x = 0;
    while (tmp_nb_of_redir > 0)
    {
        if ((*box)->dict_red_index_type[x][0] == redir_ind_in_substr)
            return (x);
        tmp_nb_of_redir--;
        x++;
    }
    return (-1);
}

/*
*   Returns:
*       1 - YES all heredocs have delimiter
*       0 - NO, heredoc was found with no delimiter
*/
/*int are_all_delimiters(int *arr_end, t_box **box)
{
    int tmp_nb_of_heredocs;
    int i;

    tmp_nb_of_heredocs = (*box)->nb_of_heredocs;
    i = 0;
    while (tmp_nb_of_heredocs > 0)
    {
        //printf("arr_end[%d] = %d\n", i, arr_end[i]);
        if (arr_end[i] == 0)
        {
            //printf("NO DELIMITER, heredoc [%d]\n", i);
            return (0);
        }
        tmp_nb_of_heredocs--;
        i++;
    }
    //printf("ALL HEREDOCS HAVE DELIMITER :)\n");
    return (1);
}*/ //old version when just specific for heredoc. New one is in 02_boxes_red_utils.c and works for any type of redirección

/* get_delimiters
*
*   Function called when 100% of heredocs do have a delimiter.
*   
*   Gets delimiter words and puts them in char **heredoc_delimiters
*   variable in box structure.
*/
/*void get_delimiters(int *arr_ind_heredoc, t_box **box)
{
    int tmp_nb_of_heredocs;
    int i;
    int heredoc_nb; //zenbagarren heredoc-a dan. Gero goiaz konparatzera en get_word con 
    
    printf("     02_boxes_rest.c - get_delimiters| Let's go get "BLUE"delimiter words"RESET_COLOR"! :)\n");
    (*box)->heredoc_delimiters = malloc(sizeof(char *)*(*box)->nb_of_heredocs);
    tmp_nb_of_heredocs = (*box)->nb_of_heredocs;
    i = 0;
    heredoc_nb = 0; //índice del heredoc en arr_ind_heredoc --> zenbagarren heredoc da
    while (tmp_nb_of_heredocs > 0)
    {
        if (is_last_redir(box, arr_ind_heredoc[i])) //si este heredoc particularmente es la última redirección
        {
            get_word(arr_ind_heredoc[i] + 2, (int)ft_strlen((*box)->input_substr) - 1, box, heredoc_nb);
            break;
        }    //end = ft_strlen
        get_word(arr_ind_heredoc[i] + 2, (*box)->dict_red_index_type[i + 1][0] - 1, box, heredoc_nb);
        tmp_nb_of_heredocs--;
        heredoc_nb++;
        i++;
    }
    tmp_nb_of_heredocs = (*box)->nb_of_heredocs;
    i = 0;
    while (tmp_nb_of_heredocs > 0)
    {
        printf("                   delimiter[%d] = "BLUE"%s\n"RESET_COLOR, i, (*box)->heredoc_delimiters[i]);
        tmp_nb_of_heredocs--;
        i++;
    }
    printf("     02_boxes_rest.c - get_delimiters| "BLUE"char **heredoc_delimiters"RESET_COLOR" generated✅\n");
}*/

/* 
*   Puts each delimiter word in corresponding space
*   inside char **heredoc_delimiters variable (box structure).
*
*   This get_word function will be called nb_of_heredoc times.
*
*   Simply gets first word and ignores rest of possible words
*   that might exist after it. It doesn't care whether if there is
*   a single word or not between redirecciones.
*
*   It might be necessary to add end jeje #segfault (:
*/
void get_word(int start, int end, t_box **box, int heredoc_nb)
{
    int len_delimiter;
    int keep_start_word;
    int i;

    //printf("get_word\n");
    //printf(BLUE"start = %d, end = %d, heredoc_nb = %d\n"RESET_COLOR, start, end, heredoc_nb);
    len_delimiter = 0;
    while (ft_isspace((*box)->input_substr[start]))
        start++;
    keep_start_word = start;
    //printf(MAGENTA"start = %d\n"RESET_COLOR, start);
    while(!ft_isspace((*box)->input_substr[start]) && start <= end)
    {
        start++;
        len_delimiter++;
        //printf("yes\n");
    }
    //printf("len_delimiter = %d\n", len_delimiter);
    (*box)->words_hrdc[heredoc_nb] = malloc(sizeof(char) * (len_delimiter + 1));
    (*box)->words_hrdc[heredoc_nb][len_delimiter] = '\0';
    i = 0;
    while (len_delimiter > 0)
    {
        //printf(GREEN"yepejoxepe, heredoc_nb = %d, i = %d, keep_start_word = %d\n"RESET_COLOR, heredoc_nb, i, keep_start_word);
        (*box)->words_hrdc[heredoc_nb][i] = (*box)->input_substr[keep_start_word];
        i++;
        keep_start_word++;
        len_delimiter--;
    }
    //printf(GREEN"done\n"RESET_COLOR);
}