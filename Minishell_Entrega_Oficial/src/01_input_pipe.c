/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   01_input_pipe.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uxmancis <uxmancis@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 12:55:10 by uxmancis          #+#    #+#             */
/*   Updated: 2024/05/19 15:10:31 by uxmancis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../inc/minishell.h"

/*  ft_pipe_last
*
*   Checks whether if pipe is in last position of input.
*   Returns:
*       1: YES, pipe in last position (will be managed as error)
*       0: NO, other character in last position
*/
int ft_pipe_last (char *input)
{
    int i; 

    i = ft_strlen(input) - 1;
    //printf(BLUE"FT_PIPE_LAST, i = %d\n"RESET_COLOR, i);
    while (i > 0)
    {
        //printf("input[%d] = %c\n", i, input[i]);
        while (ft_isspace(input[i]))
            i--;
        if (input[i] == '|')
        {
            //printf(MAGENTA"pipe in last position\n"RESET_COLOR);
            return (1);
        }
        else
            break;
    }
    return (0);
}

/*  ft_pipe_first
*
*   Checks whether if pipe is in first position of input.
*   Returns:
*       1: YES, pipe in first position (will be managed as error)
*       0: NO, other character in first position
*/
int ft_pipe_first (char *input)
{
    int i; 

    i = 0;
    while (input[i] != '\0')
    {
        while (ft_isspace(input[i]))
            i++;
        if (input[i] == '|')
        {
            //printf(MAGENTA"pipe in first position\n"RESET_COLOR);
            return (1);
        }
        else
            break;
    }
    return (0);
}

/*ft_pipe_first_or_last
*   
*   Returns:
*       1: Error found (pipe in first or last position)
*       O: Everything ok, no pipes found in invalid position (first or last)
*/
int ft_pipe_first_or_last (char *input)
{
    if (ft_pipe_first(input) == 1 || ft_pipe_last(input) == 1)
    {
        //printf(RED"pipes in first or last position\n"RESET_COLOR);
        return (-1);
    }
    //printf(GREEN"no pipes in first or last position\n"RESET_COLOR);
    return (0);
}


/*ft_is_there_pipe
*
*   1. Checks whether if pipes are found or not. Returns: -1, 0, >0  
*       -1: Error: pipe found in incorrect position, [0] or last position.
*       0: No pipes found
*       >0: number of found pipes
*
*   2. arr_index_pipes:
*       Index of real pipes (out of quotes) will be stored in array, for
*       future split. Information in char *dictionary is used to know
*       location of pipe (0: out of quotes, 1: inside single or 2. inside
*       double quotes).
*/
int ft_is_pipe(t_prompt **prompt)
{
    int i;
    int counter;
    //int tmp_len_dict;

    //i = 0;
    counter = 0;
    //printf(YELLOW"input = %s\n"RESET_COLOR, prompt->input);
    //tmp_len_dict = ft_strlen(prompt->input);
    /*printf("dict_quotes: ");
    while (tmp_len_dict > 0)
    {
        printf("%c", (int)prompt->dict_quotes[i]);
        i++;
        tmp_len_dict--;
    }
    printf("\n");*/
    i = 0;
    while ((*prompt)->input[i] != '\0')
    {
        //printf(MAGENTA"case %d: input[%d] = %c, dict: %c\n"RESET_COLOR, i, i, prompt->input[i], prompt->dict_quotes[i]);
        if ((*prompt)->input[i] == '|' && (*prompt)->dict_quotes[i] == 0) //eztakit dictionarykin zeba einbihoten konparau con '0' en vez de 0, ze ya no son chars, son int.
        {
            if (ft_pipe_first_or_last((*prompt)->input) == -1) //first or last position  --> //PDTE. actualizar lo de última posición: implementarlo bien. No nececsariamente tiene que estar en strlen -1 -> puede ser |   ddkfjjdsdf |      (espacios)
                return (-1);
            counter++;
        }
        i++;
    }
    //printf(MAGENTA"counter = %d\n"RESET_COLOR, counter);
    if (counter == 0)
        return (0); //no pipes found
    return (counter); //returns number of found pipes
}

