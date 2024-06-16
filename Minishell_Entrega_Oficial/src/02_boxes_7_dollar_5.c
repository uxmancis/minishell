/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   02_boxes_7_dollar_5.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uxmancis <uxmancis@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 17:58:45 by uxmancis          #+#    #+#             */
/*   Updated: 2024/06/16 12:57:16 by uxmancis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../inc/minishell.h"

/* replace with pid
*
*   Also new dict_quotes is generated (so than we can use it to check if no_more_dollars)
*/

//replace_pid_sec_dollar(box, x_y, tmp_rest_info_before_free, keep_dict_quotes_word, tmp_dict_quotes_word, new_len);
void replace_pid_sec_dollar(t_w_d *w_d, char *keep_old_word, int *keep_old_dict, int new_len_word)
{
    //int len_new_word;
    int len_pid_str;
    int ind_pid_str;
    int ind_old_word;
    int two_times;
    int ind_dollar;
    //int new_len_word;
    int keep_new_len_word;;

    //fill_tmp_dict_quotes(box, &tmp_dict_quotes_word, len_word, (*box)->index_beginning_words_rest[nb_word_x]);
    //printf("          replace_pid_sec_dollar | str_src = "YELLOW"%s"RESET_COLOR" - keepin' it | where is dollar, ind [%d]\n", old_word, x_y.index_y);
    //len_new_word = ft_strlen((*box)->rest_info_potential_cmd[x_y.index_x]);
    //printf(MAGENTA"                    len_new_word = %d\n"RESET_COLOR, len_new_word);
    len_pid_str = ft_strlen(ft_get_pid_str());
    ind_dollar = w_d->y;
    w_d->y = 0;
    ind_old_word = 0;
    printf("word_to_be_updated = %s\n", w_d->word_to_be_updated);
    //new_len_word = ft_strlen(w_d->word_to_be_updated);
    printf(BLUE"new_len_word = %d\n"RESET_COLOR, new_len_word);
    keep_new_len_word = new_len_word;
    ind_pid_str = 0;
    /*while (len_new_word > 0)
    {
        printf(MAGENTA"Comenzamos! ¿Es aquí el dólar donde sustituir por pid?\n"RESET_COLOR);
        printf("bucle, x = %d, y = %d, len = %d\n", x_y.index_x, x_y.index_y, len_new_word);*/
    //printf(YELLOW"ind_pid_str = %d, ind_dollar = %d\n"RESET_COLOR, ind_pid_str, ind_dollar);
    
    //1. Hasta el $, simplemente copia
    //printf("Step 1: y = %d, ind_old_word = %d\n", x_y.index_y, ind_old_word);
    //(*tmp_dict_quotes_word)[x_y.index_y]= 5;
    //printf("pruebita = %d\n", (*tmp_dict_quotes_word)[x_y.index_y]);
    while (ind_pid_str != ind_dollar)
    {
        //printf(YELLOW"letsgo y = %d", x_y.index_y);
        w_d->word_to_be_updated[w_d->y] = keep_old_word[ind_old_word]; //hasi dana kopixatzen hasta el dólar
        w_d->dict_quotes_to_be_updated[w_d->y] = keep_old_dict[ind_old_word];
        ind_pid_str++; //para que luego cojamos bien desde el dólar
        ind_old_word++;
        w_d->y++;
        //printf("printed\n"RESET_COLOR);
    }
    //printf("> step 1 completed\n");
    //2. Una vez encontramos el dólar, sustituimos
    if (ind_pid_str == ind_dollar) //un poquito redundante, y un poquito jugón el bucle anterior. En mi cabeza tiene que darse siempre ok, pero imagínate que no.. posible bucle infinito? jaj
    {
        //printf(GREEN" YES!\n"RESET_COLOR);
        //printf("\n          yes! dollar is here, len = %d\n", len_pid_str);
        ind_pid_str = 0;
        while (len_pid_str > 0)
        {   
            //printf(YELLOW"willing to assign😊 | x = %d, y = %d, ind_pid_str = %d\n", x_y.index_x, x_y.index_y, ind_pid_str);
            w_d->word_to_be_updated[w_d->y] = ft_get_pid_str()[ind_pid_str];
            w_d->dict_quotes_to_be_updated[w_d->y] = 0;
            //printf(BLUE"                  GOIKUA assigned! [%d] = %c\n"RESET_COLOR, x_y.index_y, (*box)->rest_info_potential_cmd[x_y.index_x][x_y.index_y]);
            ind_pid_str++;
            len_pid_str--;
            w_d->y++;
            //new_len_word--; 2024/06/16 uste dot ya eztotela bihar
            //printf("len_word = %d, len_pid_str = %d, ind_pid_str = %d, y = %d\n", len_new_word, len_pid_str, ind_pid_str, x_y.index_y);
        }
        //saltarnos los 2 dólares
        two_times = 0;
        while (two_times != 2 && ind_old_word < keep_new_len_word && keep_old_word[ind_old_word] == '$'/* && ind_old_word == ind_dollar*/) //para saltarnos y no copiar los 2 dólares && safety to prevent overflow
        {
            ind_old_word++;
            two_times++;
            //printf(RED"PASAR DEL DOLAR AL COPIAR\n"RESET_COLOR);
        }
    }
        //😊😊😊😊si hay un momento en el que después de 1 dólar no hay otro dólar, en ese caso termina de copiarlo todo, y salte de aquí
        
    //printf(GREEN" No, \n"RESET_COLOR);
    //printf("          status check: len = %d\n", len_new_word);
    //printf("> step 2 completed\n");
    //3. Si después todavía queda content:
    printf(RED"new_len_word = %d\n"RESET_COLOR, new_len_word);
    if (new_len_word != 0) //si todavía hay más contenido, Rest info is copied
    {
        while (w_d->y < keep_new_len_word)
        {
            //printf(MAGENTA"y = %d, len_total = %d\n"RESET_COLOR, x_y.index_y, keep_len);
            w_d->word_to_be_updated[w_d->y] = keep_old_word[ind_old_word]; //hasi dana kopixatzen hasta el dólar
            w_d->dict_quotes_to_be_updated[w_d->y] = keep_old_dict[ind_old_word];
            //printf(BLUE"                   BEHEKUA assigned! [%d] = %c, len_word = %d\n"RESET_COLOR, x_y.index_y, (*box)->rest_info_potential_cmd[x_y.index_x][x_y.index_y], len_new_word);
            ind_old_word++;
            ind_pid_str++;
            new_len_word--;
            w_d->y++;
        }
    }
    //printf("to check, str_src = %s, two_times = %d, ind_old_world = %d, len_new_word = %d\n", str_src, two_times, ind_old_word, len_new_word);        
    //printf("ya hemen, x = %d, y = %d, ind_old_word = %d\n", x_y.index_x, x_y.index_y, ind_old_word);        
    //printf(GREEN"replace_pid_sec_dollar COMPLETED\n"RESET_COLOR);
    //return (w_d);
}

