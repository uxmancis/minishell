/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   02_boxes_6_cmd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uxmancis <uxmancis@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 10:46:55 by uxmancis          #+#    #+#             */
/*   Updated: 2024/05/18 16:25:54 by uxmancis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void mark_redir(t_box **box)
{
    int tmp_nb_of_redir; //=len dict_red_index_type
    int i;
    //int x;
    int current_ind_in_substr;
    //printf(GREEN"mark_redir\n"RESET_COLOR);
    //printf("     len dict_red_index_type = %d\n", (*box)->nb_of_redir);
    
    i = 0;
    //x = 0;
    tmp_nb_of_redir = (*box)->nb_of_redir;
    while (tmp_nb_of_redir > 0)
    {
        //printf("i = %d, dict_red_index_type[%d][1] = %s\n", i, i, ft_enum_to_str((*box)->dict_red_index_type[i][1]));
        if ((*box)->dict_red_index_type[i][1] == HEREDOC || (*box)->dict_red_index_type[i][1] == OUTFILE_APPEND) //Hay que marcar 2 posiciones como 'N'
        {
            //printf("barruan\n");
            current_ind_in_substr = (*box)->dict_red_index_type[i][0];
            (*box)->what_to_take[current_ind_in_substr] = 'R';
            (*box)->what_to_take[current_ind_in_substr + 1] = 'R';
            //printf("done\n");
        }
        else if((*box)->dict_red_index_type[i][1] == INFILE || (*box)->dict_red_index_type[i][1] == OUTFILE_STRONG) //Hay que marcar 1 posición como 'N'
        {
            current_ind_in_substr = (*box)->dict_red_index_type[i][0];
            (*box)->what_to_take[current_ind_in_substr] = 'R';
        }
        i++;
        tmp_nb_of_redir--;
        //printf("result: i = %d, tmp_nb_of_redir = %d\n", i, tmp_nb_of_redir);
    }
    //printf(GREEN"END mark_redir\n"RESET_COLOR);
}

void mark_word_2(int start, int end, t_box **box)
{
    int len_word;

    len_word = 0;
    //printf("mark_word_2: start = %d, end = %d\n", start, end);
    while (ft_isspace((*box)->input_substr[start]) && start <= end)
    {
        //printf("Before, start: %d\n", start);
        start++;
        //printf("After, start = %d\n", start);
    }
    while(!ft_isspace((*box)->input_substr[start]) && start <= end)
    {
        //printf("asignar 'W', posición %d\n", start);
        (*box)->what_to_take[start] = 'W';
        start++;
        len_word++;
        //printf("yes\n");
    }
    //printf("      mark_word_2: "GREEN"DONE!\n"RESET_COLOR);
}

/*is_last_redir_2
*
*   Compares nb_of_redirs with nb_redir_x.
*
*   Returns:
*       1: YES is last redirección
*       0: NO still more redirecciones in input_substr
*/
int is_last_redir_2(t_box **box, int nb_redir_x)
{
   // int tmp_nb_of_redir;

    //tmp_nb_of_redir = (*box)->nb_of_redir;
    //(void)box;
    //printf("     is_last_redir_2\n");
    //printf("     REDIR actual = posición: %d\n", ind_redir_in_substr);
    //printf("     REDIR actual = posición: %d, tipo: %s\n", ind_redir_in_substr, ft_enum_to_str((*box)->dict_red_index_type[nb_redir_x][1]));
    //printf("     REDIR actual = posición: %d, tipo: %s\n", ind_redir_in_substr, ft_enum_to_str((*box)->dict_red_index_type[ind_redir_in_substr][1]));
    //printf("     nb_of_redir = %d\n", tmp_nb_of_redir);
    if (nb_redir_x + 1 == (*box)->nb_of_redir)
    {
        //printf(GREEN"yes is last redir\n"RESET_COLOR);
        return (1);
    }
    //printf(RED"NO still more redirs\n"RESET_COLOR);
    return (0);
}

