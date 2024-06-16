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

#include "../inc/minishell.h"

int	ft_isalnum_str(char *str)
{
	int	i;

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
*
*/
//int find_dollars_and_replace(t_box **box, t_x_y_word *x_y, int **tmp_dict_quotes_word, t_prompt **prompt) //Objetivo: ver si puedo no pasarle box, y en vez de esto pasarle la palabra a actualizar
int find_dollars_and_replace(char **word_to_be_updated, t_x_y_word *x_y, int **tmp_dict_quotes_word, t_prompt **prompt) //Objetivo: ver si puedo no pasarle box, y en vez de esto pasarle la palabra a actualizar
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
    //printf("find_dollars_and_replace - ...looking for a new $ to expand... - y = %d\n", x_y->index_y);
    if (is_dollar(*word_to_be_updated, *x_y, *tmp_dict_quotes_word))
    {
        //printf("                    dollar was found, y = %d, len_total = %d\n", x_y->index_y, (int)ft_strlen(*word_to_be_updated));
        if (next_is_space_or_end(*word_to_be_updated, *x_y))
        {
            //printf("                    case "YELLOW"1: only $\n"RESET_COLOR);
            return (0); //no need to replace, $ stays
        }  
        else if(next_is_sec_dollar(*word_to_be_updated, *x_y)) //después tiene contenido el dólar
        {
            //printf("                    case "YELLOW"2: double $$ replace pid\n"RESET_COLOR);
            //printf(GRAY"y = %d\n"RESET_COLOR, x_y->index_y);
            mng_to_replace_sec_dollar(word_to_be_updated, *x_y, tmp_dict_quotes_word);
            //printf(GREEN"y = %d\n"RESET_COLOR, x_y->index_y);
            //printf(GREEN"                    >> Result str = %s\n\n"RESET_COLOR, (*box)->rest_info_potential_cmd[x_y.index_x]);
            //printf(YELLOW"uxu we're here\n"RESET_COLOR);
            //printf("tmp_dict_qotes[%d] = %d\n", 0, (*tmp_dict_quotes_word)[0]);
            //printf("tmp_dict_qotes[%d] = %d\n", 1, (*tmp_dict_quotes_word)[1]);
        }
        else if (next_is_question(*word_to_be_updated, *x_y))
        {
            x_y->index_y++;
            //x_y.index_y++;
        }
        else if (is_in_env(*word_to_be_updated, *x_y, prompt)) //sí en env . Coger hassta fin palabra o hasta próximo dólar
        {
            //printf("                    case "YELLOW"3: env variable found\n"RESET_COLOR);
            mng_to_replace_env(word_to_be_updated, *x_y, prompt, tmp_dict_quotes_word);
            //printf(BLUE"                    >> Result str = %s, len = %d\n"RESET_COLOR, (*box)->rest_info_potential_cmd[x_y->index_x], (int)ft_strlen((*box)->rest_info_potential_cmd[x_y->index_x]));
        }
        else //no en env
        {
            word = get_word_4(*word_to_be_updated, *x_y);
            //printf(BLUE"word = %s\n"RESET_COLOR, word);
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
            //printf("                    case "YELLOW"4: replace by [], not an env variable\n"RESET_COLOR);
            mng_to_replace_delete(word_to_be_updated, *x_y);
            /*len_word = ft_strlen(word);
            while (len_word > 0)
            {
                printf(BLUE"before: y = %d \n>>>>>>>>>> patras\n", x_y.index_y);
                len_word--;
                x_y.index_y--;
                printf("after, y = %d\n"RESET_COLOR, x_y.index_y);
            }*/
            x_y->index_y--;
            //printf(MAGENTA"                    >> Result str = %s, y = %d\n"RESET_COLOR, (*box)->rest_info_potential_cmd[x_y->index_x], x_y->index_y);
        }
    }
    //printf(GREEN"$ expansion managed - done✅\n"RESET_COLOR);
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
int	no_more_dollars(char *word_to_be_checked, t_x_y_word x_y, int *tmp_dict_quotes_word)
{
	int len_word;
	int i; //to debug

	len_word = ft_strlen(word_to_be_checked);
    //printf(GREEN"no_more_dollars, len_word = %d\n", len_word);
	i = 0;
	//printf("     02_boxes_7_dollar.c - no_more_dollars | "YELLOW" are there more dollars"RESET_COLOR" along word? "RESET_COLOR"len = %d, x = %d, y = %d, i = %d\n", len_word, x_y.index_x, x_y.index_y, i);
	x_y.index_y = 0;
	while (len_word > 0)
	{
		//printf(BLUE"rest_info[%d][%d] = %c\n"RESET_COLOR, x_y.index_x, x_y.index_y, (*box)->rest_info_potential_cmd[x_y.index_x][x_y.index_y]);
		//printf(MAGENTA"tmp_dict_qotes[%d] = %d\n"RESET_COLOR, i, tmp_dict_quotes_word[i]);
		if (is_dollar(word_to_be_checked, x_y, tmp_dict_quotes_word))//si encuentra alguno
		{
			//printf(GREEN"                   yes - STILL MORE DOLLARS, y = %d\n\n"RESET_COLOR, x_y.index_y);
			return (0);
		}
		i++;
		x_y.index_y++;
		len_word--;
        //printf(YELLOW"len_word = %d\n"RESET_COLOR, len_word);
		//printf("BUCLE: i = %d, len_word = %d\n", i, len_word);
	}
	//si llega hasta el final sin encontrar ningún dólar. Si ya ha llegado aquí, si ha salido del bucle, es porque ya hemos recorrido toda la palabra y no se han encontrado dólares válidos
	//printf(RED"                   no - LAST DOLLAR WAS FOUND\n"RESET_COLOR);
	return (1);
}

/*generate_specif_dict_quotes
*
*	nb_word_x is fixed. We're in 1 particular word. nb_word_x won't change.
*/
//int	*generate_specif_dict_quotes(t_box **box, t_x_y_rest_info x_y, int len, char flag)
int	*generate_specif_dict_quotes(t_box **box, char *word_to_be_updated, int nb_word_x, char flag)
{
	int	*tmp_dict_quotes_word;
	//int	nb_word_x;
    int start;

	tmp_dict_quotes_word = malloc(sizeof(int)*ft_strlen(word_to_be_updated)); //no necesito +1 para valor nulo
	//printf("word nb_word_x= %d, tmp_dict_quotes_word - "MAGENTA" len = %d\n"RESET_COLOR, nb_word_x, len_word);
	//nb_word_x = x_y.index_x;
	//printf("generate_specif_dict_quotes | len = %d, nb_word_x = %d, y = %d\n", len, nb_word_x, x_y.index_y);
    //printf("nb_word_x = %d\n", nb_word_x);
    if (flag == 'C') //cuando vamos a generar dict_quotes porque estamos queriendo expandir C = Comandos. Variable en box: rest_info_potential_cmd
    {
        start = (*box)->index_beginning_words_rest[nb_word_x];
        //printf(GRAY"start = %d\n"RESET_COLOR, start);
    }    
    else if (flag == 'W')
    {
        start = 0;
        //printf(GRAY"start = %d\n"RESET_COLOR, start);
    }
    //printf(GRAY"start = %d\n"RESET_COLOR, start);
	fill_tmp_dict_quotes(box, &tmp_dict_quotes_word, ft_strlen(word_to_be_updated), start);
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
*
*	While(1)
*		1st, tmp_dict_quotes is updated (Function: generate_specif_dict_quotes)
*		2nd, find_dollars_and_replace
*		3rd, is there any other dollar? (Function: no_more_dollars)
*/
//void	get_each_word_updated(t_box **box, int nb_word_x, t_prompt **prompt)
void	get_each_word_updated(char *word_to_be_updated, int nb_word_x, t_box **box, t_prompt **prompt)
{
	int len_word;
	int *tmp_dict_quotes_word; //para cada palabra, creo uno propio temporal para esta función, se puede liberar al salir
	//t_x_y_rest_info x_y;
    t_x_y_word x_y;
	//char *tmp_rest_info_word; creo que ya la variable doesn't make sense thx to infinite loop
	int tmp_to_debug;
    int tmp_len_to_debug;
    int tmp_i;
    //int y; //Azkenian volvemos a x_y, posición concreta dentro de word_to_be_updated. Antes era x_y.index_y

	printf("               Before: ["MAGENTA"%s"RESET_COLOR"]\n", word_to_be_updated);
	x_y.index_x = nb_word_x;
	x_y.index_y = 0;
	tmp_to_debug = 0;
	tmp_dict_quotes_word = NULL;
    //len_word = ft_strlen((*box)->rest_info_potential_cmd[nb_word_x]);
    len_word = ft_strlen(word_to_be_updated);
	//tmp_dict_quotes_word = generate_specif_dict_quotes(box, x_y, len_word);
	tmp_dict_quotes_word = generate_specif_dict_quotes(box, word_to_be_updated, nb_word_x, (*box)->flag_word_or_cmd);
    while (1) //que recorra esta palabra (nb_word_x) tantas veces sea necesario (el len se va modificando when find_dollars_and_replace)hasta que no more dolars found along word
    {
        //printf(BLUE"     vuelta n.º %d - "RESET_COLOR, tmp_to_debug);
        //len_word = ft_strlen((*box)->rest_info_potential_cmd[nb_word_x]);
        len_word = ft_strlen(word_to_be_updated);
        tmp_len_to_debug = len_word;
        tmp_i = 0;
        //printf(GREEN"\n\ncheck_situ, word = %s, y = %d\n" RESET_COLOR, word_to_be_updated, x_y.index_y);
        while (tmp_len_to_debug > 0) //Next to solve: aquí tmp_dict_quotes_word no está llegando con su nuevo len
        {
            //printf(GREEN"          tmp_dict_qotes[%d] = %d\n"RESET_COLOR, tmp_i, tmp_dict_quotes_word[tmp_i]);
            tmp_len_to_debug--;
            tmp_i++;
            //start++;
	    }
    
        //x_y.index_x = nb_word_x; //safety purposes, just in case, to make sure
        //Cuando hagamos find_dollars_and_replace, dentro el tmp_dict_quotes_word se tiene que actualizar también. Tiene que venir actualizado de vuelta
        
        //2. Identify dollars
        //find_dollars_and_replace(box, &x_y, &tmp_dict_quotes_word, prompt); //cada palabra. tmp_dict_quotes_word MUST be updated so as to be used (no segfault) by no_more_dollars
        find_dollars_and_replace(&word_to_be_updated, &x_y, &tmp_dict_quotes_word, prompt); //cada palabra. tmp_dict_quotes_word MUST be updated so as to be used (no segfault) by no_more_dollars
        //printf(BLUE">>>>>>>>> y = %d\n"RESET_COLOR, x_y.index_y);
        if (no_more_dollars(word_to_be_updated, x_y, tmp_dict_quotes_word)) //only to check. Will not be updated. That's why we dereference.
        {
            //printf(BLUE">>>>>>>>> no more dollars in word\n"RESET_COLOR);
            break;
        }
        if (x_y.index_y == len_word) //prevent overflow, safety :)
        {
            //printf("LLEGAMOSS AL FINAL, len_word = %d, y = %d\n", len_word, x_y.index_y);
            break;
        }
        
        tmp_to_debug++;
        x_y.index_y++;
    }
    printf("               After: ["YELLOW"%s"RESET_COLOR"]\n\n", word_to_be_updated);
    free (tmp_dict_quotes_word);
}


void expand_infile_words(t_box **box, t_prompt **prompt)
{
    int tmp_nb_of_words_infile;
    int nb_infile_x;

    printf("          which words are we checking?"YELLOW" - INFILE_WORDS\n"RESET_COLOR);
    tmp_nb_of_words_infile = (*box)->nb_of_infile;
    nb_infile_x = 0;
    (*box)->flag_word_or_cmd = 'W'; //will be used in generate_specif_dict_quotes in order to know which is index word, to know which is the index in dict_quotes we wanna copy. It will impact in variable named "start".
    while (tmp_nb_of_words_infile > 0)
    {
        get_each_word_updated((*box)->words_infile[nb_infile_x], nb_infile_x, box, prompt);
        nb_infile_x++;
        tmp_nb_of_words_infile--;
    }
}

void expand_outfile_strong_words(t_box **box, t_prompt **prompt)
{
    int tmp_nb_of_words_outf_str;
    int nb_outfile_str_x;

    printf("          which words are we checking?"YELLOW" - OUTFILE_STRONG_WORDS\n"RESET_COLOR);
    tmp_nb_of_words_outf_str = (*box)->nb_of_outfile_strong;
    nb_outfile_str_x = 0;
    (*box)->flag_word_or_cmd = 'W'; //will be used in generate_specif_dict_quotes in order to know which is index word, to know which is the index in dict_quotes we wanna copy. It will impact in variable named "start".
    while (tmp_nb_of_words_outf_str > 0)
    {
        get_each_word_updated((*box)->words_outfile_strong[nb_outfile_str_x], nb_outfile_str_x, box, prompt);
        nb_outfile_str_x++;
        tmp_nb_of_words_outf_str--;
    }
}

void expand_outfile_append_words(t_box **box, t_prompt **prompt)
{
    int tmp_nb_of_words_outf_app;
    int nb_outfile_app_x;

    printf("          which words are we checking?"YELLOW" - OUTFILE_APPEND_WORDS\n"RESET_COLOR);
    tmp_nb_of_words_outf_app = (*box)->nb_of_outfile_append;
    nb_outfile_app_x = 0;
    (*box)->flag_word_or_cmd = 'W'; //will be used in generate_specif_dict_quotes in order to know which is index word, to know which is the index in dict_quotes we wanna copy. It will impact in variable named "start".
    while (tmp_nb_of_words_outf_app > 0)
    {
        get_each_word_updated((*box)->words_outfile_append[nb_outfile_app_x], nb_outfile_app_x, box, prompt);
        nb_outfile_app_x++;
        tmp_nb_of_words_outf_app--;
    }
}

void expand_rest_info_potential_cmd(t_box **box, t_prompt **prompt)
{
    int tmp_nb_of_words_rest_info;
    int nb_word_rest_x;

    printf("          which words are we checking?"YELLOW" - REST_WORDS_POTENCIAL_CMD\n"RESET_COLOR);
    tmp_nb_of_words_rest_info = (*box)->nb_of_words_rest;
    nb_word_rest_x = 0;
    (*box)->flag_word_or_cmd = 'C'; //will be used in generate_specif_dict_quotes in order to know which is index word, to know which is the index in dict_quotes we wanna copy. It will impact in variable named "start".
    while (tmp_nb_of_words_rest_info > 0)
    {
        get_each_word_updated((*box)->rest_info_potential_cmd[nb_word_rest_x], nb_word_rest_x, box, prompt);
        nb_word_rest_x++;
        tmp_nb_of_words_rest_info--;
    }
}


/*
*   Variables:
*       tmp_nb_of_words: nb_of_words_rest
*/
void	check_dollars_expansion(t_box **box, t_prompt **prompt)
{
	//int	tmp_nb_of_words;
	//int	x;

	printf("----------------------------------------------\n\n");
    printf("     02_boxes_6_cmd.c - "YELLOW"check_dollars_expansion\n"RESET_COLOR);
	//printf("     02_boxes_6_cmd.c - "YELLOW"check_dollars_expansion\n"RESET_COLOR);
	/*tmp_nb_of_words = (*box)->nb_of_words_rest;
	x = 0;
	while (tmp_nb_of_words > 0)
	{
		printf("     Analyse word nb. "YELLOW"%d"RESET_COLOR" - rest_info_potential_cmd[%d]\n", i + 1, i);
		//get_each_word_updated(box, i, prompt);
		get_each_word_updated((*box)->rest_info_potential_cmd[x], x, prompt);

        tmp_nb_of_words--;
		x++;
		//printf(" - update completed ✅\n");
	}*/


    //1. Expandir words_infiles
    expand_infile_words(box, prompt);
    //2. Expandir words outfiles_strong
    expand_outfile_strong_words(box, prompt);
    //3. Expandir words outfiles_append
    expand_outfile_append_words(box, prompt);
    //4. Expandir rest_info_potential_cmd
    expand_rest_info_potential_cmd(box, prompt);
}