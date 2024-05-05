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
    int x;

    tmp_nb_of_heredocs = (*box)->nb_of_heredocs;
    i = 0;
    x = 0;
    while (tmp_nb_of_heredocs > 0)
    {
        if ((*box)->dict_red_index_type[x][1] == HEREDOC)
        {
            (*arr_ind_heredoc)[i] = (*box)->dict_red_index_type[x][0];
            printf("x = %d, [0]_INDEX: %d   [1]_TYPE: %s\n", x, (*box)->dict_red_index_type[x][0], ft_enum_to_str((*box)->dict_red_index_type[x][1]));
            i++;
        }
        x++;
        tmp_nb_of_heredocs--;
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
    //printf("             start index = %d, end index = %d\n", start, end);
    while (start < end)
    {
        while (ft_isspace((*box)->input_substr[start]))
            start++;
        if (!ft_isspace((*box)->input_substr[start]))
            return (1); //something was found! a word that works as end delimiter! :)
    }
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

    printf(AQUAMARINE"    is_last_redir: let's check! "RESET_COLOR);
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
*   Calls is_last_redir to check wheteher if each heredoc is last redir or not.
*
*   Calls is_end_word with following parameters:
*       start: index position of heredoc + 2.
*       end: position of next redirección, or ft_strlen
*/
/*int check_end(int **arr_ind_heredoc, t_box **box)
{
    int nb_of_times_to_check; //por claridad
    int i;
    //int tmp_nb_of_redir;
    //int keep_tmp_nb_of_redir;
    int total_nb_of_redir;
    int index_arr_heredoc;
    int counter_end_delimiter;

    nb_of_times_to_check = (*box)->nb_of_heredocs; //all must have a word next to them
    total_nb_of_redir = (*box)->nb_of_redir;
    i = 0;
    index_arr_heredoc = 0;
    counter_end_delimiter = 0;
    printf(BLUE"LEN = %d\n"RESET_COLOR, (int)ft_strlen((*box)->input_substr));
    while (nb_of_times_to_check > 0)
    {
        printf(MAGENTA"índice en input_substr = %d\n"RESET_COLOR, (*arr_ind_heredoc)[index_arr_heredoc]);
        if (is_last_redir(box, (*arr_ind_heredoc)[index_arr_heredoc])) //sí es última redirección?¿ Le paso (box, índice del comienzo del heredoc). Va a checkear si hay más redirecciones en el dict
        {
            if ((*arr_ind_heredoc)[index_arr_heredoc] + 2 == (int)ft_strlen((*box)->input_substr)) //si en la posición de después de heredoc no hay espacios ni hay nada. Heredoc sí o sí son 2 posiciones
            {
                printf(GREEN"sí es last redir, no hay nada más\n"RESET_COLOR);
                printf("    CONCLUSIÓN - 0: NO tiene end_delimiter\n\n");
                break;
            }
            printf(GREEN"sí es last redir, hay más len\n"RESET_COLOR);
            if (has_end_last_check((*arr_ind_heredoc)[index_arr_heredoc] + 2, (int)ft_strlen((*box)->input_substr), box)) //end = ft_strlen(input_substr);
            {
                printf("    CONCLUSIÓN - 1: sí tiene end_delimiter\n\n");
                counter_end_delimiter++;
            }
            break;
        }
        printf(RED"no es last dir, dir. n.º %d\n"RESET_COLOR, index_arr_heredoc);
        if (has_end_last_check((*arr_ind_heredoc)[index_arr_heredoc] + 2, (*box)->dict_red_index_type[index_arr_heredoc + 1][0] - 1, box)) //si todavía hay más redirecciones --> end = posición de la próxima redirección
        {
            printf("    CONCLUSIÓN - 2: sí tiene end_delimiter\n\n");
            counter_end_delimiter++;
        }
        else
            printf("    CONCLUSIÓN - 3: NO tiene end_delimiter\n\n");   
        i++;
        nb_of_times_to_check--;
        index_arr_heredoc++;
    }
    if (counter_end_delimiter == nb_of_times_to_check)
        return (1);
    return (0);
}*/

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
    int total_nb_of_redir;
    
    printf(YELLOW"red_nb_x = %d\n"RESET_COLOR, red_nb_x);
    total_nb_of_redir = (*box)->nb_of_redir;
    if (is_last_redir(box, index_hrdc_in_substr))
    {
        if (index_hrdc_in_substr + 2 == (int)ft_strlen((*box)->input_substr)) //si en la posición de después de heredoc no hay espacios ni hay nada. Heredoc sí o sí son 2 posiciones
        {
            printf(GREEN"sí es last redir, no hay nada más\n"RESET_COLOR);
            printf("     CONCLUSIÓN - 0: NO tiene end_delimiter. Return:"BLUE" 0\n\n"RESET_COLOR);
            return (0);
        }
        printf(GREEN"sí es last redir, hay más len\n"RESET_COLOR);
        if (has_end_last_check(index_hrdc_in_substr + 2, (int)ft_strlen((*box)->input_substr), box)) //end = ft_strlen(input_substr);
        {
            printf("    CONCLUSIÓN - 1: sí tiene end_delimiter. Return:"BLUE" 1\n\n"RESET_COLOR);
            return (1);
        }
    }
    printf(RED"no es last redir\n"RESET_COLOR);
    printf("FROM (start) index_hrdc_in_substr + 2 = %d\n", index_hrdc_in_substr + 2);
    printf("TO (end) index of next redir - 1: %d\n", (*box)->dict_red_index_type[red_nb_x][0] - 1);
    if (has_end_last_check(index_hrdc_in_substr + 2, (*box)->dict_red_index_type[red_nb_x][0] - 1, box)) //si todavía hay más redirecciones --> end = posición de la próxima redirección
    {
        printf("    CONCLUSIÓN - 2: sí tiene end_delimiter. Return:"BLUE" 1\n\n"RESET_COLOR);
        return (1);
    }
    printf("    CONCLUSIÓN - 3: NO tiene end_delimiter. Return:"BLUE" 0\n\n"RESET_COLOR);
    return (0);
}

