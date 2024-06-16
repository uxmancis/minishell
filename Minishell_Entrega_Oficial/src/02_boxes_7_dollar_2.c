/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   02_boxes_7_dollar_2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uxmancis <uxmancis@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 17:55:05 by uxmancis          #+#    #+#             */
/*   Updated: 2024/06/16 14:44:48 by uxmancis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	cpy_arr_with_len_2(int *arr_src, int **arr_dst, int len)
{
	int	i;

	i = 0;
	while (len > 0)
	{
		(*arr_dst)[i] = arr_src[i];
		i++;
		len--;
	}
}

void	replace_env(char **word_to_be_updated, t_x_y_word x_y, char *tmp_val, int **tmp_dict_quotes_word)
{
    int ind_new_word;
    char *tmp_old_word_before_free;
    int new_len;
    int ind_dollar;
    int ind_old_word;
    int len_val;
    int ind_val;
    int keep_len_new_word;
    char *str_to_find;
    int len_str_to_find;
    int len_old_word;
    int *keep_old_dict_quotes_word;

    ind_new_word = 0;
    
    //1st: copy old info (old word in rest_info y la palabra a buscar)
        //1.1.- Old_word
    len_old_word = ft_strlen(*word_to_be_updated);
    tmp_old_word_before_free = malloc(sizeof(char) * (ft_strlen(*word_to_be_updated) + 1));
    tmp_old_word_before_free[ft_strlen(*word_to_be_updated)] = '\0';
    get_old_word(*word_to_be_updated, &tmp_old_word_before_free); //tmp_old_word_before_free ya lo tee
        //1.2.- Old_dictionary
    keep_old_dict_quotes_word = malloc(sizeof(int) * len_old_word);
    cpy_arr_with_len_2(*tmp_dict_quotes_word, &keep_old_dict_quotes_word, len_old_word); //old info is stored to be copied after keep_old_dict_quotes_word
    str_to_find = get_word_2(tmp_old_word_before_free, x_y);
    len_str_to_find = ft_strlen(str_to_find);
    
    //printf("                         old word to keep = %s\n", tmp_old_word_before_free);

    //2. Hacer free de la info antigua
        //2.1.- Old_word
    //ft_free(*word_to_be_updated);
    if (*word_to_be_updated)
    {
        free(*word_to_be_updated);
        *word_to_be_updated = NULL;
    }
        //2.2.- Old_dictionary
    //ft_free(*tmp_dict_quotes_word);
    if (*tmp_dict_quotes_word)
    {
        free (*tmp_dict_quotes_word);
        *tmp_dict_quotes_word = NULL;
    }
    
    //3. Generate new information
    new_len = ft_strlen(tmp_old_word_before_free) - 1 - ft_strlen(str_to_find) + ft_strlen(tmp_val);
        //3.1.- New word
    //printf(GREEN"new_len = %d\n"RESET_COLOR, new_len);
    *word_to_be_updated = malloc(sizeof(char)*(new_len + 1));
    (*word_to_be_updated)[new_len] = '\0';
    *tmp_dict_quotes_word = malloc(sizeof(int) * new_len); //new dictionary
    
    
    ind_dollar = x_y.index_y;
    x_y.index_y = 0; //tengo sesnsación-intuición de que esta y = index_new_word
    ind_old_word = 0;
    len_val = ft_strlen(tmp_val);
    ind_val = 0;
    keep_len_new_word = new_len;
    
    //printf("                         new_len = %d, keep_new_len = %d\n", new_len, keep_len_new_word);
    /*while (new_len > 0)
    {*/
    
    //cpy_arr_with_len(*tmp_dict_quotes_word, new_dict_quotes_word, (len_old_word - 2));
        //1. si antes del dólar hay cositas, copiarlas
        if (ind_new_word < ind_dollar) //if to debug, print just in this case, but only once (outside of while loop)
        {
            while (ind_new_word < ind_dollar /*&& new_len > 0*/) //lo de new_len es una manera de prevent overflow
            {
                (*word_to_be_updated)[x_y.index_y] = tmp_old_word_before_free[ind_old_word];
                (*tmp_dict_quotes_word)[x_y.index_y] = keep_old_dict_quotes_word[ind_old_word];
                //printf(RED"assigned to update dictionary\n"RESET_COLOR);
                ind_new_word++;
                ind_old_word++;
                x_y.index_y++;
                new_len--;
            }
            //printf("                         1st step BEFORE dollar completed, str = "BLUE"%s"RESET_COLOR", %d len left\n", (*box)->rest_info_potential_cmd[x_y.index_x], keep_len_new_word - new_len);
        } 
        
        //2. una vez llegamos a la posición del dólar
        if (ind_new_word == ind_dollar)
        {
            //ind_old_word++; // pasar del dólar
            while (len_str_to_find > 0)
            {
                ind_old_word++; //de la palabra "USER" también vamos a pasar
                len_str_to_find--;
            }
            while (len_val > 0)
            {
                //printf("y = %d, ind_val = %d\n", x_y.index_y, ind_val);
                (*word_to_be_updated)[x_y.index_y] = tmp_val[ind_val]; //aquí se asigna la palabra, so diccionario es = 0
                (*tmp_dict_quotes_word)[x_y.index_y] = 0;
                //printf(GRAY"assigned to update dictionary\n"RESET_COLOR);
                ind_val++;
                x_y.index_y++;
                len_val--;
            }
            //printf("                         2nd step REPLACE dollar with ENV VAR completed, str = "BLUE"%s"RESET_COLOR", %d len left\n", (*box)->rest_info_potential_cmd[x_y.index_x], keep_len_new_word - new_len);

        }

        //3. Si todavía hay más info después de val
        //printf("3. more info after expansion, y = %d, total_len_new_word = %d\n", x_y.index_y, keep_len_new_word);
        if (x_y.index_y < keep_len_new_word) //if to debug, print just in this case, but only once (outside of while loop)
        {
            ind_old_word++; //hurrengora
            //printf("                              Step 3: y = %d, len_total = %d\n", x_y.index_y, keep_len_new_word);
            while (x_y.index_y < keep_len_new_word)
            {
                (*word_to_be_updated)[x_y.index_y] = tmp_old_word_before_free[ind_old_word];
                //printf("                              assigned! [%d][%d] = %c\n", x_y.index_x, x_y.index_y,(*box)->rest_info_potential_cmd[x_y.index_x][x_y.index_y]);
                (*tmp_dict_quotes_word)[x_y.index_y] = keep_old_dict_quotes_word[ind_old_word];
                //printf(RED"2- assigned to update dictionary\n"RESET_COLOR);
                x_y.index_y++;
                ind_old_word++;
            }
            //printf("                         3rd step AFTER dollar completed, str = "BLUE"%s"RESET_COLOR", %d len left\n", (*box)->rest_info_potential_cmd[x_y.index_x], keep_len_new_word - new_len);
        }
        //new_len--;
    //}
}

