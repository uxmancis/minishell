/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   02_boxes_7_dollar_4.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uxmancis <uxmancis@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 17:58:01 by uxmancis          #+#    #+#             */
/*   Updated: 2024/06/09 10:37:16 by uxmancis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../inc/minishell.h"

/*get_len_word
*   Returns: len of substr to delete from particular word in rest_info_...(box)
*/
int get_len_word_2(t_box **box, t_x_y_rest_info x_y, int len_old_total_word, char *old_word_2_check)
{
    int counter; //len_potential_env_variable_word;
    //int len_word;
    
    //printf("get_len_word_2, x = %d, y = %d\n", x_y.index_x, x_y.index_y);
    
    (void)box;
    counter = 0;
    //printf("len_old_word = %d\n", len_old_total_word);
    x_y.index_y++; //i = posición de dólar. HUrrengotik hasi bihar gara - Ezta aktualizauko bueltan, eztoulako &-akin bialdu
    //printf("\n          get_len_word | x = %d, y = %d, len = %d\n", x_y.index_x, x_y.index_y, len_old_total_word);
    while (x_y.index_y < len_old_total_word && ft_isalnum(old_word_2_check[x_y.index_y]))
    {
        // printf(MAGENTA"x = %d, y = %d\n"RESET_COLOR, x_y.index_x, x_y.index_y);
        // printf("old_word_to_check[%d] = %c\n", x_y.index_y, old_word_2_check[x_y.index_y]);
        // //if (!ft_isalnum((*box)->rest_info_potential_cmd[x_y.index_x][x_y.index_y]))
        //     //break;
        // if (ft_isalnum(old_word_2_check[x_y.index_y]))
        // {
        counter++;
        // }
        // else
        //     break;
        x_y.index_y++;
        
    }
    //printf(GRAY"len_word = %d\n"RESET_COLOR, counter);
    return (counter);
}

/*
*   str_src = tmp_old_word_before_free 
*/
void replace_delete(t_box **box, char *str_src, t_x_y_rest_info x_y, int len_new_total_word)
{
    int len_to_delete;
    int ind_src;
    int index_dollar;

    len_to_delete = get_len_word(box, x_y, str_src); 
    //len_new_total_word = ft_strlen((*box)->rest_info_potential_cmd[x_y.index_x]);
    ind_src = 0;
    index_dollar = x_y.index_y; //guardamos esta posición...
    x_y.index_y = 0; //...luego la seteamos a 0 para poder hacer bucle con ella
    printf("replace_delete, new_len = %d, str_src = "YELLOW"%s"RESET_COLOR" index_dollar = %d, len_to_delete = %d, ind_src = %d\n", len_new_total_word, str_src, index_dollar, len_to_delete, ind_src);
    while (len_new_total_word > 0)
    {
        printf("ind_src = %d, index_dollar = %d, len_to_delete ="YELLOW" %d\n\n"RESET_COLOR, ind_src, index_dollar, len_to_delete);
        if (ind_src == index_dollar) //si coincide con la posición del dólar recibida desde x_y
        {
            ind_src++;
            while (len_to_delete > 0)
            {
                ind_src++;
                len_to_delete--;
            }
        }
        printf("ind_src = %d\n", ind_src);
        (*box)->rest_info_potential_cmd[x_y.index_x][x_y.index_y] = str_src[ind_src]; //aquellas Y que son del que hay que borrar, no se llegan a copiar en el nuevo rest_...
        //printf(GREEN"                   assigned! rest_info_potential_cmd[%d][%d] = %c\n", x_y.index_x, x_y.index_y, (*box)->rest_info_potential_cmd[x_y.index_x][x_y.index_y]);
        ind_src++;
        len_new_total_word--;
        x_y.index_y++;
    }
    //printf(GREEN"x = %d\n"RESET_COLOR, x_y.index_x);
    //printf("after: %s\n", (*box)->rest_info_potential_cmd[x_y.index_x]);
}

size_t	tmp_ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	printf("ft_strlen, str = '%s'\n", str);
	while (str[i] != '\0')
	{
		printf(">>> str[%d] = %c\n", (int)i, str[i]);
		i++;
	}
	printf("ft_strlen result, counter = %d\n", (int)i);
	return (i);
}

void mng_to_replace_delete(t_box **box, t_x_y_rest_info x_y, t_prompt **prompt)
{
    int len_old_total_word;
    char *tmp_rest_info_before_free;
    int new_len;
    int len_word;

    //IF CONTAINS NON ASCII --> RETURN

    //printf("     mng_to_replace_delete\n");
    (void)prompt;
    //1. Guardar contenido original en tmp_rest_info_before_free
    len_old_total_word = tmp_ft_strlen((*box)->rest_info_potential_cmd[x_y.index_x]);
    printf(GREEN"word = '%s'\n"RESET_COLOR, (*box)->rest_info_potential_cmd[x_y.index_x]);
    printf("          len_old_total_word = %d\n", len_old_total_word);
    tmp_rest_info_before_free = malloc(sizeof(char)*(len_old_total_word + 1));
    tmp_rest_info_before_free[len_old_total_word] = '\0';
    cpy_word((*box)->rest_info_potential_cmd[x_y.index_x], &tmp_rest_info_before_free);
    printf("keep it before free: "YELLOW"%s\n"RESET_COLOR, tmp_rest_info_before_free);
    
    //2. Liberar antigua memoria
    ft_free((*box)->rest_info_potential_cmd[x_y.index_x]);

    //3. Guardar nueva memoria
    len_word = get_len_word_2(box, x_y, len_old_total_word, tmp_rest_info_before_free);
    //printf("len_old_total_word = %d, len_word = %d\n", len_old_total_word, len_word);
    new_len = len_old_total_word - 1 - len_word; //-1 quitar 1 dólar, -len_word
    //printf(YELLOW"new_len = %d"RESET_COLOR" (len_old - 1 dólar - len_word)\n", new_len);
    //if ((*box)->rest_info_potential_cmd[x_y.index_x])
        //ft_free((*box)->rest_info_potential_cmd[x_y.index_x]);
    //printf("x = %d\n", x_y.index_x);
    //printf("yepe yepe\n");
    (*box)->rest_info_potential_cmd[x_y.index_x] = malloc(sizeof(char) * (new_len + 1)); //+1 valor nulo
    (*box)->rest_info_potential_cmd[x_y.index_x][new_len] = '\0';
    replace_delete(box, tmp_rest_info_before_free, x_y, new_len);
}

/*
*   
*/
void cpy_arr_with_len(int *arr_src, int *arr_dst, int len)
{
    int i;
    int two_times;

    i = 0;
    two_times = 0;
    //printf(GREEN"cpy_arr_with_len\n"RESET_COLOR);
    while (len > 0)
    {
        if ((*arr_src)[i] == '$' && two_times != 2) //solo quiero que pase de 2 dólares, si hay más luego noo
        {
            i++;
            two_times++;
            //printf(BLUE"hellowis\n"RESET_COLOR);
        }
        arr_dst[i] = (*arr_src)[i];
        //printf(GREEN"arr_src[%d] = %c\n"RESET_COLOR, i, (*arr_src)[i]);
        i++;
        len--;
    }
}

void fill_with_nine(int **tmp_dict_quotes_word, int len)
{
    int i; 

    //printf(GREEN"     fill_with_nine"RESET_COLOR" | len = %d\n", len);
    i = 0;
    while (len > 0)
    {
        //printf("len = %d\n", len);
        (*tmp_dict_quotes_word)[i] = 9;
        //printf("assigned!\n");
        i++;
        len--;
    }
}