/*
*   Special chars include: 
*       $ : 36 (decimal)
*/
int	is_special_char(char c)
{
	if ((c >= 0 && c <= 47) || (c >= 58 && c <= 64))
	{
		//printf("yes special char = %c\n", c);
		return (1);
	}
	//printf("no special char = %c\n", c);
	return (0);
}

/*get_len_word
*   Returns: len of substr to delete from particular word in rest_info_...(box)
*/
int	get_len_word(char *old_word_before_free, t_x_y_word x_y)
{
	int counter; //len_potential_env_variable_word;
	int len_old_word;

	//printf("get_len_word, x = %d, y = %d\n", x_y.index_x, x_y.index_y);
	counter = 0;
	len_old_word = ft_strlen(old_word_before_free);
	//printf(MAGENTA"chequeito, tmp_old_word_before_free = %s\n"RESET_COLOR, tmp_old_word_before_free);
	//printf(">>>> len_old_word_total = %d\n", len_old_word);
    //printf("len_word = %d, y = %d\n", len_word, x_y.index_y);
	x_y.index_y++; //i = posición de dólar. HUrrengotik hasi bihar gara - Ezta aktualizauko bueltan, eztoulako &-akin bialdu
	//printf("get_len_word, y = %d, len_total = %d\n", x_y.index_y,len_old_word);
	while (x_y.index_y < len_old_word)
	{
		//printf(">>value, old_rest[%d] = %c\n", x_y.index_y, tmp_old_word_before_free[x_y.index_y]);
		if (!is_special_char(old_word_before_free[x_y.index_y]))
		{
			//printf(GREEN"counter++; c = %c\n"RESET_COLOR, tmp_old_word_before_free[x_y.index_y]);
			counter++;
			//x_y.index_y++;
		}
		else
		{
			//printf(RED"didn't count RETURN counter = %d, y = %d, c = %c, len_old_word = %d\n"RESET_COLOR, counter, x_y.index_y, tmp_old_word_before_free[x_y.index_y], len_old_word);
			return (counter);
		}
		if (x_y.index_y == len_old_word)
			break; //safety
		x_y.index_y++;
	}
	//printf(MAGENTA"get_len_word | counter = %d\n"RESET_COLOR, counter);
	return (counter);
}

/*get_len_word_3
*   
*   Same as get_len_word, but instead of tmp_before_free, we use word in (*box)->rest
*   Returns: len of substr to delete from particular word in rest_info_...(box)
*/
int	get_len_word_3(char *word_to_be_updated, t_x_y_word x_y)
{
	int counter; //len_potential_env_variable_word;
	int len_old_word;

	//printf("get_len_word, x = %d, y = %d\n", x_y.index_x, x_y.index_y);
	counter = 0;
	len_old_word = ft_strlen(word_to_be_updated);
	//printf(MAGENTA"chequeito, palabrita = %s\n"RESET_COLOR, (*box)->rest_info_potential_cmd[x_y.index_x]);
	//printf("len_old_word_total = %d\n", len_old_word);
	//printf("len_word = %d, y = %d\n", len_word, x_y.index_y);
	x_y.index_y++; //i = posición de dólar. HUrrengotik hasi bihar gara - Ezta aktualizauko bueltan, eztoulako &-akin bialdu
	//printf("get_len_word, y = %d, len_total = %d\n", x_y.index_y,(int)ft_strlen((*box)->rest_info_potential_cmd[x_y.index_x]));
	while (x_y.index_y < len_old_word)
	{
		//printf(">>value, old_rest[%d] = %c\n", x_y.index_y, tmp_old_word_before_free[x_y.index_y]);
		if (!is_special_char(word_to_be_updated[x_y.index_y]))
		{
			//printf(GREEN"counter++; c = %c\n"RESET_COLOR, tmp_old_word_before_free[x_y.index_y]);
			counter++;
			//x_y.index_y++;
		}
		else
		{
			//printf(RED"didn't count RETURN counter = %d, y = %d, c = %c, len_old_word = %d\n"RESET_COLOR, counter, x_y.index_y, tmp_old_word_before_free[x_y.index_y], len_old_word);
			return (counter);
		}
		if (x_y.index_y == len_old_word)
			break; //safety
		x_y.index_y++;
	}
	//printf(MAGENTA"get_len_word | counter = %d\n"RESET_COLOR, counter);
	return (counter);
}