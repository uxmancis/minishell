/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   02_boxes_2_redir.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uxmancis <uxmancis@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2024/05/19 15:10:51 by uxmancis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../inc/minishell.h"


//useful to debug: to print enum name
char *ft_enum_to_str(int enumerator)
{
    if (enumerator == NO_REDIRECTION)
        return ("NO_REDIRECTION");
    else if (enumerator == OUTFILE_APPEND)
        return (">>: OUTFILE_APPEND");
    else if (enumerator == OUTFILE_STRONG)
        return (">: OUTFILE_STRONG");
    else if (enumerator == INFILE)
        return ("<: INFILE");
    else if (enumerator == HEREDOC)
        return ("<<: HEREDOC");
    else
        return ("ERROR\n");
}

//int ft_check_if_redir redir(t_box *box, char *input)
int ft_get_numof_redir(t_box *box)
{
    int i;
    int counter;
    int len;
    int keep_len;

    i = 0;
    counter = 0;
    printf(RED"               input_substr = %s, len = %d\n"RESET_COLOR, box->input_substr, (int)ft_strlen(box->input_substr));
    len = (int)ft_strlen(box->input_substr); //ns porq tengo que hacer -1 para que cuadre. Ya ez :)
    keep_len = len;
    //printf("len = %d\n", len);
    while (i < keep_len/*box->input_substr[i] != '\0'*//*len > 0*/)
    {
        if (i < keep_len && (box->input_substr[i] == '<' || box->input_substr[i] == '>' )) //1.a topatuta
        {
            //printf("i = %d, len = %d\n", i, len);
            if (/*i < (keep_len - 1) && */(box->input_substr[i + 1] == '<' || box->input_substr[i + 1] == '>'))
            {
                if (box->input_substr[i + 2] == '<' || box->input_substr[i + 2] == '>')
                    ft_puterror_exit("syntax error near unexpected token `newline'\n");
                else //2.a topatuta
                {
                    if (box->dict_quotes[i] == 0) //asegurar que está fuera de comillas
                    {
                        counter++;
                        i = i + 2; //juateko ya hurrengora
                        //printf(YELLOW"i = %d\n"RESET_COLOR, i);
                    }
                }
            }
            else
            {
                if (box->dict_quotes[i] == 0)
                {
                    counter++;
                    i++;
                    //printf(MAGENTA"i = %d\n"RESET_COLOR, i);
                }
            }
        }
        i++;
        len--;
        //printf("i = %d, len = %d\n", i, len);
    }
    //printf("nb_of_redirections = %d\n", counter);
    //printf(BLUE"               nb_of_red = %d\n"RESET_COLOR, box->nb_of_redir);
    printf("     02_boxes_redir.c - ft_get_numof_redir| Counted!✅"BLUE" nb_of_red = %d\n"RESET_COLOR, counter);
    return (counter);
}

/*  set_red_less_than
*       Returns:
*           0: Success - Redirection was assigned
*           -1: Redirection was finally NOT assigned (inside quotes)
*/
int set_red_less_than(t_box **box, int *i, int index_of_arr)
{
    //printf("< found, i = %d\n", (*i));
    //make sure it is correct that we enter here
    //printf(YELLOW"<     i = %d\n", (*i));
    if ((*box)->input_substr[(*i)] != '<' && (*box)->dict_quotes[(*i)] == 0)
        return(EXIT_FAILURE); //was not supposed to be here
    else if ((*box)->input_substr[(*i)] == '<' && (*box)->dict_quotes[(*i)] == 0)
    {
        if ((*box)->input_substr[(*i) + 1] == '<' && (*box)->dict_quotes[(*i) + 1] == 0)
        {
            if (((*box)->input_substr[(*i)+2] == '<' && (*box)->dict_quotes[(*i) + 2] == 0) || ((*box)->input_substr[(*i)+2] == '>' && (*box)->dict_quotes[(*i) + 2] == 0))//3rd position any kind of redirection = error
                ft_puterror_exit("syntax error near unexpected token `newline'\n");

            //printf(">> i = %d, dict_quotes[%d] = %d\n", (*i), (*i), (*box)->dict_quotes[(*i)]);
            //Redirection assignment (HEREDOC)
            if ((*box)->dict_quotes[(*i)] == 0) //si está fuera de comillas
            {
                //printf("entró, i = %d\n", (*i));
                (*box)->dict_red_index_type[index_of_arr][0] = (*i); //INDEX of heredoc
                (*box)->dict_red_index_type[index_of_arr][1] = HEREDOC; //TYPE of Redirection
                (*i) = (*i) + 1; //when double redirection is assigned
            //printf(AQUAMARINE"before i = %d, after i = %d\n"RESET_COLOR, (*i), (*i));
            }
            else
                return (-1);  
        }
        else if ((*box)->input_substr[(*i) + 1] == '>' && (*box)->dict_quotes[(*i) + 1] == 0) //si en 2ª posición está el contrario: error
            ft_puterror_exit("syntax error near unexpected token `newline'\n");
        else 
        {
            //printf(">> i = %d, dict_quotes[%d] = %d\n", (*i), (*i), (*box)->dict_quotes[(*i)]);
            //Redirection assignment (HEREDOC)
            if ((*box)->dict_quotes[(*i)] == 0) //si está fuera de comillas
            {
                //printf("no debería habr entrado\n"); //probando casuística particular
                (*box)->dict_red_index_type[index_of_arr][0] = (*i); //INDEX of heredoc
                (*box)->dict_red_index_type[index_of_arr][1] = INFILE; //TYPE of Redirection
                //printf(AQUAMARINE"before ++i = %d\n"RESET_COLOR,(*i));
            }
            else
                return (-1);
        }
    }
    return (0);
}