void mark_word(t_box **box)
{
    int tmp_nb_of_redir;
    int i;

    //printf("     mark_word\n");
    tmp_nb_of_redir = (*box)->nb_of_redir;
    i = 0;
    while (tmp_nb_of_redir > 0)
    {
        //printf("          redir n.º "MAGENTA"%d"RESET_COLOR" en dict_quotes de "MAGENTA"%d"RESET_COLOR" en total\n", i + 1, (*box)->nb_of_redir);
        //printf("          dict_redir_ind_type[%d] = %d\n", i, (*box)->dict_red_index_type[i][0]);
        if (is_last_redir_2(box, i)) //start: posición de redirección (+1 o +2), end: ft_strlen
        {
            //printf(GREEN"sí es última redirección. Particularmente:\n"RESET_COLOR);
            if ((*box)->dict_red_index_type[i][1] == HEREDOC || (*box)->dict_red_index_type[i][1] == OUTFILE_APPEND) //start: +2
            {
                //printf("   es HEREDOC o OUTFILE_APPEND\n");
                mark_word_2((*box)->dict_red_index_type[i][0] + 2, ft_strlen((*box)->input_substr) - 1, box);
            }
            else if (((*box)->dict_red_index_type[i][1] == INFILE || (*box)->dict_red_index_type[i][1] == OUTFILE_STRONG)) //start: +1
            {   
                //printf("   es INFILE o OUTFILE_STRONG\n");
                mark_word_2((*box)->dict_red_index_type[i][0] + 1, ft_strlen((*box)->input_substr) - 1, box);
                //printf("amaitxuta\n");
            }
            //printf(">listo\n");
            break;        
        }
        else //start: posición de redirección (+1 o +2), end: posición next redirección
        {
            //printf(RED"no es última redirección. Particularmente:\n"RESET_COLOR);
            if ((*box)->dict_red_index_type[i][1] == HEREDOC || (*box)->dict_red_index_type[i][1] == OUTFILE_APPEND) //start: +2
            {
                //printf("   es HEREDOC o OUTFILE_APPEND\n");
                mark_word_2((*box)->dict_red_index_type[i][0] + 2, (*box)->dict_red_index_type[i + 1][0] - 1, box);
            }
            else if (((*box)->dict_red_index_type[i][1] == INFILE || (*box)->dict_red_index_type[i][1] == OUTFILE_STRONG)) //start: +1
            {
                //printf("   es INFILE o OUTFILE_STRONG\n");
                mark_word_2((*box)->dict_red_index_type[i][0] + 1, (*box)->dict_red_index_type[i + 1][0] - 1, box);
                //printf("listo\n");
            }            
        }
        //printf(">>yes\n");
        tmp_nb_of_redir--;
        i++;
    }
    //printf("mark_word: "GREEN"DONE!\n"RESET_COLOR);
    //printf("hellohello\n");
    //mandar start_end
        //marcar word y volver al próximo
}

/*  init_what_to_take
*
*   Initializes char *what_to_take variable (box) with
*   'Y' value.
*
*   Y = YES to take as comand/argument.
*/
void init_what_to_take(t_box **box)
{
    int len;
    int i;

    i = 0;
    len = ft_strlen((*box)->what_to_take);
    while (len > 0)
    {
        (*box)->what_to_take[i] = 'Y';
        len--;
        i++;
    }
}

/*  ft_get_what_to_take
*
*   what_to_take variable will have the following info about
*   input_substr:
*
*       R: Redirección
*       W: Word (end delimiter, infile or outfile name. 1st word after redirección)
*       Y: YES take it as command and arguments to be analysed.
*/
void ft_get_what_to_take(t_box **box)
{
    int len;
    int i;
    
    (*box)->what_to_take = malloc(sizeof(char)*(ft_strlen((*box)->input_substr)+1));
    (*box)->what_to_take[ft_strlen((*box)->input_substr)] = '\0';
    init_what_to_take(box); //Everything initializes as 'Y'
    mark_redir(box);
    mark_word(box);
    //printf("hemen gare bueltan\n");
    //Result of_what_to_take:
    len = ft_strlen((*box)->input_substr);
    //len = ft_strlen((*box)->what_to_take); ns porq no funciona, baina bueno, me vale también input_substr porque tienen el mismo len
    i = 0;
    printf("     what_to_take: len = %d\n", len);
    while (len > 0)
    {
        printf("               what_to_take[%d] = %c\n", i, (*box)->what_to_take[i]);
        len--;
        i++;
    }
}

