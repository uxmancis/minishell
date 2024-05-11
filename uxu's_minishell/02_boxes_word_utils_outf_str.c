/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   02_boxes_word_utils_outf_str.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uxmancis <uxmancis@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 21:14:19 by uxmancis          #+#    #+#             */
/*   Updated: 2024/05/11 21:18:28 by uxmancis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*get_word_infile_1
*
*/
void get_word_outf_str_1(t_box **box, int *arr_ind_red_type)
{
    int tmp_nb_of_red_type;
    int red_type_nb_x; //zenbagarrena dan
    int i;

    tmp_nb_of_red_type = get_nb_of_red_type(box, OUTFILE_STRONG);
    (*box)->outfile_st_filenames = malloc(sizeof(char *) * tmp_nb_of_red_type);
    red_type_nb_x = 0;
    i = 0;
    while (tmp_nb_of_red_type > 0)
    {
        if (is_last_redir(box, arr_ind_red_type[i]))
        {
            get_word_infile_2(arr_ind_red_type[i] + 1, (int)ft_strlen((*box)->input_substr) - 1, box, red_type_nb_x);
            break;
        }
        get_word_hrdc_2(arr_ind_red_type[i] + 1, (*box)->dict_red_index_type[i + 1][0] - 1, box, red_type_nb_x);
        tmp_nb_of_red_type--;
        red_type_nb_x++;
        i++;
    }
    tmp_nb_of_red_type = get_nb_of_red_type(box, OUTFILE_STRONG);
    i = 0;
    while (tmp_nb_of_red_type > 0)
    {
        printf("                   word[%d] = "BLUE"%s\n"RESET_COLOR, i, (*box)->outfile_st_filenames[i]);
        tmp_nb_of_red_type--;
        i++;
    }
    printf("     02_boxes_rest.c - get_word_hrdc| "BLUE"char **heredoc_delimiters"RESET_COLOR" generated✅\n");
}

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
void get_word_outf_str_2(int start, int end, t_box **box, int red_type_nb_x)
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
    (*box)->outfile_ap_filenames[red_type_nb_x] = malloc(sizeof(char) * (len_delimiter + 1));
    (*box)->outfile_ap_filenames[red_type_nb_x][len_delimiter] = '\0';
    i = 0;
    while (len_delimiter > 0)
    {
        //printf(GREEN"yepejoxepe, heredoc_nb = %d, i = %d, keep_start_word = %d\n"RESET_COLOR, heredoc_nb, i, keep_start_word);
        (*box)->outfile_ap_filenames[red_type_nb_x][i] = (*box)->input_substr[keep_start_word];
        i++;
        keep_start_word++;
        len_delimiter--;
    }
    //printf(GREEN"done\n"RESET_COLOR);
}