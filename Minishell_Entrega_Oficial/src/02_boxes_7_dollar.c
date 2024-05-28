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


void ft_free(void *arr)
{
    free (arr);
    arr = NULL;
}

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

/*  Assigns values to tmp_dict_quotes_word based on start value.
*   
*   start value is taken from index_beggining_words_rest (box).
*
*/
void fill_tmp_dict_quotes(t_box **box, int **tmp_dict_quotes_word, int len, int start)
{
    int i;
    
    i = 0;
    //printf(YELLOW"     fill_tmp_dict_quotes"RESET_COLOR"| start = %d, len = %d\n", start, len);
    while (len > 0) //Next to solve: aquí tmp_dict_quotes_word no está llegando con su nuevo len
    {
        (*tmp_dict_quotes_word)[i] = (*box)->dict_quotes[start];
        //printf("          tmp_dict_qotes[%d] = %d\n", i, (*tmp_dict_quotes_word)[i]);
        len--;
        i++;
        //start++;
    }
}

/*Checks whether if dollar is found outside of quotes
*   or inside double quotes (inside single quotes is a no).
*
*   I could just say tmp_dict_quotes[i] != 1.
*   I just feel == 0 || == 2 is a little safer though.
*
*   tmp_to_compare = (*box)->rest_info_potential_cmd word, but
*   the updated version. P.ej.: imagine it's already been updated 
*   because ofother dollars before
*/
int is_dollar(t_box **box, t_x_y_rest_info x_y, int **tmp_dict_quotes)
{
    //printf("     "YELLOW"is_dollar"RESET_COLOR" | rest_info_potential_cmd[%d][%d] = %c\n", x_y.index_x, x_y.index_y, (*box)->rest_info_potential_cmd[x_y.index_x][x_y.index_y]);
    //printf("     tmp_dict_quotes[%d]= %d\n", x_y.index_y, (*tmp_dict_quotes)[x_y.index_y]);
    //if (tmp_to_compare[x_y.index_y] == '$' && (tmp_dict_quotes[x_y.index_y] == 0 || tmp_dict_quotes[x_y.index_y] == 2))
    if ((*box)->rest_info_potential_cmd[x_y.index_x][x_y.index_y] == '$' && ((*tmp_dict_quotes)[x_y.index_y] == 0 || (*tmp_dict_quotes)[x_y.index_y] == 2))
        return (1);
    return (0);
}

int next_is_space_or_end (t_box **box, t_x_y_rest_info x_y)
{
    int len_word;

    len_word = ft_strlen((*box)->rest_info_potential_cmd[x_y.index_x]);
    if (x_y.index_y == len_word - 1) //END: $ in las position
        return (1);
    if ((x_y.index_y + 1) < len_word) //SPACE: si todavía sí hay más posiciones (a way to prevent overflow), then check if próxima posición es un ' '
    {
        if ((*box)->rest_info_potential_cmd[x_y.index_x][x_y.index_y + 1] == ' ')
            return (1);
    }
    return (0);
}

int next_is_sec_dollar(t_box **box, t_x_y_rest_info x_y)
{
    int len_word;

    //printf("next_is_sec_dollar | rest_info_potential_cmd[%d][%d] = %c\n", x_y.index_x, x_y.index_x, (*box)->rest_info_potential_cmd[x_y.index_x][x_y.index_y]);
    len_word = ft_strlen((*box)->rest_info_potential_cmd[x_y.index_x]);
    if ((x_y.index_y + 1) < len_word) //a way to prevent overflow
    {
        if ((*box)->rest_info_potential_cmd[x_y.index_x][x_y.index_y + 1] == '$')
        {
            printf("second dollar identified!\n");
            return (1);
        }
    }
    printf("no second dollar\n");
    return (0);
}

void cpy_word (char *str_src, char **str_dst)
{
    int len;
    int i;

    len = ft_strlen(str_src);
    i = 0;
    while (len > 0)
    {
        (*str_dst)[i] = str_src[i];
        i++;
        len--;
    }
    //printf("               str_dst = "YELLOW"%s\n"RESET_COLOR, *str_dst);
}

int get_len_pid (t_box **box)
{
    //pid_t pid;
    int len_process_pid;

    (*box)->tmp_pid = getpid();
    (*box)->tmp_pid_str = basic_itoa((*box)->tmp_pid);
    len_process_pid = ft_strlen((*box)->tmp_pid_str);
    return (len_process_pid);
}

