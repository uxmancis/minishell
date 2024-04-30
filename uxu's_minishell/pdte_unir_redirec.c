/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pdte_unir_redirec.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uxmancis <uxmancis@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 20:50:04 by uxmancis          #+#    #+#             */
/*   Updated: 2024/04/29 20:50:04 by uxmancis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*Vamos a analizar las redirecciones que podamos encontrar en 1 caja*/

#include <stdio.h>
#include <stdlib.h> //EXIT_FAILURE
#include <unistd.h>

# define DEF_COLOR "\033[0;39m"
# define GRAY "\033[0;90m"
# define RED "\033[0;31m"
# define GREEN "\033[0;92m"
# define YELLOW "\033[0;93m"
# define BLUE "\033[0;94m"
# define MAGENTA "\033[0;95m"
# define CYAN "\033[0;96m"
# define WHITE "\033[0;97m"
# define RESET_COLOR   "\033[0m"
# define SALMON "\033[0;31m"
#define AQUAMARINE "\033[0;96m"

/* DESCRIPTION:
Outputs the char c to the file descriptor fd.
The function returns the number of characters printed and -1 if fails to print.
---------------------------------------------------------------------------- */
int	ft_putchar_fd(int c, int fd)
{
	write(fd, &c, 1);
	return (1);
}

/* DESCRIPTION:
Outputs the string s to the file descriptor fd.
The function returns the number of characters printed and -1 if fails to print.
---------------------------------------------------------------------------- */
int	ft_putstr_fd(char *str, int fd)
{
	int	count;

	count = 0;
	if (!str)
		return (write(fd, "(null)", 6));
	while (*str)
	{
		count += ft_putchar_fd(*str, fd);
		str++;
	}
	return (count);
}

void ft_puterror_exit(char *str)
{
	ft_putstr_fd("\033[31mError: ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd("\033[0;39m", 2);
	exit(EXIT_FAILURE);
}

size_t	ft_strlen(char *str)
{
	size_t	i;

	i = 0;
	while (str[i] != '\0')
	{
		i++;
	}
	return (i);
}

typedef enum e_red_type
{
    NO_REDIRECTION, //0
    OUTFILE_APPEND, //1: >>
    OUTFILE_STRONG, //2: >
    INFILE, //3: <
    HEREDOC //4: <<
}   t_red_type;

typedef struct s_box
{
    char    *input_substr;
    int     id_substr;
    int   **total_red_type_index; //[0]: index, [1]: type
}   t_box;                        //[0]: index, [1]: type

/*int ft_redir_1(t_box *box, char *input_substr)
{
    int i;
    int store_in;

    i = 0;
    store_in = 0;
    while (input_substr[i] != '0')
    {
        if (input_substr[i] == '>')
        {
            if (input_substr[i + 1] == '>')
            {
                if (input_substr[i + 2] == '>' || input_substr[i + 2] == '<')
                    ft_puterror_exit("syntax error: unexpected token\n");
                box->red_type_index[i] = "OUTFILE_APPEND"; //>>
                i++;
            }
            else if (input_substr[i + 1] == '<')
                ft_puterror_exit("syntax error: unexpected token\n");
            else
                box->red_type_index[i] = "OUTFILE_STRONG"; //>
        }
        i++;
    }
}

int ft_redir_2(t_box *box, char *input_substr)
{
    int i; 

    i = 0;
    while (input_substr[i] != '0')
    {
        while (input_substr[i] != '<' && input_substr[i] != '>')
            i++;
        if (input_substr[i] == '<')
        {
            if (input_substr[i + 1] == '<')
            {
                if (input_substr[i + 2] == '<' || input_substr[i + 2] == '>')
                    ft_puterror_exit("syntax error: unexpected token\n");
                box->red_type_index[i] = "HEREDOC";
                i++;
            }
            else
                box->red_type_index[i] = "INFILE";
        }
        i++;
    }
}*/

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

    i = 0;
    counter = 0;
    while (box->input_substr[i] != '\0')
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
                }
            }
            else
            {
                counter++;
                i++;
            }
        }
        i++;
    }
    //printf("nb_of_redirections = %d\n", counter);
    return (counter);
}


