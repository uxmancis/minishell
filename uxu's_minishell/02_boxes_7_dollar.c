/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   02_boxes_7_dollar.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uxmancis <uxmancis@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 13:31:14 by uxmancis          #+#    #+#             */
/*   Updated: 2024/05/19 13:48:28 by uxmancis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*is_dollar
*
*   Returns number of dollars found in each word to be analysed
*   from rest_info_potential_cmd. 
*/
int get_nb_of_dollars(t_box **box, int ind)
{
    int len_word;
    int i;
    int counter;

    //printf("     get_nb_of_dollars\n");
    len_word = ft_strlen((*box)->rest_info_potential_cmd[ind]);
    counter = 0;
    //printf("     len = %d, ind = %d\n", len_word, ind);
    i = 0;
    while (len_word > 0)
    {
        //printf("                      rest_info_potential_cmd[%d][%d] = %c\n", ind, i, (*box)->rest_info_potential_cmd[ind][i]);
        if ((*box)->rest_info_potential_cmd[ind][i] == '$')
            counter++;
        i++;
        len_word--;
    }
    //printf(YELLOW"     nb_of_dollars = %d\n\n"RESET_COLOR, counter);
    return (counter);
}

void ft_replace (t_box **box, int ind, char *str_after)
{
    int new_len;
    int i;

    //printf("ft_replace\n");
    new_len = ft_strlen(str_after);
    //printf("new_len = %d\n", new_len);
    free((*box)->rest_info_potential_cmd[ind]);
    (*box)->rest_info_potential_cmd[ind] = malloc(sizeof(char) * (new_len + 1));
    (*box)->rest_info_potential_cmd[ind][new_len] = '\0';
    i = 0;
    while (new_len > 0)
    {
        //printf("yes\n");
        (*box)->rest_info_potential_cmd[ind][i] = str_after[i];
        i++;
        new_len--;
    }
    //printf("done!\n");
}

char *basic_itoa(int nb)
{
    char *str;
    int len;
    int keep_nb;
    int i;
    
    keep_nb = nb;
    len = 0;
    while (nb  > 10)
    {
        //printf("Before nb = %d - ", nb);
        len++;
        nb = nb / 10;
        //printf("After nb = %d\n", nb);
    }
    if (nb > 0 && nb < 10)
        len++;
    //printf("len itoa = %d\n", len);
    str = malloc(sizeof(char) * (len + 1));
    str[len] = '\0';
    i = len - 1 ;
    while (len > 0) //copiarmos de dcha a izq.
    {
        str[i] = (keep_nb % 10) + 48;
        i--;
        keep_nb = keep_nb / 10;
        len--;
    }
    //printf("result = %s\n", str);
    return (str);
}

/*
*   Variables:
*       ind: index in rest_info_potential_cmd: zenbagarren hitza
*
*   What does get_updated_words do? Checks dollars:
*       $ --> replaces by $ (character), stays same
*       $$ --> replaces by pid
*       $ENV_VARIABE --> replaces by variable of environment
*/
void get_updated_words(t_box **box, int ind)
{
    int nb_of_dollars_in_word;
    int i;
    int len_word;
    pid_t pid;
    
    nb_of_dollars_in_word = get_nb_of_dollars(box, ind);
    printf("               nb_of_dollars_in_word = "YELLOW"%d"RESET_COLOR, nb_of_dollars_in_word);
    len_word = ft_strlen((*box)->rest_info_potential_cmd[ind]);
    pid = getpid();
    i = 0;
    while (len_word > 0)
    {
        if ((*box)->rest_info_potential_cmd[ind][i] == '$'/* && info de dict_quotess needed*/) //necesito comprobar que está fuera de comillas o dentro de dobles. Ahora mismo con la variable rest_info_potential_cmd he perdido la traza de dict. ya que no sé a cuál corresponden. Al generar what_to_take y copiar los Y a rest_info_potential_cmd tengo que guardar traza de los índices de cada caracter en inputsubstr
        {
            if ((i + 1) < len_word && (*box)->rest_info_potential_cmd[ind][i + 1] == '$') //asegurar que no hacemos overflow (i + 1) < len
            {
                printf("\n               Before replace | rest_info_potential_cmd[%d] = %s\n", ind, (*box)->rest_info_potential_cmd[ind]);
                ft_replace(box, ind, basic_itoa(pid));
                printf("               After replace | rest_info_potential_cmd[%d] = %s\n", ind, (*box)->rest_info_potential_cmd[ind]);
                if ((i + 2) < len_word) //para asegurar no overflow
                    i = i + 2;
                else
                    break;
            }     
            //if (la primera palabra == coincide con alguna variable de entorno)
                //ft_replace por el contenido de la variable
            //else //si no coincide con ninguna variable de entorno
               // ft_replace((*box)->rest_info_potential_cmd[ind], "");
        }
        len_word--;
    }
    
}

/*
*   Variables:
*       tmp_nb_of_words: nb_of_words_rest
*/
void check_dollars_expansion(t_box **box)
{
    int tmp_nb_of_words;
    int i;

    printf("----------------------------------------------\n\n");
    printf("     02_boxes_6_cmd.c - "YELLOW"check_dollars_expansion"RESET_COLOR" | nb_of_words to be analysed = "YELLOW"%d"RESET_COLOR"\n", (*box)->nb_of_words_rest);
    tmp_nb_of_words = (*box)->nb_of_words_rest;
    i = 0;
    while (tmp_nb_of_words > 0)
    {
        printf("     Analyse word nb. "YELLOW"%d"RESET_COLOR, i + 1);
        get_updated_words(box, i);
        tmp_nb_of_words--;
        i++;
        printf(" - update completed ✅\n");
    }
}