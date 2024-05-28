/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   02_boxes_red_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uxmancis <uxmancis@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 19:25:19 by uxmancis          #+#    #+#             */
/*   Updated: 2024/05/19 15:11:28 by uxmancis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../inc/minishell.h"

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
    //printf("nb_of_redir = %d\n", tmp_nb_of_redir);
    i = 0;
    counter = 0;
    while (tmp_nb_of_redir > 0)
    {
        if ((*box)->dict_red_index_type[i][1] == (int)red_type)
            counter++;
        tmp_nb_of_redir--;
        i++;
    }
    //printf(GREEN"get_nb_of_red_type (red_type = %s)| counter = %d\n"RESET_COLOR, ft_enum_to_str(red_type), counter);
    return (counter);
}

/* get_specif_index_red
*
*   Informs specif_arr_ind_red_type.
*
*   specif_arr_ind_red_type: stores indexes of red_type specified.
*                     Len of array = number of redirecciones found of specified type (red_type).
*/
void get_specif_index_red(int **arr_ind_red_type, t_box **box, t_red_type red_type)
{
    int tmp_nb_of_red_type;
    int i;
    int x; //ze indice-tan gordeta dauan redirekziñua. Es decir, se trata de la redirección en dict_red_index_type[0], o la [1], [2], ...

    tmp_nb_of_red_type = get_nb_of_red_type(box, red_type);
    i = 0;
    x = 0;
    //printf(MAGENTA"red_type = %s, tmp_nb_of_red = %d\n"RESET_COLOR, ft_enum_to_str(red_type), tmp_nb_of_red_type);
    while (tmp_nb_of_red_type > 0)
    {
        //printf(YELLOW"dict_red_index_type[%d][1] = %s\n"RESET_COLOR, x, ft_enum_to_str((*box)->dict_red_index_type[x][1]));
        if ((*box)->dict_red_index_type[x][1] == (int)red_type)
        {
            //printf("YES RED_TYPE (%s) WAS FOUND, x = %d\n", ft_enum_to_str(red_type), x);
            (*arr_ind_red_type)[i] = (*box)->dict_red_index_type[x][0];
            //printf("x = %d, [0]_INDEX: %d   [1]_TYPE: %s\n", x, (*box)->dict_red_index_type[x][0], ft_enum_to_str((*box)->dict_red_index_type[x][1]));
            i++;
            tmp_nb_of_red_type--;
        }
        x++;
        //printf(BLUE"BAI: x = %d, tmp_nb_of_heredocs = %d\n"RESET_COLOR, x, tmp_nb_of_red_type);
    }
    //para comprobaciones:
    tmp_nb_of_red_type = get_nb_of_red_type(box, red_type);
    i = 0;
    while (tmp_nb_of_red_type > 0)
    {
        //printf(MAGENTA"arr_ind_red_type[%d] = %d\n"RESET_COLOR, i, (*arr_ind_red_type)[i]);
        tmp_nb_of_red_type--;
        i++;
    }
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
void is_word_red(int **arr_word_yes_no, t_box **box, int *arr_ind_red_type, t_red_type red_type)
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
        //printf("i = %d\n", i);
        (*arr_word_yes_no)[i] = has_end_word(arr_ind_red_type[i], box, get_ind(arr_ind_red_type[i], box));
        //printf("arr_word_yes_no[%d] = %d\n", i, (*arr_word_yes_no)[i]);
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
        //printf(GREEN"arr_end[%d] = %d\n"RESET_COLOR, i, arr_word_yes_no[i]);
        if (arr_word_yes_no[i] == 0)
        {
            //printf("NO DELIMITER, heredoc [%d]\n", i);
            return (0);
        }
        tmp_nb_of_red_type--;
        i++;
    }
    //printf("ALL REDIRS HAVE DELIMITER :)\n");
    return (1);
}

/*ft_check_first_word
*   Checks whether of 100% redirecciones in substr do have
*   a word after them. 
*
*       HEREDOC || INFILE: If redirección with no delimiter is found, 
*   error message is printed and program finishes its execution.
*
*       get_word_mgmt: gets first words to work as
*               HEREDOC: end delimiter word
*               INFILE: infile filename
*               OUTFILE (strong or append): outfile filename
*
*   Variables:
*       int *specif_arr_ind_red_type: specific array which stores specific indexes of
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
    //printf(YELLOW"\n     >> ft_check_first_word| red_type = %s, nb_of_red_type = %d\n"RESET_COLOR, ft_enum_to_str(red_type), nb_of_red_type);
    specif_arr_ind_red_type = malloc(sizeof(int) * nb_of_red_type);
    if (!specif_arr_ind_red_type)
        ft_puterror_exit ("malloc error\n");
    get_specif_index_red(&specif_arr_ind_red_type, box, red_type);
    arr_word_yes_no = malloc(sizeof(int) * nb_of_red_type);
    is_word_red(&arr_word_yes_no, box, specif_arr_ind_red_type, red_type);
    tmp_to_debug_nb_of_red_type = nb_of_red_type;
    tmp_to_debug_i = 0;
    //printf(YELLOW"tmp_to_debug_nb_of_red_type = %d\n"RESET_COLOR, tmp_to_debug_nb_of_red_type);
    while (tmp_to_debug_nb_of_red_type > 0)
    {
        printf("           is WORD after red_type? YES-NO[%d] = "BLUE"%d\n"RESET_COLOR, tmp_to_debug_i, arr_word_yes_no[tmp_to_debug_i]);
        tmp_to_debug_nb_of_red_type--;
        tmp_to_debug_i++;
    }
    //printf("hellowis\n");
    if (!are_all_delimiters(arr_word_yes_no, box, red_type))
    {
        printf("dentro, red_type = %s\n", ft_enum_to_str(red_type));
        if (red_type == HEREDOC)
            ft_puterror_exit("syntax error near unexpected token `<<'\n");
        if (red_type == INFILE)
            ft_puterror_exit("syntax error near unexpected token `<'\n");
        if (red_type == OUTFILE_APPEND)
            ft_puterror_exit("syntax error near unexpected token `>>'\n");
        if (red_type == OUTFILE_STRONG)
            ft_puterror_exit("syntax error near unexpected token `>'\n");
    }
    get_word_mgmt(specif_arr_ind_red_type, box, red_type);
}