/* replace with pid
*
*   Also new dict_quotes is generated (so than we can use it to check if no_more_dollars)
*/
void replace_pid_sec_dollar(t_box **box, t_x_y_rest_info x_y, char *str_src, int **tmp_dict_quotes_word, int len_new_word)
{
    //int len_new_word;
    int len_pid_str;
    int ind_pid_str;
    int ind_old_word;
    int two_times;
    int ind_dollar;
    int keep_len;

    //fill_tmp_dict_quotes(box, &tmp_dict_quotes_word, len_word, (*box)->index_beginning_words_rest[nb_word_x]);
    //printf("          replace_pid_sec_dollar | str_src = "YELLOW"%s"RESET_COLOR" - keepin' it | where is dollar, ind [%d]\n", str_src, x_y.index_y);
    //len_new_word = ft_strlen((*box)->rest_info_potential_cmd[x_y.index_x]);
    //printf(MAGENTA"                    len_new_word = %d\n"RESET_COLOR, len_new_word);
    len_pid_str = ft_strlen((*box)->tmp_pid_str);
    ind_dollar = x_y.index_y;
    x_y.index_y = 0;
    ind_old_word = 0;
    keep_len = len_new_word;
    ind_pid_str = 0;
    /*while (len_new_word > 0)
    {
        printf(MAGENTA"Comenzamos! ¿Es aquí el dólar donde sustituir por pid?\n"RESET_COLOR);
        printf("bucle, x = %d, y = %d, len = %d\n", x_y.index_x, x_y.index_y, len_new_word);*/
    //printf(YELLOW"ind_pid_str = %d, ind_dollar = %d\n"RESET_COLOR, ind_pid_str, ind_dollar);
    
    
    //1. Hasta el $, simplemente copia
    while (ind_pid_str != ind_dollar)
    {
        (*box)->rest_info_potential_cmd[x_y.index_x][x_y.index_y] = str_src[ind_old_word]; //hasi dana kopixatzen hasta el dólar
        ind_pid_str++; //para que luego cojamos bien desde el dólar
        ind_old_word++;
        x_y.index_y++;
    }
    
    //2. Una vez encontramos el dólar, sustituimos
    if (ind_pid_str == ind_dollar) //un poquito redundante, y un poquito jugón el bucle anterior. En mi cabeza tiene que darse siempre ok, pero imagínate que no.. posible bucle infinito? jaj
    {
        //printf(GREEN" YES!\n"RESET_COLOR);
        //printf("\n          yes! dollar is here, len = %d\n", len_pid_str);
        ind_pid_str = 0;
        while (len_pid_str > 0)
        {   
            //printf(YELLOW"willing to assign😊 | x = %d, y = %d, ind_pid_str = %d\n", x_y.index_x, x_y.index_y, ind_pid_str);
            (*box)->rest_info_potential_cmd[x_y.index_x][x_y.index_y] = (*box)->tmp_pid_str[ind_pid_str];
            (*tmp_dict_quotes_word)[x_y.index_y] = 0;
            //printf(BLUE"                  GOIKUA assigned! [%d] = %c\n"RESET_COLOR, x_y.index_y, (*box)->rest_info_potential_cmd[x_y.index_x][x_y.index_y]);
            ind_pid_str++;
            len_pid_str--;
            x_y.index_y++;
            len_new_word--;
            //printf("len_word = %d, len_pid_str = %d, ind_pid_str = %d, y = %d\n", len_new_word, len_pid_str, ind_pid_str, x_y.index_y);
        }
        //saltarnos los 2 dólares
        two_times = 0;
        while (two_times != 2 && ind_old_word < keep_len && str_src[ind_old_word] == '$'/* && ind_old_word == ind_dollar*/) //para saltarnos y no copiar los 2 dólares && safety to prevent overflow
        {
            ind_old_word++;
            two_times++;
            //printf(RED"PASAR DEL DOLAR AL COPIAR\n"RESET_COLOR);
        }
    }
        //😊😊😊😊si hay un momento en el que después de 1 dólar no hay otro dólar, en ese caso termina de copiarlo todo, y salte de aquí
        
    //printf(GREEN" No, \n"RESET_COLOR);
    //printf("          status check: len = %d\n", len_new_word);
    
    //3. Si después todavía queda content:
    if (len_new_word != 0) //si todavía hay más contenido, Rest info is copied
    {
        while (x_y.index_y < keep_len)
        {
            //printf(MAGENTA"y = %d, len_total = %d\n"RESET_COLOR, x_y.index_y, keep_len);
            (*box)->rest_info_potential_cmd[x_y.index_x][x_y.index_y] = str_src[ind_old_word]; //hasi dana kopixatzen hasta el dólar
            //printf(BLUE"                   BEHEKUA assigned! [%d] = %c, len_word = %d\n"RESET_COLOR, x_y.index_y, (*box)->rest_info_potential_cmd[x_y.index_x][x_y.index_y], len_new_word);
            ind_old_word++;
            ind_pid_str++;
            len_new_word--;
            x_y.index_y++;
        }
    }
    //printf("to check, str_src = %s, two_times = %d, ind_old_world = %d, len_new_word = %d\n", str_src, two_times, ind_old_word, len_new_word);        
    //printf("ya hemen, x = %d, y = %d, ind_old_word = %d\n", x_y.index_x, x_y.index_y, ind_old_word);        
    //printf(GREEN"replace_pid_sec_dollar COMPLETED\n"RESET_COLOR);
}
int is_special_char(char c)
{
    if (c >= 0 && c <= 47)
        return (1);
    return (0);
}

