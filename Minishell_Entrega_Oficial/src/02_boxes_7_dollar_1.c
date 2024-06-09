/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   02_boxes_7_dollar.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uxmancis <uxmancis@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 13:31:14 by uxmancis          #+#    #+#             */
/*   Updated: 2024/05/26 18:51:02 by uxmancis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../inc/minishell.h"

int ft_isalnum_str(char *str)
{
    int i; 

    i = 0;
    while (str[i] != '\0')
    {
        if (!ft_isalnum(str[i]))
            return (-1);
        i++;
    }
    return (0);
}

/*
*   return (0) only used to exit function when next_is_space
*
*   tmp_dict_quotes_word hay que pasarlo como int **, ya que hay ciertas funciones 
*   a las que se les llama desde find_dollars_and_replace que sí que modifican
*   los valores de la variable. E.g.: fill_with_nine, replace_pid_sec_dollar, 
*   finish_to_update_dict_quotes. Todos estos ejemplos particularmente se llaman 
*   desde mng_to_replace_sec_dollar. En el resto de funciones (foto actual)
*   la variable puede pasarse desreferenciada, ya que las funciones a las que llamamos
*   únicamente serán usuarios de la variable, pero no la modificarán.
*/
int find_dollars_and_replace(t_box **box, t_x_y_rest_info *x_y, int **tmp_dict_quotes_word, t_prompt **prompt)
{
    char *word;
    //int len_word;
    //int len_word; //to debug
    //printf("                    find_dollars_and_replace, x = %d, y = %d\n", x_y.index_x, x_y.index_y);
    //len_word = ft_strlen((*box)->rest_info_potential_cmd[x_y.index_x]);
    //printf("     find_dollars_and_replace | "MAGENTA"y = %d, len_word = %d\n"RESET_COLOR, x_y.index_y, len_word);
    /*while (len_word > 0)
    {
        //printf("we're checkin here\n");
      */
    if (is_dollar(box, *x_y, *tmp_dict_quotes_word))
    {
        printf("                    dollar was found, y = %d, len_total = %d\n", x_y->index_y, (int)ft_strlen((*box)->rest_info_potential_cmd[x_y->index_x]));
        if (next_is_space_or_end(box, *x_y))
        {
            //printf("                    case "YELLOW"1: only $\n"RESET_COLOR);
            return (0); //no need to replace, $ stays
        }  
        else if(next_is_sec_dollar(box, *x_y)) //después tiene contenido el dólar
        {
            //printf("                    case "YELLOW"2: double $$ replace pid\n"RESET_COLOR);
                mng_to_replace_sec_dollar(box, *x_y, tmp_dict_quotes_word);
                //printf(GREEN"                    >> Result str = %s\n\n"RESET_COLOR, (*box)->rest_info_potential_cmd[x_y.index_x]);
                //printf(YELLOW"uxu we're here\n"RESET_COLOR);
                //printf("tmp_dict_qotes[%d] = %d\n", 0, (*tmp_dict_quotes_word)[0]);
                //printf("tmp_dict_qotes[%d] = %d\n", 1, (*tmp_dict_quotes_word)[1]);
        }
        else if (next_is_question(box, *x_y))
        {
            x_y->index_y++;
            //x_y.index_y++;
        }
        else if (is_in_env(box, *x_y, prompt)) //sí en env . Coger hassta fin palabra o hasta próximo dólar
        {
            printf("                    case "YELLOW"3: env variable found\n"RESET_COLOR);
            mng_to_replace_env(box, *x_y, prompt, tmp_dict_quotes_word);
            printf(BLUE"                    >> Result str = %s\n"RESET_COLOR, (*box)->rest_info_potential_cmd[x_y->index_x]);
        }
        else //no en env
        {
            word = get_word_4(box, *x_y, NULL); //WIP
            printf(BLUE"word = %s\n"RESET_COLOR, word);
            if (word == NULL)
            {
                x_y->index_y++;
                return (0);
            }            
            else if (ft_isalnum_str(word) == -1)
            {
                x_y->index_y++;
                return (0);
            }
            printf("                    case "YELLOW"4: replace by [], not an env variable\n"RESET_COLOR);
            mng_to_replace_delete(box, *x_y, prompt);
            /*len_word = ft_strlen(word);
            while (len_word > 0)
            {
                printf(BLUE"before: y = %d \n>>>>>>>>>> patras\n", x_y.index_y);
                len_word--;
                x_y.index_y--;
                printf("after, y = %d\n"RESET_COLOR, x_y.index_y);
            }*/
            x_y->index_y--;
            printf(MAGENTA"                    >> Result str = %s, y = %d\n"RESET_COLOR, (*box)->rest_info_potential_cmd[x_y->index_x], x_y->index_y);
        }
    }
        //}
        //x_y.index_y++;
        //len_word--;
        //printf("status: y = %d, len_word = %d\n", x_y.index_y, len_word);
    //printf("tmp_dict_qotes[%d] = %d\n", 0, (*tmp_dict_quotes_word)[0]);
    //printf("tmp_dict_qotes[%d] = %d\n", 1, (*tmp_dict_quotes_word)[1]);
    //printf("tmp_dict_qotes[%d] = %d\n", 2, (*tmp_dict_quotes_word)[2]);
    return (0);
}

