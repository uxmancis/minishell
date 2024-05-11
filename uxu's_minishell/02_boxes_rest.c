/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   02_boxes_rest.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uxmancis <uxmancis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 16:32:24 by uxmancis          #+#    #+#             */
/*   Updated: 2024/05/05 17:15:47 by uxmancis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int ft_get_numof_heredocs(t_box **box)
{
    int tmp_nb_of_redir;
    int counter_heredoc;
    int i;
    //int *arr_index_heredoc; //por claridad en el código

    tmp_nb_of_redir = (*box)->nb_of_redir;
    counter_heredoc = 0;
    i = 0;
    //contar cuántos heredocs tenemos
    while (tmp_nb_of_redir > 0)
    {
        if ((*box)->dict_red_index_type[i][1] == HEREDOC)
            counter_heredoc++; //número de heredocs
        i++;
        tmp_nb_of_redir--;
    }
    //printf("counter_heredoc = %d\n", counter_heredoc);
    return (counter_heredoc);
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
            return (1); //something was found! a word that works as end delimiter! :)
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
int is_last_redir(t_box **box, int index_current_heredoc)
{
    int tmp_total_nb_of_redir; //por claridad y para no cambiarle el valor el original
    int redir_position; //zenbagarrena da? --> hau azkenian counter_position-ek esango nuke eitxen dabela
    int counter_position; //podría haber sido i (sobre el que iteramos), es por mejorar la comprensión

    //printf(AQUAMARINE"    is_last_redir: let's check! "RESET_COLOR);
    tmp_total_nb_of_redir = (*box)->nb_of_redir;
    counter_position = 1; //lo vamos a comparar con el número total de redirecciones
    redir_position = 0;
    //printf("\n        total nb of redir: %d\n", (*box)->nb_of_redir);
    //printf("        index_current_heredoc: %d\n", index_current_heredoc);
    while (tmp_total_nb_of_redir > 0)
    {
        //printf("                counter_position: %d\n", counter_position);
        if (index_current_heredoc == (*box)->dict_red_index_type[redir_position][0])
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
int has_end_word(int index_hrdc_in_substr, t_box **box, int red_nb_x)
{
    //int total_nb_of_redir;
    
    //printf(GREEN">>> has_end_word: index_hrdc_in_substr = %d, red_nb_x = %d\n"RESET_COLOR, index_hrdc_in_substr, red_nb_x);
    //total_nb_of_redir = (*box)->nb_of_redir;
    if (is_last_redir(box, index_hrdc_in_substr))
    {
        if (index_hrdc_in_substr + 2 == (int)ft_strlen((*box)->input_substr)) //si en la posición de después de heredoc no hay espacios ni hay nada. Heredoc sí o sí son 2 posiciones
        {
            //printf(GREEN"sí es last redir, no hay nada más\n"RESET_COLOR);
            //printf("     CONCLUSIÓN - 0: NO tiene end_delimiter. Return:"BLUE" 0\n\n"RESET_COLOR);
            return (0);
        }
        //printf(GREEN"sí es last redir, hay más len\n"RESET_COLOR);
        if (has_end_last_check(index_hrdc_in_substr + 2, (int)ft_strlen((*box)->input_substr), box)) //end = ft_strlen(input_substr);
        {
            //printf("    CONCLUSIÓN - 1: sí tiene end_delimiter. Return:"BLUE" 1\n\n"RESET_COLOR);
            return (1);
        }
    }
    //cuando todavía sí hay alguna otra redirección posterior
    //printf(RED"no es last redir, index_hrdc_in_substr = %d\n"RESET_COLOR, index_hrdc_in_substr);
    //printf("FROM (start) index_hrdc_in_substr + 2 = %d\n", index_hrdc_in_substr + 2);
    //printf(MAGENTA"red_nb_x = %d\n"RESET_COLOR, red_nb_x);
    //printf("TO (end) index of next redir - 1: %d\n", (*box)->dict_red_index_type[red_nb_x + 1][0] - 1);
    if (has_end_last_check(index_hrdc_in_substr + 2, (*box)->dict_red_index_type[red_nb_x + 1][0] - 1, box)) //si todavía hay más redirecciones --> end = posición de la próxima redirección
    {
        //printf("    CONCLUSIÓN - 2: sí tiene end_delimiter. Return:"BLUE" 1\n\n"RESET_COLOR);
        return (1);
    }
    //printf("    CONCLUSIÓN - 3: NO tiene end_delimiter. Return:"BLUE" 0\n\n"RESET_COLOR);
    return (0);
}

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
int get_ind (int hrdc_ind_in_substr, t_box **box)
{
    int tmp_nb_of_redir;
    int x;

    tmp_nb_of_redir = (*box)->nb_of_redir;
    x = 0;
    while (tmp_nb_of_redir > 0)
    {
        if ((*box)->dict_red_index_type[x][0] == hrdc_ind_in_substr)
            return (x);
        tmp_nb_of_redir--;
        x++;
    }
    return (-1);
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

/*
*   Returns:
*       1 - YES all heredocs have delimiter
*       0 - NO, heredoc was found with no delimiter
*/
int are_all_delimiters(int *arr_end, t_box **box)
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
void get_word(int start/*, int end, */,t_box **box, int heredoc_nb)
{
    int len_delimiter;
    int keep_start_word;
    int i;

    printf("get_word\n");
    printf(BLUE"start = %d, heredoc_nb = %d\n"RESET_COLOR, start, heredoc_nb);
    len_delimiter = 0;
    while (ft_isspace((*box)->input_substr[start]))
        start++;
    keep_start_word = start;
    //rintf("start = %d\n", start);
    while(!ft_isspace((*box)->input_substr[start])/* && start < end*/)
    {
        start++;
        len_delimiter++;
    }
    //printf("len_delimiter = %d\n", len_delimiter);
    (*box)->heredoc_delimiters[heredoc_nb] = malloc(sizeof(char) * (len_delimiter + 1));
    (*box)->heredoc_delimiters[heredoc_nb][len_delimiter] = '\0';
    i = 0;
    while (len_delimiter > 0)
    {
        //printf(GREEN"yepejoxepe, heredoc_nb = %d, i = %d, keep_start_word = %d\n"RESET_COLOR, heredoc_nb, i, keep_start_word);
        (*box)->heredoc_delimiters[heredoc_nb][i] = (*box)->input_substr[keep_start_word];
        i++;
        keep_start_word++;
        len_delimiter--;
    }
}