/*get_word_2
*
*   Returns: char *env_variable = the word we will aim to find in env.
*
*
*   Called from is_in_env
*/
char	*get_word_2(char *old_word_before_free, t_x_y_word x_y)
{
	char	*env_variable;
	int		len_word;
	int		x;

	(void)old_word_before_free;
	if (old_word_before_free)
		len_word = get_len_word(old_word_before_free, x_y);
	else
		len_word = get_len_word_3(old_word_before_free, x_y);
	env_variable = malloc(sizeof(char) * (len_word + 1));
	env_variable[len_word] = '\0';
	x_y.index_y++;
	x = 0;
	while (len_word > 0)
	{
		env_variable[x] = old_word_before_free[x_y.index_y];
		len_word--;
		x++;
		x_y.index_y++;
	}
	return (env_variable);
}

/*get_word_2
*
*   Returns: char *env_variable = the word we will aim to find in env.
*
*
*   Called from is_in_env
*/
char	*get_word_4(char *old_word_before_free, t_x_y_word x_y)
{
	char	*env_variable;
	int		len_word;
	int		x;

	if (old_word_before_free)
		len_word = get_len_word(old_word_before_free, x_y);
	else
		len_word = get_len_word_3(old_word_before_free, x_y);
	if (len_word == 0)
		return (NULL);
	env_variable = malloc(sizeof(char) * (len_word + 1));
	env_variable[len_word] = '\0';
	x_y.index_y++; //i = dolarran posiziñua. Hurrengotik hasi bihar gara
	x = 0;
	while (len_word > 0)
	{
		env_variable[x] = old_word_before_free[x_y.index_y];
		len_word--;
		x++;
		x_y.index_y++;
	}
	return (env_variable);
}

void	cpy_to_val(char *str_src, char **str_dst)
{
	int	len;
	int	i;

	len = ft_strlen(str_src);
	i = 0;
	while (len > 0)
	{
		(*str_dst)[i] = str_src[i];
		len--;
		i++;
	}
}
