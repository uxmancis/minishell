/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   02_boxes_redir.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uxmancis <uxmancis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 20:14:39 by uxmancis          #+#    #+#             */
/*   Updated: 2024/05/01 11:27:05 by uxmancis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

    i = 0;
    counter = 0;
    printf(RED"input_substr = %s\n"RESET_COLOR, box->input_substr);
    len = (int)ft_strlen(box->input_substr); //ns porq tengo que hacer -1 para que cuadre
    printf("len = %d\n", len);
    while (box->input_substr[i] != '\0'/*len > 0*/)
    {
        if (box->input_substr[i] == '<' || box->input_substr[i] == '>' ) //1.a topatuta
        {
            if (box->input_substr[i + 1] == '<' || box->input_substr[i + 1] == '>')
            {
                if (box->input_substr[i + 2] == '<' || box->input_substr[i + 2] == '>')
                    ft_puterror_exit("syntax error near unexpected token `newline'\n");
                else //2.a topatuta
                {
                    counter++;
                    i = i + 2; //juateko ya hurrengora
                    printf(YELLOW"i = %d\n"RESET_COLOR, i);
                }
            }
            else
            {
                counter++;
                i++;
                printf(MAGENTA"i = %d\n"RESET_COLOR, i);
            }
        }
        else
            i++;
        len--;
        printf("i = %d, len = %d\n", i, len);
    }
    //printf("nb_of_redirections = %d\n", counter);
    return (counter);
}

int set_red_less_than(t_box **box, int *i, int index_of_arr)
{
    //printf("< found, i = %d\n", (*i));
    //make sure it is correct that we enter here
    //printf(YELLOW"<     i = %d\n", (*i));
    if ((*box)->input_substr[(*i)] != '<')
        return(EXIT_FAILURE); //was not supposed to be here
    else if ((*box)->input_substr[(*i)] == '<')
    {
        if ((*box)->input_substr[(*i) + 1] == '<')
        {
            if ((*box)->input_substr[(*i)+2] == '<' || (*box)->input_substr[(*i)+2] == '>')//3rd position any kind of redirection = error
                ft_puterror_exit("syntax error near unexpected token `newline'\n");
            //Redirection assignment (HEREDOC)
            (*box)->total_red_type_index[index_of_arr][0] = (*i); //INDEX of heredoc
            (*box)->total_red_type_index[index_of_arr][1] = HEREDOC; //TYPE of Redirection
            (*i) = (*i) + 1; //when double redirection is assigned
            //printf(AQUAMARINE"before i = %d, after i = %d\n"RESET_COLOR, (*i), (*i));
        }
        else if ((*box)->input_substr[(*i) + 1] == '>') //si en 2ª posición está el contrario: error
            ft_puterror_exit("syntax error near unexpected token `newline'\n");
        else 
        {
            //Redirection assignment (HEREDOC)
            (*box)->total_red_type_index[index_of_arr][0] = (*i); //INDEX of heredoc
            (*box)->total_red_type_index[index_of_arr][1] = INFILE; //TYPE of Redirection
            //printf(AQUAMARINE"before ++i = %d\n"RESET_COLOR,(*i));
        }
    }
    return (0);
}