//pdte. contar únicamente si está fuera de comillas. Utilizar dict_quotes (t_prompt): Agregado YES it works
/*void set_red_type_index(t_box **box)
{
    int i;
    int index_of_arr;
    int len;

    i = 0;
    index_of_arr = 0;
    //printf("i = %d\n", i);
    len = (int)ft_strlen((*box)->input_substr);
    //printf("len = %d\n", (int)ft_strlen((*box)->input_substr));
    while (/*(*box)->input_substr[i] != '\0'len > 0)
    {
        if ((*box)->input_substr[i] == '<' || (*box)->input_substr[i] == '>' ) //1.a topatuta
        {
            if ((*box)->input_substr[i + 1] == '<' || (*box)->input_substr[i + 1] == '>')
            {
                if ((*box)->input_substr[i + 2] == '<' || (*box)->input_substr[i + 2] == '>')
                    ft_puterror_exit("syntax error near unexpected token `newline'\n");
                else //2.a topatuta
                {
                    (*box)->total_red_type_index[index_of_arr][0] = i; //ASSIGN RED_INDEX
                    if ((*box)->input_substr[i] == '<')
                        (*box)->total_red_type_index[index_of_arr][1] = HEREDOC; //ASSIGN RED_TYPE
                    else
                        (*box)->total_red_type_index[index_of_arr][1] = OUTFILE_APPEND; //ASSIGN RED_TYPE
                    //printf("DOUBLE red. assigned, i = %d, go to next\n", i);
                    index_of_arr++;
                    i = i + 2; //juateko ya hurrengora
                    len = len - 2;
                }
            }
            else //1 bakarrik dauka
            {
                (*box)->total_red_type_index[index_of_arr][0] = i; //ASIGNAR ÍNDICE REDIR. redir index in input_substr
                if ((*box)->input_substr[i] == '<')
                        (*box)->total_red_type_index[index_of_arr][1] = INFILE; //ASIGNAR TIPO REDIR redir type
                else
                    (*box)->total_red_type_index[index_of_arr][1] = OUTFILE_STRONG; //redir type
                //printf("SINGLE red. assigned, i = %d, go to next\n", i);
                index_of_arr++;
                i++; //juateko hurrengora
                len--;
            }
        }
        len--;
        i++;
        //printf("(line 216) i++, i = %d\n", i);
    }
    printf("\nRESULTADO:\n");
    printf("red. 1 | total_red_index_type | [0] INDEX_red_in_substr = %d | [1]_red_type: %s\n", (*box)->total_red_type_index[0][0], ft_enum_to_str((*box)->total_red_type_index[0][1]));
    printf("red. 2 | total_red_index_type | [0] INDEX_red_in_substr = %d | [1]_red_type: %s\n", (*box)->total_red_type_index[1][0], ft_enum_to_str((*box)->total_red_type_index[1][1]));
    printf("red. 3 | total_red_index_type | [0] INDEX_red_in_substr = %d | [1]_red_type: %s\n", (*box)->total_red_type_index[2][0], ft_enum_to_str((*box)->total_red_type_index[2][1]));
    printf("red. 4 | total_red_index_type | [0] INDEX_red_in_substr = %d | [1]_red_type: %s\n", (*box)->total_red_type_index[3][0], ft_enum_to_str((*box)->total_red_type_index[3][1]));
    printf("red. 5 | total_red_index_type | [0] INDEX_red_in_substr = %d | [1]_red_type: %s\n", (*box)->total_red_type_index[4][0], ft_enum_to_str((*box)->total_red_type_index[4][1]));
    printf("red. 6 | total_red_index_type | [0] INDEX_red_in_substr = %d | [1]_red_type: %s\n", (*box)->total_red_type_index[5][0], ft_enum_to_str((*box)->total_red_type_index[5][1]));
    printf("red. 7 | total_red_index_type | [0] INDEX_red_in_substr = %d | [1]_red_type: %s\n", (*box)->total_red_type_index[6][0], ft_enum_to_str((*box)->total_red_type_index[6][1]));
    //printf("str2 = %s\n", (*box)->total_red_type_index[1]);
    //printf("str3 = %s\n", (*box)->total_red_type_index[2])
}*/


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
    len = (int)ft_strlen((*box)->input_substr);
    //printf("set_red_type_index, len = %d\n");
    while (len > 0)
    {
        if ((*box)->input_substr[i] == '<')
        {
            //printf(AQUAMARINE"< identified! - Send to LESS THAN, i = "YELLOW"%d"AQUAMARINE" - input_substr[%d] = %c\n"RESET_COLOR, i, i, (*box)->input_substr[i]);
            set_red_less_than(box, &i, index_of_arr); //< and << are assigned. Includes error management. We send &i in case it must be updated (+2, when double redirection is found)
            printf(GREEN"redirection %d assigned: [0]_INDEX: %d, [1]_TYPE: %s\n"RESET_COLOR, (index_of_arr + 1), (*box)->total_red_type_index[index_of_arr][0], ft_enum_to_str((*box)->total_red_type_index[index_of_arr][1]));  
        }
        else if ((*box)->input_substr[i] == '>')
        {
            //printf(AQUAMARINE"> identified! - Send to GREATER THAN, i = "YELLOW"%d"AQUAMARINE" - input_substr[%d] = %c\n"RESET_COLOR, i, i, (*box)->input_substr[i]);
            set_red_greater_than(box, &i, index_of_arr);//> and >> are assigned. Includes error management. We send &i in case it must be updated (+2, when double redirection is found)
            printf(GREEN"redirection %d assigned: [0]_INDEX: %d, [1]_TYPE: %s\n"RESET_COLOR, (index_of_arr + 1), (*box)->total_red_type_index[index_of_arr][0], ft_enum_to_str((*box)->total_red_type_index[index_of_arr][1]));          
        }
        //else if ((*box)->input_substr[i] == '>')
        //HAU INPRIMAU HORIXA IKUSTEKO!
        //printf(YELLOW"before, ++, i = %d, input_substr[%d] = %c\n"RESET_COLOR, i, i, (*box)->input_substr[i]); //wtf cómo que printf hau gabe eztabela ondo funzionatzen?? jaja 
        i++; //es como que necesita el printf de arriba para que sí funcione este i++, wtf
        //printf(BLUE"before, i = %d\n"RESET_COLOR, i); hau barek bai, de este parece que sí se puede prescindir jaja wtf
        index_of_arr;
        len--;
        //printf("vuelta completed, i = %d\n", i);
    }
}

