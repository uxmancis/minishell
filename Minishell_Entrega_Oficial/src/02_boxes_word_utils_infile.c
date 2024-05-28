/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   02_boxes_word_utils_infile.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uxmancis <uxmancis@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 21:10:19 by uxmancis          #+#    #+#             */
/*   Updated: 2024/05/19 15:11:34 by uxmancis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../inc/minishell.h"

void get_word_infile_1(t_box **box, int *arr_ind_red_type)
{
    int tmp_nb_of_red_type;
    int keep_nb_of_red_type;
    int total_red_nb_x; //zenbagarrena dan --> index en dict_red_index_type (bebai ahal da lortu con get_in)
    int red_type_nb_x; //zenbagarrena en el particularmente entre este tipo de red. Utiilizado para ubicación en words_infile[n] (words_hrdc, el que sea)
    int i;

    tmp_nb_of_red_type = get_nb_of_red_type(box, INFILE);
    keep_nb_of_red_type = tmp_nb_of_red_type;
    //printf("tmp_nb_of_red_type = %d\n", tmp_nb_of_red_type);
    (*box)->words_infile = malloc(sizeof(char *) * tmp_nb_of_red_type);
    red_type_nb_x = 0;
    i = 0;
    total_red_nb_x = 0;
    //printf("nb_of_infiles = %d\n", tmp_nb_of_red_type);
    //printf("               get_word_infile_1\n");
    while (tmp_nb_of_red_type > 0)
    {
        // if (is_last_redir(box, arr_ind_red_type[i]))
        // if (is_last_redir(box, (*box)->dict_red_index_type[total_red_nb_x][0]))
        if (is_last_redir(box, arr_ind_red_type[i])/* || i == (keep_nb_of_red_type - 1)*/) //es decir, igual no es la úlltima redir de todas, pero sí es la última de su tipo. Incorrecto. SOlo quiero que entre aquí si se trata de la última de todas. Si es la última de su tipo, tengo que hacer que salga de otra manera
        {
            //printf(GREEN"yes is last redir of total i = %d, no more redirs\n"RESET_COLOR, i);
            // printf("total_red_nb_x = %d\n", total_red_nb_x);
            if ((*box)->dict_red_index_type[get_ind(arr_ind_red_type[i], box)][1] == INFILE)
                get_word_infile_2(arr_ind_red_type[red_type_nb_x] + 1, (int)ft_strlen((*box)->input_substr) - 1, box, red_type_nb_x);
            break;
        }
        //printf(GREEN"i = %d, keep_nb_of_red_type = %d\n"RESET_COLOR, i, keep_nb_of_red_type);
        //printf(MAGENTA"still more redirs after, i = %d\n"RESET_COLOR, i);
        //printf("red_type_nb_x = %d, arr_ind_red_type[%d] = %d\n", red_type_nb_x, red_type_nb_x, arr_ind_red_type[red_type_nb_x]);
        //printf("red_type_nb_x = %d\n", red_type_nb_x);
        //printf("total_red_nb_x = %d\n", total_red_nb_x);
        //printf("dict_red_index_type[%d][1] == %s\n", total_red_nb_x, ft_enum_to_str((*box)->dict_red_index_type[total_red_nb_x][1]));
        if ((*box)->dict_red_index_type[total_red_nb_x][1] == INFILE)
        {
            //printf(GREEN"bai, coincide\n"RESET_COLOR);
            get_word_infile_2(arr_ind_red_type[red_type_nb_x] + 1, (*box)->dict_red_index_type[total_red_nb_x + 1][0] - 1, box, red_type_nb_x);
            tmp_nb_of_red_type--;
            red_type_nb_x++;
            i++; //solo si sí coincide hacemos i++, para hacer referencia a la próxima redir
        }
        else
            //printf(RED"no coincide\n"RESET_COLOR);
        if (i == keep_nb_of_red_type) //si es la última de su tipo. Habremos hecho ya i++ cuando sí ha coincidido
        {
            //printf(RED"salimos de aquí por última redir de su tipo, no necesitamos más words\n"RESET_COLOR);
            break;//salte de aquí, ya has hecho tu trabajo
        }
        total_red_nb_x++;
    }
    tmp_nb_of_red_type = get_nb_of_red_type(box, INFILE);
    //printf("               tmp_nb_of_red_type = %d\n", tmp_nb_of_red_type);
    i = 0;
    while (tmp_nb_of_red_type > 0)
    {
        printf("                   word[%d] = ["BLUE"%s"RESET_COLOR"]\n", i, (*box)->words_infile[i]);
        tmp_nb_of_red_type--;
        i++;
    }
    printf("     02_boxes_rest.c - get_word_hrdc| "BLUE"char **words_infile"RESET_COLOR" generated✅\n");
    printf("     -----------------------------------------------\n\n");
}


/* 
*   Puts each word in corresponding space inside 
*   char **words_infile variable (box structure).
*
*   This get_word function will be called nb_of_red_type times.
*
*   Simply gets first word and ignores rest of possible words
*   that might exist after it. It doesn't care whether if there is
*   a single word or not between redirecciones.
*
*/
void get_word_infile_2(int start, int end, t_box **box, int red_type_nb_x)
{
    int len_delimiter;
    int keep_start_word;
    int i;

    //printf("get_word\n");
    printf(BLUE"               get_word_infile_2: start = %d, end = %d, heredoc_nb = %d\n"RESET_COLOR, start, end, red_type_nb_x);
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
    (*box)->words_infile[red_type_nb_x] = malloc(sizeof(char) * (len_delimiter + 1));
    (*box)->words_infile[red_type_nb_x][len_delimiter] = '\0';
    i = 0;
    while (len_delimiter > 0)
    {
        //printf(GREEN"yepejoxepe, heredoc_nb = %d, i = %d, keep_start_word = %d\n"RESET_COLOR, red_type_nb_x, i, keep_start_word);
        (*box)->words_infile[red_type_nb_x][i] = (*box)->input_substr[keep_start_word];
        i++;
        keep_start_word++;
        len_delimiter--;
    }
    //printf(GREEN"done\n"RESET_COLOR);
}