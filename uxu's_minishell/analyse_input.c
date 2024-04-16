/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analyse_input.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uxmancis <uxmancis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 10:53:21 by uxmancis          #+#    #+#             */
/*   Updated: 2024/04/16 20:43:15 by uxmancis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int ft_quotes_2(char *input, char **dictionary, int i)
{
    printf(YELLOW);
    printf("        ENTRADA comillas simples, input[%d] = %c\n", i, input[i]);
    printf(RESET_COLOR);
    (*dictionary)[i] = '0'; //comillas principales (simples) están fuera de comillas
    i++;
    printf("i++, line 29, input[%d] = %c\n", i, input[i]);
    while (input[i] != '\0' && input[i] != '\'')
    {
        printf("             dentro comillas simples, input[%d] = %c\n", i, input[i]);
        (*dictionary)[i] = '1'; //dentro de comillas simples
        i++;
        printf("             i++, line 44, input[%d] = %c\n", i, input[i]);
    }
    printf(YELLOW);
    printf("        SALIDA comillas simples, input[%d] = %c\n\n", i, input[i]);
    printf(RESET_COLOR);
    if (i == (int)ft_strlen(input))
            return (-1); //Error: unclosed quotes
    else
        return (i);
}

int ft_quotes_3(char *input, char **dictionary, int i)
{
    printf(MAGENTA);
    printf("        ENTRADA comillas DOBLES, input[%d] = %c\n", i, input[i]);
    printf(RESET_COLOR);
    (*dictionary)[i] = '0'; //comillas principales (dobles) están fuera de comillas
    i++;
    printf("             i++, line 44, input[%d] = %c\n", i, input[i]);
    while (input[i] != '\0' && input[i] != '\"')
    {
        printf("             dentro comillas DOBLES, input[%d] = %c\n", i, input[i]);
        (*dictionary)[i] = '2'; //dentro de comillas dobles
        i++;
        printf("             i++, line 44, input[%d] = %c\n", i, input[i]);
    }
    printf(MAGENTA);
    printf("        SALIDA comillas DOBLES, input[%d] = %c\n\n", i, input[i]);
    printf(RESET_COLOR);
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
--------------------------------------------------------------*/
int ft_quotes(char *input, char **dictionary) //kenduta komentarixuak
{
    int i;
    //int *dictionary; 

    i = 0;
    printf(RED);
    printf(">> entrada en bucle - análisis comillas\n");
    printf(RESET_COLOR);
    while (input[i] != '\0')
    {
        if (input[i] == '\'')
        {
            i = ft_quotes_2(input, dictionary, i);
            if (i == -1)
                return (-1);
        }
        if (input[i] == '\"')
        {
            i = ft_quotes_3(input, dictionary, i);
            if (i == -1)
                return (-1);
        }
        (*dictionary)[i] = '0'; //fuera de comillas
        i++;
        if (i != (int)ft_strlen(input)) //solo para printear. Sin este if nos imprime un caracter de más, yendo ya más allá de la cadena "input". Eso ya no quiero que me lo imprimas.
            printf("i++, line 49, input[%d] = %c\n", i, input[i]);
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

/*ft_is_there_pipe
*
*   Analyses input in order to check whether if pipes are found or not
*   along input.  
*
*    Returns:
*       -2: Error: pipe found in incorrect position [0] or last position
*       -1: No pipes found
*       >0: position of pipe (0 not possible. As, pipe in [0] returns -2)
*/
int ft_is_there_pipe(char *input)
{
    int i;
    int counter; 

    i = 0;
    counter = 0;
    while (input[i] != '\0')
    {
        if (input[i] == '|')
        {
            if (i == 0 ||i == ((int)ft_strlen(input) - 1)) //first or last position
                return (-2);
            counter++;
        }
        i++;
    }
    if (counter == 0)
        return (-1); //no pipes found
    return (counter); //returns number of found pipes
}

void init_instructions(char *input, t_prompt *prompt)
{
    prompt->are_there_pipes = ft_is_there_pipe(input);
    printf("number of pipes = %d\n", prompt->are_there_pipes);
}

void ft_analyse_input(char *input, t_prompt *prompt)
{
    //char *clean_input; //no espacios innecesarios --> esto al imprimir sí es importante, saber si está dentro o fuera de comillas para saber si imprimir o no los espacios
    //declarar estructura que va a devolver: con todas las instrucciones
    char *dictionary;
    
    //conclusiones análisis: ¿qué conclusiones quiero?
    //1. número de comandos a ejecutar = número de procesos hijo a crear
    //if (ft_quotes(input) == -1) //1.1) Asegurar que todas las comillas principales están cerradas
        //ft_puterror_exit("syntax error: unclosed quotes");
    dictionary = malloc(sizeof(int) * (ft_strlen(input) + 1));
    dictionary[ft_strlen(input)] = '\0'; //es para indicar final de array. Al ser int *, no nos deja '\0' para finalizar array. El 9 es el final. ¿Podríamos hacerlo char *? Sí, pero los indicadres son 0, 1, 2, integers. Podríamos hacerlo '0', '1' y '2', pero no quiero.
    if (ft_quotes (input, &dictionary)== -1)
        ft_puterror("syntax error: unclosed quotes\n");
    init_instructions(input, prompt);
    //test dictionary
    int i;
    i = 0;
    printf(BLUE);
    printf("test dictionary, len = %d\n", (int)ft_strlen(dictionary));
    printf(RESET_COLOR);
    while (dictionary[i] != '\0')
    {
        printf("dictionary[%d] = %c\n", i, dictionary[i]);
        i++;
    }
    //igual hau eztot eingo, 1.2) Limpiar todos los espacios INNECESARIOS (que no se van a imprimir) = siempre que esté fuera de comillas, quita espacio
            //clean_input = ft_no_spaces(input);
    //baina bai, una función a la que yo pueda llamar y me devuelva si me encuentro dentro o fuera de comillas. Hola, cuando encuentro un echo o algo de esto (edozer gauza), checkeo con esta función aber si estoy dentro o fuera para ver cómo debo actuar.
    //ft_quotes_dictionary
    //ft_is_it_in_quotes(input)
    //2. obtener 
}