/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   02_boxes_7_dollar_3.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uxmancis <uxmancis@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 17:55:40 by uxmancis          #+#    #+#             */
/*   Updated: 2024/06/15 18:10:33 by uxmancis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../inc/minishell.h"

/*
*   tmp_dict_quotes_word has already new_len.
*
*   Was initialized with 9 value in its whole new_len.
*
*   0s were assigned in pid value indexes.
*
*   Rest info (still with 9 values) we'll get it from old/previous tmptmp_dict_quotes,
*   we used it to keep info of tmp_dict_quotes_word before it got new_len.
*
*   Variables:
*       tmp_dict_quotes_word: New arr to get updated
*/
void finish_to_update_dict_quotes (int **tmp_dict_quotes_word, int new_len, int *tmp_tmp_dict_quotes_word, int len_old_word)
{
    int i;
    int index_old_dict;

    //printf("finish_to_update_dict_quotes, new_len = %d, len_word = %d\n", new_len, len_old_word);
    i = 0;
    index_old_dict = 0;
    //index_old_dict = 0;
    //(void)tmp_tmp_dict_quotes_word;
    //(void)new_len;
    //len_old_word y número valores que todavía tienen 9 asignado tienen relación y siempre se entiende que deberán cuadrar perfe
    while (new_len > 0)
    {
        if ((*tmp_dict_quotes_word)[i] == 9)
        {
            (*tmp_dict_quotes_word)[i] = tmp_tmp_dict_quotes_word[index_old_dict];
            //printf(BLUE"         assigned value! tmp_dict_quotes[%d] = %d\n"RESET_COLOR, i, (*tmp_dict_quotes_word)[i]);
            index_old_dict++;
        }
        i++;
        len_old_word--;
        new_len--;
        //printf("                  len_old_word = %d, new_len = %d, i = %d, index_old_dict = %d\n", len_old_word, new_len, i, index_old_dict);
    }
    //printf("done: finish_to_update_dict_quotes\n");
}

void put_arr(int *arr, int len)
{
    int i; 

    i = 0;
    while (len > 0)
    {
        printf(YELLOW"%d", arr[i]);
        i++;
        len--;
    }
    printf(RESET_COLOR);
}

/*mng_to_replace_sec_dollar
*
*   particular word in (*box)->rest_info_potencial_cmd is updated
*   tmp_dict_quotes_word is updated
*/
void	mng_to_replace_sec_dollar(t_box **box, t_x_y_rest_info x_y, int **tmp_dict_quotes_word)
{
	int		len_old_word;
	int		len_process_pid;
	char	*tmp_rest_info_before_free; //to keep info
	int		new_len;
	int		*keep_dict_quotes_word; //to keep info

    printf(YELLOW"mng_to_replace_sec_dollar\n"RESET_COLOR);
    
    //1. Keep old info in tmp variables: char *tmp_rest_info_before_free, pero quitándole los 2 dólares que no necesitamos, and int *tmp_tmp_dict_quotes_word;
    len_old_word = ft_strlen((*box)->rest_info_potential_cmd[x_y.index_x]);
    //printf("len_old_word = %d\n", len_old_word);
        //1.1.- keep Old word
    tmp_rest_info_before_free = malloc(sizeof(char)*(len_old_word + 1));
    tmp_rest_info_before_free[len_old_word] = '\0';
    cpy_word((*box)->rest_info_potential_cmd[x_y.index_x], &tmp_rest_info_before_free);
        //1.2.- keep old dictionary
    keep_dict_quotes_word = malloc(sizeof(int)*len_old_word); //no necesitamos +1 para valor nulo, le acabo de añadir -2 porque no vamos a meter info de los 2 dólares que queremos quitar                  
    cpy_arr_with_len_2(*tmp_dict_quotes_word, &keep_dict_quotes_word, len_old_word); //to keep old tmp_dict_quotes_word (because we'll generate a new one)
    
    //2. Free old info
        //2.1.- Free old word
    if ((*box)->rest_info_potential_cmd[x_y.index_x])
    {
        free ((*box)->rest_info_potential_cmd[x_y.index_x]);
        (*box)->rest_info_potential_cmd[x_y.index_x] = NULL;
    }
        //2.2.- Free old dictionary
    if (*tmp_dict_quotes_word)
    {
        free(*tmp_dict_quotes_word); //ya lo hemos guardado en tmp_tmp_dict_quotes_word - ¿me está generando segfault?
        *tmp_dict_quotes_word = NULL;
    }
    //printf("     tmp_tmp_dict_quotes_word = ");
    //put_arr(tmp_tmp_dict_quotes_word, len_old_word); //to debug
    //printf("\n");

    
    //2. Get new info
    len_process_pid = get_len_pid(box);
    printf("                    len_process_pid = %d, len_old_word = %d\n", len_process_pid, len_old_word);
    new_len = len_old_word - 2 + len_process_pid; //-2 por quitar los 2 dólares
    printf(MAGENTA"                    new_len = %d\n"RESET_COLOR, new_len);
    *tmp_dict_quotes_word = malloc(sizeof(int) * new_len); //no necesitamos +1 para valor nulo
    (*tmp_dict_quotes_word)[0] = 1;
    printf("probatxue, [0] = %d\n", (*tmp_dict_quotes_word)[0]);
    //if (!tmp_dict_quotes_word)
        //ft_puterror("Error when allocating memory\n");
    //fill_with_nine(tmp_dict_quotes_word, new_len); //random value 9 to initialize, 9 is not possible in 
    //printf("                    mng_to_replace_sec_dollar - Before rest_info_potential_cmd[%d][%d] = %s, len_old = %d, len_pid = %d, new_len = %d\n", x_y.index_x,x_y.index_y, (*box)->rest_info_potential_cmd[x_y.index_x], len_old_word, len_process_pid, new_len);
    //printf("\n          tmp_rest_info_before_free = "YELLOW"%s"RESET_COLOR" | keep it to cpy, new_len = %d\n", tmp_rest_info_before_free, new_len);
    (*box)->rest_info_potential_cmd[x_y.index_x] = ft_calloc(new_len + 1, sizeof(char));
    (*box)->rest_info_potential_cmd[x_y.index_x][new_len] = '\0';
    replace_pid_sec_dollar(box, x_y, tmp_rest_info_before_free, keep_dict_quotes_word, tmp_dict_quotes_word, new_len);
    //printf(">>  let's finish it!\n");
    finish_to_update_dict_quotes(tmp_dict_quotes_word, new_len, keep_dict_quotes_word, len_old_word);
}

/*  is_in_env
*
*   Checks whether if WORD is found along variables in environment (list).
*
*   ft_get_env_local(xxx, str_to_find)
*       E.g.: ft_get_env_local(data->vars, "USER")
*/
int	is_in_env(t_box **box, t_x_y_rest_info x_y, t_prompt **prompt)
{
	//printf("\n\n                         is word in env? ");
	if (ft_getenv_local((*prompt)->vars, get_word_2(box, x_y, NULL)))
	{
		printf("                         is word in env?"GREEN" YES\n"RESET_COLOR);
		return (1);
	}
	printf("                         is word in env?"RED" NO\n"RESET_COLOR);  
	return (0);
}

void	get_old_word(char *str_src, char **str_dst)
{
	int	len_src;
	int	i;

	len_src = ft_strlen(str_src);
	i = 0;
	while (len_src > 0)
	{
		(*str_dst)[i] = str_src[i];
		len_src--;
		i++;
	}
}