/*get_len_word
*   Returns: len of substr to delete from particular word in rest_info_...(box)
*/
int get_len_word(t_box **box, t_x_y_rest_info x_y)
{
    int counter; //len_potential_env_variable_word;
    int len_word;

    printf("get_len_word, x = %d, y = %d\n", x_y.index_x, x_y.index_y);
    counter = 0;
    len_word = ft_strlen((*box)->rest_info_potential_cmd[x_y.index_x]);
    printf("len_word = %d, y = %d\n", len_word, x_y.index_y);
    x_y.index_y++; //i = posición de dólar. HUrrengotik hasi bihar gara - Ezta aktualizauko bueltan, eztoulako &-akin bialdu
    while (x_y.index_y < len_word)
    {
        if ((*box)->rest_info_potential_cmd[x_y.index_x][x_y.index_y] !='$' && !is_special_char((*box)->rest_info_potential_cmd[x_y.index_x][x_y.index_y]))
        {
            counter++;
            x_y.index_y++;
        }
        printf("y = %d, len_word = %d\n", x_y.index_y, len_word);
        if (x_y.index_y == len_word)
            break; //safety
        x_y.index_y++;
    }
    printf("counter = %d\n", counter);
    return (counter);
}

/*get_len_word
*   Returns: len of substr to delete from particular word in rest_info_...(box)
*/
int get_len_word_2(t_box **box, t_x_y_rest_info x_y, int len_old_total_word)
{
    int counter; //len_potential_env_variable_word;
    //int len_word;
    
    //printf("get_len_word_2, x = %d, y = %d\n", x_y.index_x, x_y.index_y);
    
    (void)box;
    counter = 0;
    //printf("len_old_word = %d\n", len_old_total_word);
    x_y.index_y++; //i = posición de dólar. HUrrengotik hasi bihar gara - Ezta aktualizauko bueltan, eztoulako &-akin bialdu
    //printf("\n          get_len_word | x = %d, y = %d, len = %d\n", x_y.index_x, x_y.index_y, len_old_total_word);
    while (x_y.index_y < len_old_total_word)
    {
        counter++;
        x_y.index_y++;
    }
    //printf("len_word = %d\n", counter);
    return (counter);
}


void replace_delete(t_box **box, char *str_src, t_x_y_rest_info x_y, int len_new_total_word)
{
    int len_to_delete;
    int ind_src;
    int index_dollar;

    len_to_delete = get_len_word(box, x_y) + 1; //+1: dolarra ere kenduko doulako
    //len_new_total_word = ft_strlen((*box)->rest_info_potential_cmd[x_y.index_x]);
    ind_src = 0;
    //printf("replace_delete, new_len = %d, str_src = "YELLOW"%s\n"RESET_COLOR, len_new_total_word, str_src);
    index_dollar = x_y.index_y; //guardamos esta posición...
    x_y.index_y = 0; //...luego la seteamos a 0 para poder hacer bucle con ella
    while (len_new_total_word > 0)
    {
        if (ind_src == index_dollar) //si coincide con la posición del dólar recibida desde x_y
        {
            while (len_to_delete > 0)
            {
                ind_src++;
                len_to_delete--;
            }
        }
        (*box)->rest_info_potential_cmd[x_y.index_x][x_y.index_y] = str_src[ind_src]; //aquellas Y que son del que hay que borrar, no se llegan a copiar en el nuevo rest_...
        //printf(GREEN"                   assigned! rest_info_potential_cmd[%d][%d] = %c\n", x_y.index_x, x_y.index_y, (*box)->rest_info_potential_cmd[x_y.index_x][x_y.index_y]);
        ind_src++;
        len_new_total_word--;
        x_y.index_y++;
    }
    printf(GREEN"x = %d\n"RESET_COLOR, x_y.index_x);
    //printf("after: %s\n", (*box)->rest_info_potential_cmd[x_y.index_x]);
}

