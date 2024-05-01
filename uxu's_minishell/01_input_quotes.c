/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uxmancis <uxmancis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 10:53:21 by uxmancis          #+#    #+#             */
/*   Updated: 2024/04/28 15:40:40 by uxmancis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int ft_quotes_2(t_prompt **prompt, int i)
{
    printf(YELLOW);
    printf("        ENTRADA comillas simples, input[%d] = %c\n", i, (*prompt)->input[i]);
    printf(RESET_COLOR);
    (*prompt)->dict_quotes[i] = '0'; //comillas principales (simples) están fuera de comillas
    //printf("i++, line 29, input[%d] = %c\n", i, (*prompt)->input[i]);
    i++;
    while ((*prompt)->input[i] != '\0' && (*prompt)->input[i] != '\'')
    {
        printf("             dentro comillas simples, input[%d] = %c\n", i, (*prompt)->input[i]);
        (*prompt)->dict_quotes[i] = '1'; //dentro de comillas simples
        i++;
        printf("             i++, line 44, input[%d] = %c\n", i, (*prompt)->input[i]);
    }
    printf(YELLOW);
    printf("        SALIDA comillas simples, input[%d] = %c\n\n", i, (*prompt)->input[i]);
    printf(RESET_COLOR);
    if (i == (int)ft_strlen((*prompt)->input))
            return (-1); //Error: unclosed quotes
    else
        return (i);
}

int ft_quotes_3(t_prompt **prompt, int i)
{
    printf(MAGENTA);
    printf("        ENTRADA comillas DOBLES, input[%d] = %c\n", i, (*prompt)->input[i]);
    printf(RESET_COLOR);
    (*prompt)->dict_quotes[i] = '0'; //comillas principales (dobles) están fuera de comillas
    i++;
    printf("             i++, line 44, input[%d] = %c\n", i, (*prompt)->input[i]);
    while ((*prompt)->input[i] != '\0' && (*prompt)->input[i] != '\"')
    {
        printf("             dentro comillas DOBLES, input[%d] = %c\n", i, (*prompt)->input[i]);
        (*prompt)->dict_quotes[i] = '2'; //dentro de comillas dobles
        i++;
        printf("             i++, line 44, input[%d] = %c\n", i, (*prompt)->input[i]);
    }
    printf(MAGENTA);
    printf("        SALIDA comillas DOBLES, input[%d] = %c\n\n", i, (*prompt)->input[i]);
    printf(RESET_COLOR);
    if (i == (int)ft_strlen((*prompt)->input))
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
--------------------------------------------------------------*/
int ft_quotes(t_prompt **prompt) //kenduta komentarixuak
{
    int i;
    //int *dictionary; 

    i = 0;
    printf(RED);
    printf(">> entrada en bucle - análisis comillas\n");
    printf(RESET_COLOR);
    while ((*prompt)->input[i] != '\0')
    {
        if ((*prompt)->input[i] == '\'') //una vez entramos en comilla SIMPLE verificamos si están cerradas
        {
            i = ft_quotes_2(prompt, i); //
            if (i == -1)
                return (-1);
        }
        if ((*prompt)->input[i] == '\"')//una vez entramos en comilla DOBLE verificamos si están cerradas
        {
            i = ft_quotes_3(prompt, i);
            if (i == -1)
                return (-1);
        }
        (*prompt)->dict_quotes[i] = '0'; //fuera de comillas
        if (i != (int)ft_strlen((*prompt)->input)) //solo para printear. Sin este if nos imprime un caracter de más, yendo ya más allá de la cadena "input". Eso ya no quiero que me lo imprimas.
            printf("i++, line 49, input[%d] = %c\n", i, (*prompt)->input[i]);
        i++;
    }
    printf(GREEN);
    printf("<< salida de bucle - análisis comillas\n");
    printf(RESET_COLOR);
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