/*  set_red_greater_than
*       Returns:
*           0: Success - Redirection was assigned
*           -1: Redirection was finally NOT assigned (inside quotes)
*/
int set_red_greater_than(t_box **box, int *i, int index_of_arr)
{
    //make sure it is correct that we enter here
    //printf("> found\n");
    //printf(MAGENTA">     i = %d\n", (*i));
    if ((*box)->input_substr[(*i)] != '>' && (*box)->dict_quotes[(*i)] == 0)
        return(EXIT_FAILURE); //was not supposed to be here
    else if ((*box)->input_substr[(*i)] == '>' && (*box)->dict_quotes[(*i)] == 0)
    {
        if ((*box)->input_substr[(*i) + 1] == '>' && (*box)->dict_quotes[(*i) + 1] == 0)
        {
            if (((*box)->input_substr[(*i)+2] == '<' && (*box)->dict_quotes[(*i) + 2] == 0) || ((*box)->input_substr[(*i)+2] == '>' && (*box)->dict_quotes[(*i) + 2] == 0)) //3rd position any kind of redirection = error
                ft_puterror_exit("syntax error near unexpected token `newline'\n");
            
            if ((*box)->dict_quotes[(*i)] == 0 )//si está fuera de comillas
            {
                //printf("line 140 | i = %d\n", (*i));
                //Redirection assignment (OUTFILE_APPEND)
                (*box)->dict_red_index_type[index_of_arr][0] = (*i); //INDEX of heredoc
                (*box)->dict_red_index_type[index_of_arr][1] = OUTFILE_APPEND; //TYPE of Redirection
                //printf(AQUAMARINE"before ++i = %d\n", (*i));
                (*i) = (*i) + 1; //when double redirection is assigned
                //printf(AQUAMARINE"after ++i = %d\n", (*i));
            }
            else
                return (-1);
        }
        else if ((*box)->input_substr[(*i) + 1] == '<' && (*box)->dict_quotes[(*i) + 1] == 0) //si en 2ª posición está el contrario: error
            ft_puterror_exit("syntax error near unexpected token `newline'\n");
        else 
        {
            if ((*box)->dict_quotes[(*i)] == 0)//si está fuera de comillas
            {
                //printf("index_or_arr = %d, i = %d\n", index_of_arr, (*i));
                //printf("line 156 | i = %d\n", (*i));
                //Redirection assignment (HEREDOC)
                (*box)->dict_red_index_type[index_of_arr][0] = (*i); //INDEX of heredoc
                (*box)->dict_red_index_type[index_of_arr][1] = OUTFILE_STRONG; //TYPE of Redirection
            }
            else
                return (-1);
        }
    }
    return (0);
}

