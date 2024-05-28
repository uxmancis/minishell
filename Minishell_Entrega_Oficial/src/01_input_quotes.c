/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   01_input_quotes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uxmancis <uxmancis@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 10:53:21 by uxmancis          #+#    #+#             */
/*   Updated: 2024/05/19 15:10:40 by uxmancis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../inc/minishell.h"

//int ft_quotes_2(t_prompt **prompt, int i)
int ft_quotes_2(char *input, int **dict_quotes, int i)
{
    //printf(YELLOW"        ENTRADA comillas simples, input[%d] = %c\n"RESET_COLOR, i, input[i]);
    (*dict_quotes)[i] = 0; //comillas principales (simples) están fuera de comillas
    //printf("i++, line 29, input[%d] = %c\n", i, (*prompt)->input[i]);
    i++;
    while (input[i] != '\0' && input[i] != '\'')
    {
        //printf("             dentro comillas simples, input[%d] = %c\n", i, input[i]);
        (*dict_quotes)[i] = 1; //dentro de comillas simples
        i++;
        //printf("             i++, line 44, input[%d] = %c\n", i, input[i]);
    }
    //printf(YELLOW"        SALIDA comillas simples, input[%d] = %c\n\n"RESET_COLOR, i, input[i]);
    if (i == (int)ft_strlen(input))
            return (-1); //Error: unclosed quotes
    else
        return (i);
}

//int ft_quotes_3(t_prompt **prompt, int i)
int ft_quotes_3(char *input, int **dict_quotes, int i)
{
    //printf(MAGENTA"        ENTRADA comillas DOBLES, input[%d] = %c\n"RESET_COLOR, i, input[i]);
    (*dict_quotes)[i] = 0; //comillas principales (dobles) están fuera de comillas
    i++;
    //printf("             i++, line 44, input[%d] = %c\n", i, input[i]);
    while (input[i] != '\0' && input[i] != '\"')
    {
        //printf("             dentro comillas DOBLES, input[%d] = %c\n", i, input[i]);
        (*dict_quotes)[i] = 2; //dentro de comillas dobles
        i++;
        //printf("             i++, line 44, input[%d] = %c\n", i, input[i]);
    }
    //printf(MAGENTA"        SALIDA comillas DOBLES, input[%d] = %c\n\n"RESET_COLOR, i, input[i]);
    if (i == (int)ft_strlen(input))
        return (-1); //Error: unclosed quotes
    else
        return (i);
}

/*ft_quotes iterates through input for the 1st time.
*   Returns:
*       -1: Error: syntax error: unclosed quotes
*       0: Success (assigns value to dictionary on the way)
*
*   Dictionary refers whether if each position on input:
*       0: is out from quotes
*       1: is inside simple quotes ' '
*       2: is inside double quotes " "
*
*   Calls ft_quotes_2 and ft_quotes_3 to make function shorter 
*   (less than 25 line) because of 42 Norminette.
*
*   I want to use ft_quotes for dict_quotes in t_prompt, but also
*   dict_quotes in t_box. 
--------------------------------------------------------------*/
//int ft_quotes(t_prompt **prompt) //kenduta komentarixuak
int ft_quotes(char *input, int **dict_quotes)
{
    int i; 

    i = 0;
    //printf("len_input = %d, input = %s\n", (int)ft_strlen(input), input);
    //(*dict_quotes)[0] = 1;
    //(*dict_quotes)[1] = 1;
    //(*dict_quotes)[2] = 1;
    //printf(RED">> entrada en bucle - análisis comillas\n"RESET_COLOR);
    //(*dict_quotes[0])
    printf(RESET_COLOR);
    while (input[i] != '\0')
    {
        if (input[i] == '\'') //una vez entramos en comilla SIMPLE verificamos si están cerradas
        {
            i = ft_quotes_2(input, dict_quotes, i); //
            if (i == -1)
                return (-1);
        }
        if (input[i] == '\"')//una vez entramos en comilla DOBLE verificamos si están cerradas
        {
            i = ft_quotes_3(input, dict_quotes, i);
            if (i == -1)
                return (-1);
        }
        //printf("pre ++, i = %d\n", i);
        (*dict_quotes)[i] = 0; //fuera de comillas
        if (i != (int)ft_strlen(input)) //solo para printear. Sin este if nos imprime un caracter de más, yendo ya más allá de la cadena "input". Eso ya no quiero que me lo imprimas.
            //printf("i++, line 49, input[%d] = %c\n", i, input[i]);
        i++;
        //printf("post ++, i = %d\n", i);
    }
    //printf(GREEN"<< salida de bucle - análisis comillas\n"RESET_COLOR);
    return (0); //Success, quotes properly closed and dictionary created
}

/*ft_where_r_u
*   Uses dictionary to tell whether if character in input
*   in position [index] is out of quotes or not.
*
*   Returns:
*       0: Out of quotes
*       1: Inside single quotes ('  ')
*       2: Inside double quotes ("  ")
*/
int ft_where_r_u (int index, int *dictionary)
{
       return (dictionary[index]);
}

/*
*   ind_pipes = ft_where_are_pipes returs possibe values
*        -1: pipes in not valid position
*        0: no pipes found
*        >0: number of found pipes
*

*/
/*void init_instructions(char *input, t_prompt *prompt, char *dictionary)
{
    int nb_of_pipes;
    int *index_pipes;

    nb_of_pipes = ft_where_r_pipes(input, &prompt->arr_index_pipes, dictionary);
    
    
        
    //if
    
    printf("number of pipes = %d\n", prompt->are_there_pipes);
}*/