void mng_to_replace_delete(t_box **box, t_x_y_rest_info x_y, t_prompt **prompt)
{
    int len_old_total_word;
    char *tmp_rest_info_before_free;
    int new_len;
    int len_word;

    //printf("     mng_to_replace_delete\n");
    (void)prompt;
    //1. Guardar contenido original en tmp_rest_info_before_free
    len_old_total_word = ft_strlen((*box)->rest_info_potential_cmd[x_y.index_x]);
    //printf("          len_old_total_word = %d\n", len_old_total_word);
    tmp_rest_info_before_free = malloc(sizeof(char)*(len_old_total_word + 1));
    tmp_rest_info_before_free[len_old_total_word] = '\0';
    cpy_word((*box)->rest_info_potential_cmd[x_y.index_x], &tmp_rest_info_before_free);
    //printf("keep it before free: "YELLOW"%s\n"RESET_COLOR, tmp_rest_info_before_free);
    
    //2. Liberar antigua memoria
    ft_free((*box)->rest_info_potential_cmd[x_y.index_x]);

    //3. Guardar nueva memoria
    len_word = get_len_word_2(box, x_y, len_old_total_word);
    //printf("len_old_total_word = %d, len_word = %d\n", len_old_total_word, len_word);
    new_len = len_old_total_word - 1 - len_word; //-1 quitar 1 dólar, -len_word
    //printf(YELLOW"new_len = %d"RESET_COLOR" (len_old - 1 dólar - len_word)\n", new_len);
    //if ((*box)->rest_info_potential_cmd[x_y.index_x])
        //ft_free((*box)->rest_info_potential_cmd[x_y.index_x]);
    //printf("x = %d\n", x_y.index_x);
    (*box)->rest_info_potential_cmd[x_y.index_x] = malloc(sizeof(char) * (new_len + 1)); //+1 valor nulo
    (*box)->rest_info_potential_cmd[x_y.index_x][new_len] = '\0';
    replace_delete(box, tmp_rest_info_before_free, x_y, new_len);
}

void cpy_arr_with_len(int **arr_src, int *arr_dst, int len)
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