/*int get_len_only_needed(t_box **box)
{
    int counter;
    int len;
    int i;

    counter = 0;
    len = ft_strlen((*box)->input_substr);
    i = 0;
    while (len > 0)
    {
        if ((*box)->what_to_take[i] == 'Y')
            counter++;
        len++;
    }
    return (counter);
}*/

/*rest_numof_words
*
*   In char    **rest_info_potential_cmd variable (box) we will
*   store rest of info, where we will aim to find commands and arguments.
*
*   rest_numof_words will return the number of words we will find
*   along rest 'Y' marked info (in what_to_take).
*/
int rest_numof_words(t_box **box)
{
    int counter;
    int len;
    int i;
    int keep_len;

    //printf("rest_numof_words\n");
    len = ft_strlen((*box)->input_substr);
    keep_len = len;
    i = 0;
    counter = 0;
    //printf("keep_len = %d\n",keep_len);
    while (len > 0)
    {
        //printf(BLUE"i = %d, input_substr[%d] = %c\n"RESET_COLOR, i, i, (*box)->input_substr[i]);
        if ((*box)->what_to_take[i] == 'Y' && !ft_isspace((*box)->input_substr[i]))
        {
            //printf("               let's count! input_substr[%d] = %c               counter = %d\n", i, (*box)->input_substr[i], counter);
            counter++;
            //printf(GREEN"                     counter = %d\n"RESET_COLOR, counter);
            while (!ft_isspace((*box)->input_substr[i]) && i < keep_len)
            {
                i++;
                //printf("i = %d, input_substr[%d] = %c\n", i, i, (*box)->input_substr[i]);
            }
                
        }
        //printf("kanpuan, i = %d, keep_len = %d\n", i, keep_len);
        if (i == keep_len - 1 || i == keep_len) //fallotxuak zuzentzen, kasuistikak jeje
            break;
        len--;
        i++;
    }
    printf("               rest_numof_words | counter = %d\n", counter);
    return (counter);
}

/*rest_get_ind_beginning_words
*
*   It's almost the same function as rest_numof_words.
*
*   Difference: instead of using it to return number of words
*   (int     nb_of_words_rest in words), we'll use it to inform
*   following variable: int    *index_beginning_words_rest (box),
*   containing index of beginning of each of rest of words to be
*   afterwards copied in char    **rest_info_potential_cmd (box).
*
*/
void rest_get_ind_beginning_words(t_box **box)
{
    int len;
    int i;
    int keep_len;
    int x;

    
    (*box)->index_beginning_words_rest = malloc(sizeof(int) * (*box)->nb_of_words_rest);
    //printf("rest_numof_words\n");
    len = ft_strlen((*box)->input_substr);
    keep_len = len;
    i = 0;
    x = 0;
    //printf("keep_len = %d\n",keep_len);
    while (len > 0)
    {
        //printf(BLUE"i = %d, input_substr[%d] = %c\n"RESET_COLOR, i, i, (*box)->input_substr[i]);
        if ((*box)->what_to_take[i] == 'Y' && !ft_isspace((*box)->input_substr[i]))
        {
            //printf("               let's count! input_substr[%d] = %c               counter = %d\n", i, (*box)->input_substr[i], counter);
            (*box)->index_beginning_words_rest[x] = i;
            printf("                      index_beginning_words_rest[%d] = %d\n", x, (*box)->index_beginning_words_rest[x]);
            x++;
            //printf(GREEN"                     counter = %d\n"RESET_COLOR, counter);
            while (!ft_isspace((*box)->input_substr[i]) && i < keep_len)
            {
                i++;
                //printf("i = %d, input_substr[%d] = %c\n", i, i, (*box)->input_substr[i]);
            }
                
        }
        //printf("kanpuan\n");
        if (i == keep_len - 1 || i == keep_len)
            break;
        len--;
        i++;
    }
    //printf("rest_get_ind_beginning_words:"GREEN" DONE!\n"RESET_COLOR);
}

