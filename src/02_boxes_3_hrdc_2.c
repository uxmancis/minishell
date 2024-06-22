/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   02_boxes_3_hrdc_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uxmancis <uxmancis@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 14:33:15 by uxmancis          #+#    #+#             */
/*   Updated: 2024/05/19 15:10:58 by uxmancis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../inc/minishell.h"

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
*   Receives as parameter redir_ind_in_substr: position of redirección in
*   input_substr.
*
*   Returns:
*       Success: corresponding position's content of varibale
*   int     **dict_red_index_type[x][0].
*       -1: Failure (not expected) in any case.
*
*   How? Based on int redir_ind_in_substr identifies which redirección are we
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