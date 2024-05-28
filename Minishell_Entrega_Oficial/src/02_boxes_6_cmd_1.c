/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   02_boxes_6_cmd_1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uxmancis <uxmancis@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 10:46:55 by uxmancis          #+#    #+#             */
/*   Updated: 2024/05/24 18:24:44 by uxmancis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../inc/minishell.h"

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

void ft_get_cmd_args(t_box **box, t_prompt **prompt)
{
    ft_get_what_to_take(box);
    printf(MAGENTA"     char *what_to_take"RESET_COLOR" generated✅\n");
    ft_get_only_needed(box);
    //printf("nb_of_words_rest = %d\n", (*box)->nb_of_words_rest);
    if ((*box)->nb_of_words_rest) //solo vamos a analizar dólar si hay palabras a analizar
        check_dollars_expansion(box, prompt);
}

void   ft_cmd_args (t_box **box, t_prompt **prompt)
{
    //(*box)->micasa = malloc(sizeof(char) * 4);
    //(*box)->micasa[0] = 'u';
    //(*box)->micasa[1] = 'u';
    //(*box)->micasa[2] = 'u';
    //(*box)->micasa[3] = '\0';
    //printf(">>>>>>>>>>>> name = %s\n", (*box)->micasa);
    printf("     02_boxes_6_cmd.c - "MAGENTA"ft_cmd_args\n"RESET_COLOR);
    ft_get_cmd_args(box, prompt);
}