void set_red_index_type(t_box **box)
{
    int i;
    int index_of_arr;
    int len;

    i = 0;
    index_of_arr = 0;
    //printf(AQUAMARINE"set_red_type_index\n"RESET_COLOR);
    len = (int)ft_strlen((*box)->input_substr);
    printf("     02_boxes_redir.c - "BLUE"set_red_index_type"RESET_COLOR"| Info about redirecciones is stored here:\n");
    while (i < len)
    {
        //printf(AQUAMARINE"hasi! i = %d\n"RESET_COLOR, i);
        if ((*box)->input_substr[i] == '<' && (*box)->dict_quotes[i] == 0)
        {
            //printf(AQUAMARINE"< identified! - Send to LESS THAN, i = "YELLOW"%d"AQUAMARINE" - input_substr[%d] = %c\n"RESET_COLOR, i, i, (*box)->input_substr[i]);
            //printf("less than\n");
            if (set_red_less_than(box, &i, index_of_arr) == 0) //< and << are assigned. Includes error management. We send &i in case it must be updated (+2, when double redirection is found)
            {
                printf(GREEN"               redirection %d assigned:     [0]_INDEX: %d  [1]_TYPE: %s\n"RESET_COLOR, (index_of_arr + 1), (*box)->dict_red_index_type[index_of_arr][0], ft_enum_to_str((*box)->dict_red_index_type[index_of_arr][1]));
                index_of_arr++;
            }      
                    
        }
        else if ((*box)->input_substr[i] == '>' && (*box)->dict_quotes[i] == 0)
        {
            //printf(AQUAMARINE"> identified! - Send to GREATER THAN, i = "YELLOW"%d"AQUAMARINE" - input_substr[%d] = %c\n"RESET_COLOR, i, i, (*box)->input_substr[i]);
            //printf("greater than\n");
            if (set_red_greater_than(box, &i, index_of_arr) == 0)//> and >> are assigned. Includes error management. We send &i in case it must be updated (+2, when double redirection is found)
            {    printf(GREEN"               redirection %d assigned:     [0]_INDEX: %d  [1]_TYPE: %s\n"RESET_COLOR, (index_of_arr + 1), (*box)->dict_red_index_type[index_of_arr][0], ft_enum_to_str((*box)->dict_red_index_type[index_of_arr][1]));          
                 index_of_arr++;
            }
        }
        //else if ((*box)->input_substr[i] == '>')
        //HAU INPRIMAU HORIXA IKUSTEKO!
        //printf(YELLOW"before, ++, i = %d, input_substr[%d] = %c\n"RESET_COLOR, i, i, (*box)->input_substr[i]); //wtf cómo que printf hau gabe eztabela ondo funzionatzen?? jaja 
        i++; //es como que necesita el printf de arriba para que sí funcione este i++, wtf
        //printf(BLUE"before, i = %d\n"RESET_COLOR, i); hau barek bai, de este parece que sí se puede prescindir jaja wtf
        //len--;
        //printf("vuelta completed, i = %d, len = %d, input_substr[%d] = %c\n", i, len, i, (*box)->input_substr[i]);
    }
}

void ft_fill_red_info(t_box **box)
{
    int i;
    int tmp_nb_of_red;

    i = 0;
    tmp_nb_of_red = (*box)->nb_of_redir;
    while (tmp_nb_of_red > 0)
    {
        (*box)->dict_red_index_type[i] = malloc(sizeof(int)*2);
        tmp_nb_of_red--;
        i++;
    }
    set_red_index_type(box);
    printf("     02_boxes.c - ft_fill_red_info|"BLUE" dict_red_index_type"RESET_COLOR" generated✅\n");
}

/*ft_is_redir
*
*   Checks whether if there are any redirections along our 
*   input_substr to be analysed.
*
*   Returns:
*       0: No redirections found along input_substr
*       1: Yes, some redirections were found
*
*   Also, if YES (1) redirections were found, ft_fill_red_info function
*   is called. In it,  information of found redirections is stored in 
*   total_red_type_index variable member (t_box) in the following way:
*       [0]: Redirection type
*       [1]: Redirection index in input_substr
*/
int get_redirections(t_box *box)
{
    //int nb_of_red; //to malloc total_redir...

    box->nb_of_redir = ft_get_numof_redir(box);
    //printf(BLUE"               nb_of_red = %d\n"RESET_COLOR, box->nb_of_redir);
    if (box->nb_of_redir == 0)
        return (0); 
    box->dict_red_index_type = malloc(sizeof(char*)*(box->nb_of_redir)); //1 array para cada redirección. En cada array, [0] = tipo de redir, [1] índice en el que se encuentra en el input_substr
    ft_fill_red_info(&box); //se informa total_red_type_index
    return (1);
}