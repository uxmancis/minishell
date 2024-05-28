/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   02_boxes_utils_nav.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uxmancis <uxmancis@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 14:23:03 by uxmancis          #+#    #+#             */
/*   Updated: 2024/05/19 15:11:30 by uxmancis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../inc/minishell.h"

/*Contains following functions:
1. int has_end_last_check(int start, int end, t_box **box)
2. int is_last_redir(t_box **box, int index_current_heredoc)
3. int has_end_word(int index_hrdc_in_substr, t_box **box, int red_nb_x)
*/

/*is_end_word
*   Checks whether if any word is found between start
*   and end positions (index) in input_substr.
*
*   Returns:
*       1: YES, word was found (different to spaces and tabs)
*       0: NO, no word was found
*/
int has_end_last_check(int start, int end, t_box **box)
{
    //printf(MAGENTA"             start index = %d, end index = %d\n"RESET_COLOR, start, end);
    while (start < end)
    {
        while (ft_isspace((*box)->input_substr[start]))
            start++;
        if (!ft_isspace((*box)->input_substr[start]))
        {
            //printf("something was found!\n");
            return (1); //something was found! a word that works as end delimiter! :)
        }
    }
    //printf(YELLOW"               NO HAY PALABRA FINAL\n"RESET_COLOR);
    return (0);
}

/*Checks if current redirección is the last one or not.
*       Return: 
*           1: YES, last redir
*           0: NO, there are more redirs along input_substr
*
*   Parameters:
*       int index_current_heredoc: position (index) of current heredoc
*                                  in input_substr (t_box box)
*/
int is_last_redir(t_box **box, int index_current_redir)
{
    int tmp_total_nb_of_redir; //por claridad y para no cambiarle el valor el original
    int redir_position; //zenbagarrena da? --> hau azkenian counter_position-ek esango nuke eitxen dabela
    int counter_position; //podría haber sido i (sobre el que iteramos), es por mejorar la comprensión

    //printf(AQUAMARINE"    is_last_redir: let's check! "RESET_COLOR);
    tmp_total_nb_of_redir = (*box)->nb_of_redir;
    counter_position = 1; //lo vamos a comparar con el número total de redirecciones
    redir_position = 0;
    //printf("-        total nb of redir: %d", (*box)->nb_of_redir);
    //printf("        index_current_redir: %d    -", index_current_redir);
    while (tmp_total_nb_of_redir > 0)
    {
        //printf("                counter_position: %d\n", counter_position);
        if (index_current_redir == (*box)->dict_red_index_type[redir_position][0])
            break;
        tmp_total_nb_of_redir--;
        counter_position++;
        redir_position++;
    }
    //printf("counter_position = %d\n", counter_position);
    if (counter_position == (*box)->nb_of_redir)
    {
        //printf(GREEN"sí es last redir\n"RESET_COLOR);
        return (1);
    }
    //printf(RED"no es last redir\n"RESET_COLOR);
    return (0); 
}

/*  
*   Parameters:
*       index_hrdc_in_substr: index of heredoc in substr.
*       red_nb_x: redirección number X. Zenbagarren redirekziñua da.
*                 Adib.: baldin badare guztira Y redirekziño, hau da
*                        X.a
*
*   Returns:
*       1: YES has delimiter
*       0: NO no delimiter
*/
int has_end_word(int index_red_in_substr, t_box **box, int red_nb_x)
{
    //int total_nb_of_redir;
    
    //printf(GREEN">>> has_end_word: index_hrdc_in_substr = %d, red_nb_x = %d\n"RESET_COLOR, index_hrdc_in_substr, red_nb_x);
    //total_nb_of_redir = (*box)->nb_of_redir;
    if (is_last_redir(box, index_red_in_substr))
    {
        //printf("last redir here! :)\n");
        if (index_red_in_substr + 2 == (int)ft_strlen((*box)->input_substr)) //si en la posición de después de heredoc no hay espacios ni hay nada. Heredoc sí o sí son 2 posiciones
        {
            //printf(GREEN"sí es last redir, no hay nada más\n"RESET_COLOR);
            //printf("     CONCLUSIÓN - 0: NO tiene end_delimiter. Return:"BLUE" 0\n\n"RESET_COLOR);
            return (0);
        }
        //printf(GREEN"sí es last redir, hay más len\n"RESET_COLOR);
        if (has_end_last_check(index_red_in_substr + 2, (int)ft_strlen((*box)->input_substr), box)) //end = ft_strlen(input_substr);
        {
            //printf("    CONCLUSIÓN - 1: sí tiene end_delimiter. Return:"BLUE" 1\n\n"RESET_COLOR);
            return (1);
        }
        return (0); //cuando no es el caso del primer if, pero tampoco tiene word has_last_check=0
    }
    //cuando todavía sí hay alguna otra redirección posterior
    //printf(RED"no es last redir, index_hrdc_in_substr = %d\n"RESET_COLOR, index_hrdc_in_substr);
    //printf("FROM (start) index_hrdc_in_substr + 2 = %d\n", index_hrdc_in_substr + 2);
    //printf(MAGENTA"red_nb_x = %d\n"RESET_COLOR, red_nb_x);
    //printf("TO (end) index of next redir - 1: %d\n", (*box)->dict_red_index_type[red_nb_x + 1][0] - 1);
    if (has_end_last_check(index_red_in_substr + 2, (*box)->dict_red_index_type[red_nb_x + 1][0] - 1, box)) //si todavía hay más redirecciones --> end = posición de la próxima redirección
    {
        //printf("    CONCLUSIÓN - 2: sí tiene end_delimiter. Return:"BLUE" 1\n\n"RESET_COLOR);
        return (1);
    }
    //printf("    CONCLUSIÓN - 3: NO tiene end_delimiter. Return:"BLUE" 0\n\n"RESET_COLOR);
    return (0);
}

/* get_word_mgmt
*
*   Function called when 100% of heredocs do have a delimiter.
*   
*   Gets delimiter words and puts them in char **heredoc_delimiters
*   variable in box structure.
*/
void get_word_mgmt(int *arr_ind_red_type, t_box **box, t_red_type red_type)
{
    //int tmp_nb_of_red_type;
    //int i;
    //int heredoc_nb; //zenbagarren heredoc-a dan. Gero goiaz konparatzera en get_word con 
    
    //printf("     02_boxes_rest.c - get_word_mgmt| Let's go get "BLUE" words"RESET_COLOR" for red_type = "BLUE"%s! :)\n"RESET_COLOR, ft_enum_to_str(red_type));
    //tmp_nb_of_red_type = get_nb_of_red_type(box, red_type);
    if ((int)red_type == HEREDOC)
        get_word_hrdc_1(box, arr_ind_red_type);
    else if ((int)red_type == INFILE)
        get_word_infile_1(box, arr_ind_red_type);
    else if ((int)red_type == OUTFILE_APPEND)
        get_word_outf_app_1(box, arr_ind_red_type);
    else if ((int)red_type == OUTFILE_STRONG)
        get_word_outf_str_1(box, arr_ind_red_type);
}