/*no_more_dollars
*  Returns:
*       1: Success, no more dollars were found allong word (taking quotes into account)
*       0: Still more dollars to be analysed and then replaced
*/
int no_more_dollars(t_box **box, t_x_y_rest_info x_y, int *tmp_dict_quotes_word)
{
    int len_word;
    //int i; //to debug
    
    len_word = ft_strlen((*box)->rest_info_potential_cmd[x_y.index_x]);
    //i = 0;
    //printf("     02_boxes_7_dollar.c | "YELLOW" are there more dollars"RESET_COLOR" along word? "RESET_COLOR"len = %d, x = %d, y = %d, i = %d\n", len_word, x_y.index_x, x_y.index_y, i);
    //printf(MAGENTA"uxu we're here\n"RESET_COLOR);
    //printf("tmp_dict_qotes[%d] = %d\n", 0, (*tmp_dict_quotes_word)[0]);
    //printf("tmp_dict_qotes[%d] = %d\n", 1, (*tmp_dict_quotes_word)[1]);
    //printf("tmp_dict_qotes[%d] = %d\n", 2, (*tmp_dict_quotes_word)[2]);
    x_y.index_y = 0;
    while (len_word > 0)
    {
        //printf("rest_info[%d][%d] = %c\n", x_y.index_x, x_y.index_y, (*box)->rest_info_potential_cmd[x_y.index_x][x_y.index_y]);
        //printf("tmp_dict_qotes[%d] = %d\n", i, (*tmp_dict_quotes_word)[i]);
        if (is_dollar(box, x_y, tmp_dict_quotes_word))//si encuentra alguno
        {
            printf(GREEN"                   yes - STILL MORE DOLLARS, y = %d\n\n"RESET_COLOR, x_y.index_y);
            return (0);
        }
        //i++;
        x_y.index_y++;
        len_word--;
        //printf("BUCLE: i = %d, len_word = %d\n", i, len_word);
    }
   //si llega hasta el final sin encontrar ningún dólar. Si ya ha llegado aquí, si ha salido del bucle, es porque ya hemos recorrido toda la palabra y no se han encontrado dólares válidos
    printf(RED"                   no - LAST DOLLAR WAS FOUND\n"RESET_COLOR);
    return (1);
}

int *generate_specif_dict_quotes(t_box **box, t_x_y_rest_info x_y, int len)
{
    int *tmp_dict_quotes_word;
    int nb_word_x; //fixed, ze hitz konkretu baten gare, ezta aldatuko

    tmp_dict_quotes_word = malloc(sizeof(int)*len); //no necesito +1 para valor nulo
    //printf("word nb_word_x= %d, tmp_dict_quotes_word - "MAGENTA" len = %d\n"RESET_COLOR, nb_word_x, len_word);
    nb_word_x = x_y.index_x;
    //printf("generate_specif_dict_quotes | len = %d, nb_word_x = %d, y = %d\n", len, nb_word_x, x_y.index_y);
    fill_tmp_dict_quotes(box, &tmp_dict_quotes_word, len, (*box)->index_beginning_words_rest[nb_word_x]);
    //printf("          ");
    //put_arr(tmp_dict_quotes_word, len);
    //printf("\n");
    //printf("     02_boxes_7_dollar.c - generated_specif_dict_quotes | "GREEN"tmp_dict_quotes_word"RESET_COLOR" generated✅\n"RESET_COLOR);
    return (tmp_dict_quotes_word);
}