void    mng_to_replace_sec_dollar(t_box **box, t_x_y_rest_info x_y, int **tmp_dict_quotes_word)
{
    int len_old_word;
    int len_process_pid;
    char *tmp_rest_info_before_free; //to keep info
    int new_len;
    int *tmp_tmp_dict_quotes_word; //to keep info

    //printf(YELLOW"mng_to_replace_sec_dollar\n"RESET_COLOR);
    //1. Keep old info in tmp variables: char *tmp_rest_info_before_free, pero quitándole los 2 dólares que no necesitamos, and int *tmp_tmp_dict_quotes_word;
    len_old_word = ft_strlen((*box)->rest_info_potential_cmd[x_y.index_x]);
    tmp_tmp_dict_quotes_word = malloc(sizeof(int)*(len_old_word - 2)); //no necesitamos +1 para valor nulo, le acabo de añadir -2 porque no vamos a meter info de los 2 dólares que queremos quitar                  
    cpy_arr_with_len(tmp_dict_quotes_word, tmp_tmp_dict_quotes_word, (len_old_word - 2)); //to keep old tmp_dict_quotes_word (because we'll generate a new one)
    tmp_rest_info_before_free = malloc(sizeof(char)*(len_old_word + 1));
    tmp_rest_info_before_free[len_old_word] = '\0';
    cpy_word((*box)->rest_info_potential_cmd[x_y.index_x], &tmp_rest_info_before_free);
    //printf("     tmp_tmp_dict_quotes_word = ");
    //put_arr(tmp_tmp_dict_quotes_word, len_old_word); //to debug
    printf("\n");
    free(*tmp_dict_quotes_word); //ya lo hemos guardado en tmp_tmp_dict_quotes_word - ¿me está generando segfault?
    *tmp_dict_quotes_word = NULL;
    
    //2. Get new info
    len_process_pid = get_len_pid(box);
    //printf("                    len_process_pid = %d, len_old_word = %d\n", len_process_pid, len_old_word);
    new_len = len_old_word - 2 + len_process_pid; //-2 por quitar los 2 dólares
    //printf(MAGENTA"                    new_len = %d\n"RESET_COLOR, new_len);
    *tmp_dict_quotes_word = malloc(sizeof(int)*new_len); //no necesitamos +1 para valor nulo
    //if (!tmp_dict_quotes_word)
        //ft_puterror("Error when allocating memory\n");
    fill_with_nine(tmp_dict_quotes_word, new_len); //random value 9 to initialize, 9 is not possible in 
    //printf("                    mng_to_replace_sec_dollar - Before rest_info_potential_cmd[%d][%d] = %s, len_old = %d, len_pid = %d, new_len = %d\n", x_y.index_x,x_y.index_y, (*box)->rest_info_potential_cmd[x_y.index_x], len_old_word, len_process_pid, new_len);
    //printf("\n          tmp_rest_info_before_free = "YELLOW"%s"RESET_COLOR" | keep it to cpy, new_len = %d\n", tmp_rest_info_before_free, new_len);
    free ((*box)->rest_info_potential_cmd[x_y.index_x]);
    (*box)->rest_info_potential_cmd[x_y.index_x] = ft_calloc(new_len + 1, sizeof(char));
    (*box)->rest_info_potential_cmd[x_y.index_x][new_len] = '\0';
    replace_pid_sec_dollar(box, x_y, tmp_rest_info_before_free, tmp_dict_quotes_word, new_len);
    //printf(">>  let's finish it!\n");
    finish_to_update_dict_quotes(tmp_dict_quotes_word, new_len, tmp_tmp_dict_quotes_word, len_old_word);
    //printf(GREEN"uxu we're here\n"RESET_COLOR);
    //printf("tmp_dict_qotes[%d] = %d\n", 0, (*tmp_dict_quotes_word)[0]);
    //printf("tmp_dict_qotes[%d] = %d\n", 1, (*tmp_dict_quotes_word)[1]);
    //printf("tmp_dict_qotes[%d] = %d\n", 2, (*tmp_dict_quotes_word)[2]);
    //printf("tmp_dict_qotes[%d] = %d\n", 3, (*tmp_dict_quotes_word)[3]);
    //printf("tmp_dict_qotes[%d] = %d\n", 4, (*tmp_dict_quotes_word)[4]);

}

char *get_word_2(t_box **box, t_x_y_rest_info x_y)
{
    char *env_variable; //potential
    int len_word;
    int x;

    printf("get_word_2\n");
    len_word = get_len_word(box, x_y);
    printf("          len_word_potential_variable = %d\n", len_word);
    env_variable = malloc(sizeof(char) * (len_word + 1));
    env_variable[len_word] = '\0';
    x_y.index_y++; //i = dolarran posiziñua. Hurrengotik hasi bihar gara
    x = 0;
    while (len_word > 0)
    {
        env_variable[x] = (*box)->rest_info_potential_cmd[x_y.index_x][x_y.index_y];
        len_word--;
        x++;
        x_y.index_y++;
    }
    printf("get_word_2 | word to find in env: %s\n", env_variable);
    return (env_variable);
}

/*  is_in_env
*
*   Checks whether if WORD is found along variables in environment (list).
*
*   ft_get_env_local(xxx, str_to_find)
*       E.g.: ft_get_env_local(data->vars, "USER")
*/
int is_in_env(t_box **box, t_x_y_rest_info x_y, t_prompt **prompt)
{
    printf("          is word in env? ");
    if (ft_getenv_local((*prompt)->vars, get_word_2(box, x_y)))
    {
        printf(GREEN" YES\n"RESET_COLOR);
        return (1);
    }
    printf(RED" NO\n"RESET_COLOR);   
    return (0);
}