/*cpy_1_word
*
*   Variables:
*       nb_of_word: zenbagarren rest-eko hitza dan (posición en index_beginning_words_rest)
*/
void cpy_1_word(t_box **box, int nb_of_word)
{
    int len;
    int start;
    int keep_start;
    int x;

    //printf(YELLOW"cpy_1_word | nb_of_word = %d\n"RESET_COLOR, nb_of_word);
    start = (*box)->index_beginning_words_rest[nb_of_word]; //hasiera de dónde empieza la palabra word
    keep_start = start;
    len = 0;
    //printf("start = %d\n", start);
    while (!ft_isspace((*box)->input_substr[start]) && (start < (int)ft_strlen((*box)->input_substr)))
    {
        start++;
        len++;
        //printf("yes\n");
    }
    //printf("len = %d\n", len);
    //printf("holiwis\n");
    (*box)->rest_info_potential_cmd[nb_of_word] = malloc(sizeof(char) * (len + 1));
    (*box)->rest_info_potential_cmd[nb_of_word][len] = '\0';
    x = 0;
    while (len > 0)
    {
        (*box)->rest_info_potential_cmd[nb_of_word][x] = (*box)->input_substr[keep_start];
        len--;
        x++;
        keep_start++;
    }
    //printf("nb_of_word = %d\n", nb_of_word);
    printf("                      we've got the word! rest_info_potential_cmd[%d] = %s\n", nb_of_word, (*box)->rest_info_potential_cmd[nb_of_word]);
}

void cpy_rest_words(t_box **box)
{
    int tmp_nb_of_rest_words;
    int i;

    printf("     cpy_rest_words, nb_of_words_rest = %d\n", (*box)->nb_of_words_rest);
    (*box)->rest_info_potential_cmd = malloc(sizeof(char *) * (*box)->nb_of_words_rest);
    //printf("done\n");
    tmp_nb_of_rest_words = (*box)->nb_of_words_rest;
    i = 0;
    while (tmp_nb_of_rest_words > 0)
    {
        cpy_1_word(box, i);
        tmp_nb_of_rest_words--;
        i++;
    }
}

void ft_get_only_needed(t_box **box)
{
    //int len_rest;
    //int i;
    //printf("micasa = %s\n", (*box)->micasa);
    printf("     ft_get_only_needed\n");
    (*box)->nb_of_words_rest = rest_numof_words(box);
    printf("               rest_numof_words | counter = "MAGENTA"%d\n"RESET_COLOR, (*box)->nb_of_words_rest);
    rest_get_ind_beginning_words(box);

    cpy_rest_words(box);
    
    /*len_rest = get_len_only_needed(box);
    (*box)->rest_info_potential_cmd = malloc(sizeof(char *) * (len_rest + 1))
    (*box)->rest_info_potential_cmd[len_rest] = '\0';
    i = 0;
    while (len_rest > 0)
    {
        
    }*/
}

/**/
void ft_get_cmd_args(t_box **box)
{
    ft_get_what_to_take(box);
    printf(MAGENTA"     char *what_to_take"RESET_COLOR" generated✅\n");
    ft_get_only_needed(box);
}

void   ft_cmd_args (t_box **box)
{
    //(*box)->micasa = malloc(sizeof(char) * 4);
    //(*box)->micasa[0] = 'u';
    //(*box)->micasa[1] = 'u';
    //(*box)->micasa[2] = 'u';
    //(*box)->micasa[3] = '\0';
    //printf(">>>>>>>>>>>> name = %s\n", (*box)->micasa);
    printf("     02_boxes_6_cmd.c - "MAGENTA"ft_cmd_args\n"RESET_COLOR);
    ft_get_cmd_args(box);
}