/*get_end_arr: Informes arr_end variable: filled with 0 and 1.
*      1: YES end delimiter
*      0: NO end delimiter
*
* Variables:
*       int *arr_ind_heredoc: specific array which contains indexes of
*                             total heredocs found along input_substr.
*                             (based on nb_of_heredocs).
*
*/
void get_end_arr(int **arr_end, t_box **box, int *arr_ind_heredoc)
{
    int tmp_nb_of_heredocs;
    int i;
    int red_nb_x;
    int tmp_to_debug_nb_of_heredocs;
    //int tmp_to_debug_i;

    tmp_nb_of_heredocs = (*box)->nb_of_heredocs;
    tmp_to_debug_nb_of_heredocs = tmp_nb_of_heredocs;
    red_nb_x = 1; //empieza en 1 porque indica zenbagarrena. Gero konparaukou con el número total. Hemen behinguagaitxik ez gara 0tik hasten
    i = 0;
    while (tmp_nb_of_heredocs > 0)
    {
        (*arr_end)[i] = has_end_word(arr_ind_heredoc[i], box, red_nb_x);
        tmp_nb_of_heredocs--;
        red_nb_x++;
        i++;
    }
    /*printf(YELLOW"tmp_to_debug_nb_of_heredocs = %d\n", tmp_to_debug_nb_of_heredocs);
    tmp_to_debug_i = 0;
    while (tmp_to_debug_nb_of_heredocs > 0)
    {
        printf("end delimiter YES-NO[%d] = %d\n", tmp_to_debug_i, (*arr_end)[tmp_to_debug_i]);
        tmp_to_debug_nb_of_heredocs--;
    }*/
}


/*ft_check_end
*   Checks whether of 100% heredocs in substr do have
*   a end_indicator.
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
int ft_check_delimiter(t_box **box)
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
    printf(YELLOW"tmp_to_debug_nb_of_heredocs = %d\n", tmp_to_debug_nb_of_heredocs);
    while (tmp_to_debug_nb_of_heredocs > 0)
    {
        printf("end delimiter YES-NO[%d] = %d\n", tmp_to_debug_i, arr_end[tmp_to_debug_i]);
        tmp_to_debug_nb_of_heredocs--;
        tmp_to_debug_i++;
    }
    /*if (check_end(&arr_ind_heredoc, box))
    {
        printf(BLUE"yes end delimiter was found\n"RESET_COLOR);
        return (1);
    }
    printf("NO, end delimiter was not found\n");*/
    return (0);
}

/*void ft_is_heredoc(t_box **box)
{
    int tmp_nb_of_redir;
    int counter_heredoc;
    int i;
    int *arr_index_heredoc; //por claridad en el código

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
    arr_index_heredoc = malloc(sizeof(int) * counter_heredoc);
    if (!arr_index_heredoc)
        ft_puterror_exit("malloc error\n");
    i = 0;
    //guardar sus índices en un arr particular (por claridad en código y arreglar fácil de manera visual los posibles errores)
    while (counter_heredoc > 0)
    {
        if ((*box)->dict_red_index_type[i][1] == HEREDOC)
            arr_index_heredoc[i] = (*box)->dict_red_index_type[i][0]; //almacenar índices de heredoc
        i++;
        counter_heredoc--;
    }
    //checkear que todos tienen el end_final (palabra a la derecha). Si no, llora
    //¿en qué posiciones están los heredoc? para buscar comando de start a end
}*/

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
    if (!ft_check_delimiter(box)) 
        ft_puterror_exit("syntax error near unexpected token `newline'\n");
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