void ft_fill_red_info(t_box **box, int nb_of_red)
{
    int i; 

    i = 0;
    //printf("ft_fill_red_info\n");
    while (nb_of_red > 0)
    {
        (*box)->total_red_type_index[i] = malloc(sizeof(int)*2);
        nb_of_red--;
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
int ft_is_redir(t_box *box)
{
    int i;
    int index_total_redir;
    int nb_of_red; //to malloc total_redir...

    nb_of_red = ft_get_numof_redir(box);
    printf(AQUAMARINE"nb_of_red = %d\n"RESET_COLOR, nb_of_red);
    if (nb_of_red == 0)
        return (0);
    box->total_red_type_index = malloc(sizeof(char*)*nb_of_red); //1 array para cada redirección. En cada array, [0] = tipo de redir, [1] índice en el que se encuentra en el input_substr
    ft_fill_red_info(&box, nb_of_red); //se informa total_red_type_index
    return (1);
}

int main(void)
{
    t_box box;

    box.input_substr = "< >> >> << < < > holi";
    //printf("str = %s\n", box.input_substr);
    if (!ft_is_redir(&box)) //al llamar, si hay redirecciones, ya se rellena el array de redirecciones (total_red_type_index). Si no, imprimimos resultado.
        printf("No redirections found\n");
    return (0);
}