/* get_delimiters
*
*   Function called when 100% of heredocs do have a delimiter.
*   
*   Gets delimiter words and puts them in char **heredoc_delimiters
*   variable in box structure.
*/
void get_delimiters(int *arr_ind_heredoc, t_box **box)
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
        get_word(arr_ind_heredoc[i] + 2, box, heredoc_nb);
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
}

/*ft_check_end
*   Checks whether of 100% heredocs in substr do have
*   a end_indicator. If heredoc with no delimiter is found, 
*   error message is printed and program finishes its execution.
*
*   Variables:
*       int *arr_end: array which len is number of heredocs.
*                     In each position stores 1 or 0, depending
*                     on if heredocs have end delimiter or not.
*
*       Returns:
*           1: YES, 100% heredocs have a end delimiter
*           0: NO, at least 1 heredoc identified with no end delimiter
*/
void ft_check_delimiter(t_box **box)
{
    int *arr_ind_heredoc; //por claridad en el código
    int *arr_end;
    int tmp_to_debug_nb_of_heredocs;
    int tmp_to_debug_i;
    //printf(GREEN"NB_OF_HEREDOCS = %d\n"RESET_COLOR, (*box)->nb_of_heredocs);
    arr_ind_heredoc = malloc(sizeof(int) * (*box)->nb_of_heredocs);
    if (!arr_ind_heredoc)
        ft_puterror_exit ("malloc error\n");
    get_arr_heredoc(&arr_ind_heredoc, box);
    arr_end = malloc(sizeof(int) * (*box)->nb_of_heredocs);
    get_end_arr(&arr_end, box, arr_ind_heredoc);
    tmp_to_debug_nb_of_heredocs = (*box)->nb_of_heredocs;
    tmp_to_debug_i = 0;
    //printf(YELLOW"tmp_to_debug_nb_of_heredocs = %d\n", tmp_to_debug_nb_of_heredocs);
    while (tmp_to_debug_nb_of_heredocs > 0)
    {
        printf("                   HEREDOC delimiter YES-NO[%d] = "BLUE"%d\n"RESET_COLOR, tmp_to_debug_i, arr_end[tmp_to_debug_i]);
        tmp_to_debug_nb_of_heredocs--;
        tmp_to_debug_i++;
    }
    if (!are_all_delimiters(arr_end, box))
        ft_puterror_exit("syntax error near unexpected token `<<'\n");
    get_delimiters(arr_ind_heredoc, box);
}


//checkear que todos tienen el end_final (palabra a la derecha). Si no, llora --> falso rick
//¿en qué posiciones están los heredoc? para buscar comando de start a end


/* ft_heredocs
*       Checks whether if 100% heredocs have end delimiter.
*       
*       If heredocs is found with no end delimiter, then error message is printed
+       and minishell program finishes its execution.
*/
void ft_heredocs(t_box **box)
{
    (*box)->nb_of_heredocs = ft_get_numof_heredocs(box);
    printf("     02_boxes.c - ft_heredocs| numof_heredocs = "BLUE"%d\n"RESET_COLOR, (*box)->nb_of_heredocs);
    printf("              do heredocs have" BLUE" delimiter"RESET_COLOR"? yes[1] / no[0]\n");
    ft_check_delimiter(box); //if 1 heredoc has no delimiter, program finishes
    //printf(MAGENTA"<<<<<<<<<<<<    check_delimiter completed     >>>>>>>>>>>>>\n"RESET_COLOR);
}

void get_rest (t_box *box)
{
    printf(GREEN"02_boxes_rest.c | get_rest\n"RESET_COLOR);
    //box->nb_of_heredocs = ft_get_numof_heredocs(box);
    //printf("GET REST | nb_of_heredocs = %d\n", box->nb_of_heredocs);
    //box->nb_of_heredocs = ft_get_numof_heredocs(box);
    ft_heredocs(&box);
    //box->nb_of_heredocs = 
    //printf("nb_of_heredocs = %d\n", box->nb_of_heredocs);
    //printf("     02_boxes.c - get_rw|"BLUE" dict_quotes"RESET_COLOR" generated✅\n");)
    //ft_is_heredoc(&box);
}