/*get_each_word_updated
*
*   Infinite loop until no more dollars are found in word.
*
*   Word = the corresponding word in char **rest_info_potential_cmd (box).
*
*   We'll call this get_updated_words function for each of the words in
*   the variable.
*
*   What does get_updated_words do? Checks dollars:
*       $ --> replaces by $ (character), stays same
*       $$ --> replaces by pid
*       $ENV_VARIABE --> replaces by variable of environment
*/
void get_each_word_updated(t_box **box, int nb_word_x, t_prompt **prompt)
{
    int len_word;
    int *tmp_dict_quotes_word; //para cada palabra, creo uno propio temporal para esta función, se puede liberar al salir
    t_x_y_rest_info x_y;
    //char *tmp_rest_info_word; creo que ya la variable doesn't make sense thx to infinite loop
    int tmp_to_debug;
    
    printf("               Before: ["MAGENTA"%s"RESET_COLOR"]\n", (*box)->rest_info_potential_cmd[nb_word_x]);
    x_y.index_x = nb_word_x;
    x_y.index_y = 0;
    tmp_to_debug = 0;
    tmp_dict_quotes_word = NULL;
    //1. tmp_dict_quotes is updated
    //2. find_dollars_and_replace
    while (1) //que recorra esta palabra (nb_word_x) tantas veces sea necesario (el len se va modificando when find_dollars_and_replace)hasta que no more dolars found along word
    {
        //printf(BLUE"     vuelta n.º %d - "RESET_COLOR, tmp_to_debug);
        len_word = ft_strlen((*box)->rest_info_potential_cmd[nb_word_x]);
        //1. Generate (updadte*) tmp_dict_quotes
        //printf(MAGENTA"len_word = %d, x = %d\n"RESET_COLOR, len_word, nb_word_x);
        /*if (tmp_dict_quotes_word)
        {
            free(tmp_dict_quotes_word);
            tmp_dict_quotes_word = NULL;
        }*/
        if (tmp_dict_quotes_word)
            ft_free(tmp_dict_quotes_word);
        tmp_dict_quotes_word = generate_specif_dict_quotes(box, x_y, len_word);
        //printf(MAGENTA"uxu we're here\n"RESET_COLOR);
        //printf("          ");
        //put_arr(tmp_dict_quotes_word, len_word);
        //printf("\n");
        
        //tmp_dict_quotes_word = malloc(sizeof(int) * len_word); //no necesito +1 para ningún valor nulo final
        //printf("word nb_word_x= %d, tmp_dict_quotes_word - "MAGENTA" len = %d\n"RESET_COLOR, nb_word_x, len_word);
        //fill_tmp_dict_quotes(box, &tmp_dict_quotes_word, len_word/*, (*box)->index_beginning_words_rest[nb_word_x]*/);
        //put_arr(tmp_dict_quotes_word, len_word);
        //printf("printed\n");
        x_y.index_x = nb_word_x; //safety purposes, just in case, to make sure
        //Cuando hagamos find_dollars_and_replace, dentro el tmp_dict_quotes_word se tiene que actualizar también. Tiene que venir actualizado de vuelta
        
        //2. Identify dollars
        find_dollars_and_replace(box, &x_y, &tmp_dict_quotes_word, prompt); //cada palabra
        printf(BLUE">>>>>>>>> %d\n"RESET_COLOR, x_y.index_y);
        //printf(BLUE"uxu we're here\n"RESET_COLOR);
        //printf("tmp_dict_qotes[%d] = %d\n", 0, tmp_dict_quotes_word[0]);
        //printf("tmp_dict_qotes[%d] = %d\n", 1, tmp_dict_quotes_word[1]);
        //printf("tmp_dict_qotes[%d] = %d\n", 2, tmp_dict_quotes_word[2]);
        if (no_more_dollars(box, x_y, tmp_dict_quotes_word))
        {
            printf(BLUE">>>>>>>>> no more dollars in word\n"RESET_COLOR);
            break;
        }
        if (x_y.index_y == len_word) //prevent overflow, safety :)
        {
            printf("LLEGAMOSS AL FINAL, len_word = %d, y = %d\n", len_word, x_y.index_y);
            break;
        }
        
            
        tmp_to_debug++;
        x_y.index_y++;
    }
    printf("               After: ["YELLOW"%s"RESET_COLOR"]\n\n", (*box)->rest_info_potential_cmd[x_y.index_x]);
    free (tmp_dict_quotes_word);
}

/*
*   Variables:
*       tmp_nb_of_words: nb_of_words_rest
*/
void check_dollars_expansion(t_box **box, t_prompt **prompt)
{
    int tmp_nb_of_words;
    int i;

    printf("----------------------------------------------\n\n");
    printf("     02_boxes_6_cmd.c - "YELLOW"check_dollars_expansion"RESET_COLOR" | nb_of_words to be analysed = "YELLOW"%d"RESET_COLOR"\n", (*box)->nb_of_words_rest);
    tmp_nb_of_words = (*box)->nb_of_words_rest;
    i = 0;
    while (tmp_nb_of_words > 0)
    {
        printf("     Analyse word nb. "YELLOW"%d"RESET_COLOR" - rest_info_potential_cmd[%d]\n", i + 1, i);
        get_each_word_updated(box, i, prompt);
        tmp_nb_of_words--;
        i++;
        //printf(" - update completed ✅\n");
    }
}