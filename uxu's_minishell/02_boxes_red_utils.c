/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   02_boxes_red_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uxmancis <uxmancis@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 19:25:19 by uxmancis          #+#    #+#             */
/*   Updated: 2024/05/11 21:39:59 by uxmancis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//Pretends to be the single functions used for all redirections to check content (first word)
//after redirección.

//First, we'll copy the heredoc functions.
//Then, we'll try using them calling them both from heredoc, but also from other redir types.
//If successful, we'll delete previous specific functions for heredoc


/*get_nb_of_red_type
*
*   Gets e_red_type as input: HEREDOC / INFILE / OUTFILE_APPEND / OUTFILE_STRONG
*
*   Returns: counter, total number of redirecciones found of specified
*            type in dict_red_index_type (box). 
*/
int get_nb_of_red_type(t_box **box, t_red_type red_type)
{
    int tmp_nb_of_redir;
    int i;
    int counter;

    tmp_nb_of_redir = (*box)->nb_of_redir;
    i = 0;
    while (tmp_nb_of_redir > 0)
    {
        if ((*box)->dict_red_index_type[i][1] == (int)red_type)
            counter++;
        tmp_nb_of_redir--;
    }
    return (counter);
}

/* get_specif_index_red
*
*   Informs arr_ind_red_type variable.
*
*   arr_ind_red_type: stores indexes of red type specified (e_red_type).
*                     Len of array = number of redirecciones found of specified type (e_red_type).
*/
void get_specif_index_red(int **arr_ind_red_type, t_box **box, t_red_type red_type)
{
    int tmp_nb_of_red;
    int i;
    int x; //ze indice-tan gordeta dauan redirekziñua. Es decir, se trata de la redirección en dict_red_index_type[0], o la [1], [2], ...

    tmp_nb_of_red = get_nb_of_red_type(box, red_type);
    i = 0;
    x = 0;
    //printf(MAGENTA"nb_of_heredocs = %d\n"RESET_COLOR, tmp_nb_of_heredocs);
    while (tmp_nb_of_red > 0)
    {
        //printf(YELLOW"dict_red_index_type[%d][1] = %s\n"RESET_COLOR, x, ft_enum_to_str((*box)->dict_red_index_type[x][1]));
        if ((*box)->dict_red_index_type[x][1] == (int)red_type)
        {
            //printf("YES HEREDOC WAS FOUND, x = %d\n", x);
            (*arr_ind_red_type)[i] = (*box)->dict_red_index_type[x][0];
            //printf("x = %d, [0]_INDEX: %d   [1]_TYPE: %s\n", x, (*box)->dict_red_index_type[x][0], ft_enum_to_str((*box)->dict_red_index_type[x][1]));
            i++;
        }
        x++;
        tmp_nb_of_red--;
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

/*get_word_red: Informes arr_word_yes_no variable: filled with 0 and 1.
*      1: YES word was found
*      0: NO word was found
*
* Variables:
*       int *arr_ind_red_type: specific array which contains indexes of
*                             total redireccioness found along input_substr of
*                             specified red type (e_red_type):
*/
void get_word_red(int **arr_word_yes_no, t_box **box, int *arr_ind_red_type, t_red_type red_type)
{
    int tmp_nb_of_red_type;
    int i;
    //int ind_red_total; //ze posiziñotan dauan redirekziñua en dict_red_index_type --> ezta bihar ya, soluzionatzen dou get_ind-ekin
    //int tmp_to_debug_nb_of_heredocs;
    //int tmp_to_debug_i;

    tmp_nb_of_red_type = get_nb_of_red_type(box, red_type);
    //tmp_to_debug_nb_of_heredocs = tmp_nb_of_heredocs;
    //red_nb_x = 1; //empieza en 1 porque indica zenbagarrena. Gero konparaukou con el número total. Hemen behinguagaitxik ez gara 0tik hasten. Uste dot hau obsoleto gelditxu dala.
    i = 0;
    //ind_red_total = 0;
    while (tmp_nb_of_red_type > 0)
    {
        /*if ((*box)->dict_red_index_type[ind_red_total][1] == HEREDOC)
        {*/
        (*arr_word_yes_no)[i] = has_end_word(arr_ind_red_type[i], box, get_ind(arr_ind_red_type[i], box));
        tmp_nb_of_red_type--;
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

/*are_all_delimiters
*
*   e_red_type specifies type of redirección to be analysed:
*       HEREDOC / INFILE / OUTFILE_APPEND / OUTFILE_STRONG  
*
*   Returns:
*       1 - YES all red_type specified have word next to them
*       0 - NO, redirección was found with no word next to it
*/
int are_all_delimiters(int *arr_word_yes_no, t_box **box, t_red_type red_type)
{
    int tmp_nb_of_red_type;
    int i;

    tmp_nb_of_red_type = get_nb_of_red_type(box, red_type);
    i = 0;
    while (tmp_nb_of_red_type > 0)
    {
        //printf("arr_end[%d] = %d\n", i, arr_end[i]);
        if (arr_word_yes_no[i] == 0)
        {
            //printf("NO DELIMITER, heredoc [%d]\n", i);
            return (0);
        }
        tmp_nb_of_red_type--;
        i++;
    }
    //printf("ALL HEREDOCS HAVE DELIMITER :)\n");
    return (1);
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
    
    printf("     02_boxes_rest.c - get_delimiters| Let's go get "BLUE"delimiter words"RESET_COLOR"! :)\n");
    //tmp_nb_of_red_type = get_nb_of_red_type(box, red_type);
    if ((int)red_type == HEREDOC)
        get_word_hrdc_1(box, arr_ind_red_type);
    else if ((int)red_type == INFILE)
        get_word_infile_1(box, arr_ind_red_type);
    else if ((int)red_type == OUTFILE_APPEND)
        get_word_outf_app_1(box, arr_ind_red_type);
    else if ((int)red_type == OUTFILE_STRONG)
        get_word_outf_str_1(box, arr_ind_red_type);
    
    /*(*box)->heredoc_delimiters = malloc(sizeof(char *)*(*box)->nb_of_heredocs);
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
*/
}

/*ft_check_first_word
*   Checks whether of 100% redirecciones in substr do have
*   a word after them. If redirección with no delimiter is found, 
*   error message is printed and program finishes its execution.
*
*   Variables:
*       int *arr_ind_red_type: specific array which stores specific indexes of
*                              specified e_red_type.
*                              E.g. if HEREDOCS are going to be analysed, array
*                                   will store indexes of HEREDOCS. If another type
*                                   of redirección is asked for (e_red_type), the
*                                   corresponding indexes will be stored.
*   
*       int *arr_word_yes_no: array which len is number of redirecciones of X type.
*                     In each position stores 1 or 0, depending
*                     on if redirección has a word after it or not.
*
*/
void ft_check_first_word(t_box **box, t_red_type red_type)
{
    int *specif_arr_ind_red_type; //por claridad en el código
    int *arr_word_yes_no;
    int tmp_to_debug_nb_of_red_type;
    int tmp_to_debug_i;
    int nb_of_red_type;
    //printf(GREEN"NB_OF_HEREDOCS = %d\n"RESET_COLOR, (*box)->nb_of_heredocs);
    
    nb_of_red_type = get_nb_of_red_type(box, red_type);
    specif_arr_ind_red_type = malloc(sizeof(int) * nb_of_red_type);
    if (!specif_arr_ind_red_type)
        ft_puterror_exit ("malloc error\n");
    get_specif_index_red(&specif_arr_ind_red_type, box, red_type);
    arr_word_yes_no = malloc(sizeof(int) * nb_of_red_type);
    get_word_red(&arr_word_yes_no, box, specif_arr_ind_red_type, red_type);
    tmp_to_debug_nb_of_red_type = nb_of_red_type;
    tmp_to_debug_i = 0;
    //printf(YELLOW"tmp_to_debug_nb_of_heredocs = %d\n", tmp_to_debug_nb_of_heredocs);
    while (tmp_to_debug_nb_of_red_type > 0)
    {
        printf("                   HEREDOC delimiter YES-NO[%d] = "BLUE"%d\n"RESET_COLOR, tmp_to_debug_i, arr_word_yes_no[tmp_to_debug_i]);
        tmp_to_debug_nb_of_red_type--;
        tmp_to_debug_i++;
    }
    if (!are_all_delimiters(arr_word_yes_no, box, red_type))
        ft_puterror_exit("syntax error near unexpected token `<<'\n");
    get_delimiters(specif_arr_ind_red_type, box);
}