/*DESCRIPTION:
*   Returns:
*       0: No index found
*       >0: Number of found indexes
*
*   Additionally, array is created with indexes of input
*   where pipes are located.
*/
void set_index_pipe(t_prompt **prompt)
{
    int i;
    int y; 

    i = 0;
    y = 0;
    while ((*prompt)->input[i] != '\0')
    {
        if ((*prompt)->input[i] == '|')
        {
            if ((*prompt)->dict_quotes[i] == 0) //si sí está fuera de comillas el pipe, '0' en el diccionario, entonces sí es un pipe cuyo índice quiero guardar
            {
                (*prompt)->arr_index_pipes[y] = i; //me guardo el índice del pipe en arr_index_pipes
                y++;
            }
        }
        i++;
    }
}

/*
*   1. ft_is_pipe: Tells us whether if there are any pipes on valid position of input
*   2. If yes pipes in valid location --> cretes array with indexes of found pipes
*/
void ft_where_r_pipes(t_prompt **prompt)
{
    //int nb_of_pipes;
    //char *arr_index_pipes; //must be created here (not sent as parameter and updated with &) as we need nb_of_pipes to know len of arr_index_pipes (for malloc)
    int aux_para_imprimir_nb_of_pipes;
    
    (*prompt)->nb_of_pipes = ft_is_pipe(prompt); //el valor que queremos obtener es nb_of_pipes, por lo que desreferenciamos prompt (*prompt), no necesitamos que sus valores se actualicen
    printf(MAGENTA"01_input_pipe.c - ft_where_r_pipes: nb_of_pipes = %d\n"RESET_COLOR, (*prompt)->nb_of_pipes);
    if ((*prompt)->nb_of_pipes == -1)
        ft_puterror_exit("syntax error near unexpected token `|'\n");
    else if ((*prompt)->nb_of_pipes > 0) // si sí que hay algún pipe carcter
    {
        (*prompt)->arr_index_pipes = malloc(sizeof(int) * ((*prompt)->nb_of_pipes)); //sin el más uno, es int*, no tiene '\0' al final para indicar final. Puedo usar el 0 como indicador de final. Ze la posición nunca será 0, ese error ya lo habré gestinado. Ze ona! Ta hola ahall dot len lortu! Aunque un poco rebuscado/chapu igual?
        if (!(*prompt)->arr_index_pipes)
            ft_puterror_exit("malloc error\n");
        //(*prompt)->arr_index_pipes[(*prompt)->nb_of_pipes] = 0; //ahal dot hola ein, ze sekula ezta izengo 0, ze el contenido = índices = ezta sekula izengo 0.
        //printf(YELLOW"last_arr[%d] = %d\n"RESET_COLOR, nb_of_pipes, prompt->arr_index_pipes[nb_of_pipes]);
        set_index_pipe(prompt);
        int i; 
        i = 0;
        //while ((*prompt)->arr_index_pipes[i] != '0')
        aux_para_imprimir_nb_of_pipes = (*prompt)->nb_of_pipes; //eztot nahi el real variable txikitxerik tamainuz
        while ((aux_para_imprimir_nb_of_pipes) > 0) //bakarrik inprimitzeko
        {
            printf(MAGENTA"arr_index_pipes[%d] = %d\n"RESET_COLOR, i, (*prompt)->arr_index_pipes[i]);
            i++;
            aux_para_imprimir_nb_of_pipes--;
        }
        printf(MAGENTA"salida de ft_where_r_pipes\n");
        //return ((*prompt)->arr_index_pipes); //cuando devolvemos arr_index_pipes ya sabremos number of pipes, con ft_strlen
    }
    //printf(MAGENTA"salida de ft_where_r_pipes\n");
    //return (0); //no pipes found
}