void cpy_to_val(char *str_src, char **str_dst)
{
    int len;
    int i;

    len = ft_strlen(str_src);
    i = 0;
    while (len > 0)
    {
        (*str_dst)[i] = str_src[i];
        len--;
        i++;
    }
}

void get_old_word(char *str_src, char **str_dst)
{
    int len_src;
    int i;

    len_src = ft_strlen(str_src);
    i = 0;
    while (len_src > 0)
    {
        (*str_dst)[i] = str_src[i];
        len_src--;
        i++;
    }
}

void replace_env(t_box **box, t_x_y_rest_info x_y, char *tmp_val)
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
    printf("replace_env | x = %d, y = %d\n", x_y.index_x, x_y.index_y);
    ind_new_word = 0;
    
    //1st: copy old info (old word in rest_info y la palabra a buscar)
    tmp_old_word_before_free = malloc(sizeof(char) * (ft_strlen((*box)->rest_info_potential_cmd[x_y.index_x]) + 1));
    tmp_old_word_before_free[ft_strlen((*box)->rest_info_potential_cmd[x_y.index_x])] = '\0';
    get_old_word((*box)->rest_info_potential_cmd[x_y.index_x], &tmp_old_word_before_free); //tmp_old_word_before_free ya lo tee
    str_to_find = get_word_2(box, x_y);
    len_str_to_find = ft_strlen(str_to_find);
    
    //2. Hacer free de la info antigua
    ft_free((*box)->rest_info_potential_cmd[x_y.index_x]);
    new_len = ft_strlen(tmp_old_word_before_free) - 1 - ft_strlen(str_to_find) + ft_strlen(tmp_val);
    (*box)->rest_info_potential_cmd[x_y.index_x] = malloc(sizeof(char)*(new_len + 1));
    (*box)->rest_info_potential_cmd[x_y.index_x][new_len] = '\0';
    ind_dollar = x_y.index_y;
    x_y.index_y = 0;
    ind_old_word = 0;
    len_val = ft_strlen(tmp_val);
    ind_val = 0;
    keep_len_new_word = new_len;
    printf("new_len = %d\n", new_len);
    while (new_len > 0)
    {
        //1. si antes del dólar hay cositas, copiarlas
        while (ind_new_word < ind_dollar)
        {
            (*box)->rest_info_potential_cmd[x_y.index_x][x_y.index_y] = tmp_old_word_before_free[ind_old_word];
            ind_new_word++;
            ind_old_word++;
            x_y.index_y++;
        }

        //2. una vez llegamos a la posición del dólar
        if (ind_new_word == ind_dollar)
        {
            ind_old_word++; // pasar del dólar
            while (len_str_to_find > 0)
            {
                ind_old_word++; //de la palabra "USER" también vamos a pasar
                len_str_to_find--;
            }
            while (len_val > 0)
            {
                printf("y = %d, ind_val = %d\n", x_y.index_y, ind_val);
                (*box)->rest_info_potential_cmd[x_y.index_x][x_y.index_y] = tmp_val[ind_val];
                ind_val++;
                x_y.index_y++;
                len_val--;
            }
        }

        //3. Si todavía hay más info después de val
        while ((x_y.index_y + 1) < keep_len_new_word)
        {
            (*box)->rest_info_potential_cmd[x_y.index_x][x_y.index_y] = tmp_old_word_before_free[ind_old_word];
            x_y.index_y++;
            ind_old_word++;
        }
        new_len--;
    }
}


void mng_to_replace_env(t_box **box, t_x_y_rest_info x_y, t_prompt **prompt)
{
    int len_val;
    char *tmp_val; //funtzio honetan eukitzeko bakarrik, por readability

    len_val = ft_strlen((ft_getenv_local((*prompt)->vars, get_word_2(box, x_y)))->val);
    tmp_val = malloc(sizeof(char)*(len_val + 1));
    tmp_val[len_val] = '\0';
    cpy_to_val ((ft_getenv_local((*prompt)->vars, get_word_2(box, x_y)))->val, &tmp_val);
    printf("          mngt_to_replace_env | tmp_val copied! = "YELLOW"%s\n"RESET_COLOR, tmp_val);
    replace_env(box, x_y, tmp_val);
}