int set_red_greater_than(t_box **box, int *i, int index_of_arr)
{
    //make sure it is correct that we enter here
    //printf("> found\n");
    //printf(MAGENTA">     i = %d\n", (*i));
    if ((*box)->input_substr[(*i)] != '>')
        return(EXIT_FAILURE); //was not supposed to be here
    else if ((*box)->input_substr[(*i)] == '>')
    {
        if ((*box)->input_substr[(*i) + 1] == '>')
        {
            if ((*box)->input_substr[(*i)+2] == '<' || (*box)->input_substr[(*i)+2] == '>') //3rd position any kind of redirection = error
                ft_puterror_exit("syntax error near unexpected token `newline'\n");
            //Redirection assignment (OUTFILE_APPEND)
            (*box)->total_red_type_index[index_of_arr][0] = (*i); //INDEX of heredoc
            (*box)->total_red_type_index[index_of_arr][1] = OUTFILE_APPEND; //TYPE of Redirection
            //printf(AQUAMARINE"before ++i = %d\n", (*i));
            (*i) = (*i) + 1; //when double redirection is assigned
            //printf(AQUAMARINE"after ++i = %d\n", (*i));
        }
        else if ((*box)->input_substr[(*i) + 1] == '<') //si en 2ª posición está el contrario: error
            ft_puterror_exit("syntax error near unexpected token `newline'\n");
        else 
        {
            printf("index_or_arr = %d, i = %d\n", index_of_arr, (*i));
            //Redirection assignment (HEREDOC)
            (*box)->total_red_type_index[index_of_arr][0] = (*i); //INDEX of heredoc
            (*box)->total_red_type_index[index_of_arr][1] = OUTFILE_STRONG; //TYPE of Redirection
        }
    }
    return (0);
}

void set_red_type_index(t_box **box)
{
    int i;
    int index_of_arr;
    int len;

    i = 0;
    index_of_arr = 0;
    //printf(AQUAMARINE"set_red_type_index\n"RESET_COLOR);
    len = (int)ft_strlen((*box)->input_substr);
    printf(AQUAMARINE"set_red_type_index, len = %d\n"RESET_COLOR, len);
    while (i < len)
    {
        //printf(AQUAMARINE"hasi! i = %d\n"RESET_COLOR, i);
        if ((*box)->input_substr[i] == '<')
        {
            //printf(AQUAMARINE"< identified! - Send to LESS THAN, i = "YELLOW"%d"AQUAMARINE" - input_substr[%d] = %c\n"RESET_COLOR, i, i, (*box)->input_substr[i]);
            set_red_less_than(box, &i, index_of_arr); //< and << are assigned. Includes error management. We send &i in case it must be updated (+2, when double redirection is found)
            printf(GREEN"redirection %d assigned: [0]_INDEX: %d, [1]_TYPE: %s\n"RESET_COLOR, (index_of_arr + 1), (*box)->total_red_type_index[index_of_arr][0], ft_enum_to_str((*box)->total_red_type_index[index_of_arr][1]));  
            index_of_arr++;        
        }
        else if ((*box)->input_substr[i] == '>')
        {
            //printf(AQUAMARINE"> identified! - Send to GREATER THAN, i = "YELLOW"%d"AQUAMARINE" - input_substr[%d] = %c\n"RESET_COLOR, i, i, (*box)->input_substr[i]);
            set_red_greater_than(box, &i, index_of_arr);//> and >> are assigned. Includes error management. We send &i in case it must be updated (+2, when double redirection is found)
            printf(GREEN"redirection %d assigned: [0]_INDEX: %d, [1]_TYPE: %s\n"RESET_COLOR, (index_of_arr + 1), (*box)->total_red_type_index[index_of_arr][0], ft_enum_to_str((*box)->total_red_type_index[index_of_arr][1]));          
            index_of_arr++;
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
    printf(AQUAMARINE"ft_fill_red_info\n"RESET_COLOR);
    while (tmp_nb_of_red > 0)
    {
        (*box)->total_red_type_index[i] = malloc(sizeof(int)*2);
        tmp_nb_of_red--;
        i++;
    }
    set_red_type_index(box);
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
    printf(AQUAMARINE"nb_of_red = %d\n"RESET_COLOR, box->nb_of_redir);
    if (box->nb_of_redir == 0)
        return (0);
    box->total_red_type_index = malloc(sizeof(char*)*(box->nb_of_redir)); //1 array para cada redirección. En cada array, [0] = tipo de redir, [1] índice en el que se encuentra en el input_substr
    ft_fill_red_info(&box); //se informa total_red_type_index
    return (1);
}