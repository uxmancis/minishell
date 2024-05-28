/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   02_boxes_6_cmd_3.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uxmancis <uxmancis@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 13:41:36 by uxmancis          #+#    #+#             */
/*   Updated: 2024/05/19 15:11:14 by uxmancis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../inc/minishell.h"

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
        if ((*box)->what_to_take[i] == 'Y')
        {
            //printf("               let's count! input_substr[%d] = %c               counter = %d\n", i, (*box)->input_substr[i], counter);
            if (possible_cases(box, i))
                counter++;
            //printf(GREEN"                     counter = %d\n"RESET_COLOR, counter);
            while (possible_cases(box, i) && i < keep_len)
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
    //printf("               rest_numof_words | counter = %d\n", counter);
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
        if ((*box)->what_to_take[i] == 'Y')
        {
            if (possible_cases(box, i))
            {
                (*box)->index_beginning_words_rest[x] = i;
                printf("                      index_beginning_words_rest[%d] = %d\n", x, (*box)->index_beginning_words_rest[x]);
                x++;
            }
            while (possible_cases(box, i) && i < keep_len)
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

/*
*   Cases to take into account in order to consider when counting
*   total number of words to be copied in rest_info_potential_cmd.
*
*   Explanation:
*       - Anything that is not '\'', '\"' or !ft_isspace --> will automatically count
*       as new word. Doesn't matter if inside of outside of quotes.
*       - Quotes (either both simple '\'' and double '\"') --> will count only when
*       inside of other type of quotes. Simples must be inside of doubles and viceversa.
*       - ft_isspace will count if inside of quotes (either both single or doble)
*/
int possible_cases(t_box **box, int index)
{
    //comillas simples dentro de comillas dobles
    if ((*box)->input_substr[index] == '\'' && (*box)->dict_quotes[index] == 2) //simples dentro de dobles sí es palabra para counter (1. no puede estar fuera de comillas = serían principales. Already managed. 2. no puede estar dentro de simples = sería principales. Already managed.)
        return (1);
    else if((*box)->input_substr[index] == '\"' && (*box)->dict_quotes[index] == 1) //dobles dentro de simples sí es palabra para counter (1. no puede estar fuera de comillas = serían principales. Already managed. 2. no puede estar dentro de dobles = sería principales. Already managed.)
        return (1);
    else if(ft_isspace((*box)->input_substr[index]) && (*box)->dict_quotes[index] != 0) //espacio dentro de comillas sí cuenta como palabra (simples o dobles ambas nos valen)
        return (1);
    else if ((*box)->input_substr[index] != '\'' && (*box)->input_substr[index] != '\"' && !ft_isspace((*box)->input_substr[index]))
        return (1);
    return (0);
}

/*cpy_1_word
*
*   Variables:
*       nb_of_word: zenbagarren rest-eko hitza dan (posición en index_beginning_words_rest)
*       start: index of beginning of word. Already precise. No need to go spaces++
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
    while (possible_cases(box, start) && (start < (int)ft_strlen((*box)->input_substr)))
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
    printf("                      rest_info_potential_cmd[%d] = ["MAGENTA"%s"RESET_COLOR"]\n", nb_of_word, (*box)->rest_info_potential_cmd[nb_of_word]);
    //printf("rest_info_potential_cmd[0][0] = %c\n", (*box)->rest_info_potential_cmd[0][0]);
}