/*
*   return (0) only used to exit function when next_is_space
*/
int find_dollars_and_replace(t_box **box, t_x_y_rest_info x_y, int **tmp_dict_quotes_word, t_prompt **prompt)
{
    //int len_word; //to debug
    printf(MAGENTA"find_dollars_and_replace, x = %d, y = %d\n"RESET_COLOR, x_y.index_x, x_y.index_y);
    //len_word = ft_strlen((*box)->rest_info_potential_cmd[x_y.index_x]);
    //printf("     find_dollars_and_replace | "MAGENTA"y = %d, len_word = %d\n"RESET_COLOR, x_y.index_y, len_word);
    /*while (len_word > 0)
    {
        //printf("we're checkin here\n");
      */
    if (is_dollar(box, x_y, tmp_dict_quotes_word))
    {
        printf(YELLOW"          dollar was found\n"RESET_COLOR);
        if (next_is_space_or_end(box, x_y))
            return (0); //no need to replace, $ stays
        else //después tiene contenido el dólar
        {
            printf(YELLOW"else\n"RESET_COLOR);
            if (next_is_sec_dollar(box, x_y)) //$$
            {
                printf("               two dollars here! let's get pid! - ");
                mng_to_replace_sec_dollar(box, x_y, tmp_dict_quotes_word);
                //printf(YELLOW"uxu we're here\n"RESET_COLOR);
                //printf("tmp_dict_qotes[%d] = %d\n", 0, (*tmp_dict_quotes_word)[0]);
                //printf("tmp_dict_qotes[%d] = %d\n", 1, (*tmp_dict_quotes_word)[1]);
            }
            else if (is_in_env(box, x_y, prompt)) //sí en env . Coger hassta fin palabra o hasta próximo dólar
            {
                printf("          yes variable exists in env, x = %d, y = %d\n", x_y.index_x, x_y.index_y);
                mng_to_replace_env(box, x_y, prompt);
            }
            else //no en env
            {
                printf(" - no variable is not in env\n");
                mng_to_replace_delete(box, x_y, prompt);
            }
        }
        //}
        //x_y.index_y++;
        //len_word--;
        //printf("status: y = %d, len_word = %d\n", x_y.index_y, len_word);
    }
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
int no_more_dollars(t_box **box, t_x_y_rest_info x_y, int **tmp_dict_quotes_word)
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
            //printf(GREEN"                   yes - STILL MORE DOLLARS, y = %d\n\n"RESET_COLOR, x_y.index_y);
            return (0);
        }
        //i++;
        x_y.index_y++;
        len_word--;
        //printf("BUCLE: i = %d, len_word = %d\n", i, len_word);
    }
   //si llega hasta el final sin encontrar ningún dólar. Si ya ha llegado aquí, si ha salido del bucle, es porque ya hemos recorrido toda la palabra y no se han encontrado dólares válidos
    //printf(RED"                   no - LAST DOLLAR WAS FOUND\n"RESET_COLOR);
    return (1);
}

int *generate_specif_dict_quotes(t_box **box, t_x_y_rest_info x_y, int len)
{
    int *tmp_dict_quotes_word;
    int nb_word_x; //fixed, ze hitz konkretu baten gare, ezta aldatuko

    tmp_dict_quotes_word = malloc(sizeof(int)*len); //no necesito +1 para valor nulo
    //printf("word nb_word_x= %d, tmp_dict_quotes_word - "MAGENTA" len = %d\n"RESET_COLOR, nb_word_x, len_word);
    nb_word_x = x_y.index_x;
    printf("generate_specif_dict_quotes | len = %d, nb_word_x = %d, y = %d\n", len, nb_word_x, x_y.index_y);
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
        printf(BLUE"vuelta n.º %d - "RESET_COLOR, tmp_to_debug);
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
        find_dollars_and_replace(box, x_y, &tmp_dict_quotes_word, prompt); //cada palabra
        //printf(BLUE"uxu we're here\n"RESET_COLOR);
        //printf("tmp_dict_qotes[%d] = %d\n", 0, tmp_dict_quotes_word[0]);
        //printf("tmp_dict_qotes[%d] = %d\n", 1, tmp_dict_quotes_word[1]);
        //printf("tmp_dict_qotes[%d] = %d\n", 2, tmp_dict_quotes_word[2]);
        if (no_more_dollars(box, x_y, &tmp_dict_quotes_word))
        {
            printf(BLUE">>>>>>>>> no more dollars in word\n"RESET_COLOR);
            break;
        }
        if ((x_y.index_y + 1) == len_word) //prevent overflow, safety :)
            break;
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