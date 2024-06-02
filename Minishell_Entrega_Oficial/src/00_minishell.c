/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   00_minishell.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uxmancis <uxmancis@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 10:27:41 by uxmancis          #+#    #+#             */
/*   Updated: 2024/05/19 15:10:37 by uxmancis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../inc/minishell.h"

/*ft_pipe_after_pipe
*
*   When there is no content between pipes, error is printed.
*
*   Returns: 
*       1: pipe after pipe was found
*       0: no pipe after pipe found
*/
int ft_pipe_after_pipe(char *input)
{
    int i;
    int len;

    i = 0;
    len = ft_strlen(input);
    printf("ft_pipe_after_pipe\n");
    while (input[i] != '\0')
    {
        if (input[i] == '|')
        {
            while (ft_isspace(input[i]))
                i++;
            if (i == len)
                return (0);
            if (input[i])
            {
                if (input[i] == '|')
                    return (1);
            }
            else
                return (0);
        }
        i++;
    }
    return (0);
}

/* ft_get_substr
*
*   Returns:
*       -1: Error
*               ft_quotes: syntax error: unclosed quotes
*               ft_where_r_pipes: syntax error near unexpected token `|'
*        0: Success
*/
int ft_get_substr(t_prompt *prompt)
{    
    //int nb_of_substr;
    //conclusiones análisis: ¿qué conclusiones quiero?
    //1. número de comandos a ejecutar = número de procesos hijo a crear
    prompt->nb_of_substr = 1;
    prompt->dict_quotes = malloc(sizeof(int) * (ft_strlen(prompt->input) + 1));
    prompt->dict_quotes[ft_strlen(prompt->input)] = '0'; //es para indicar final de array. Al ser int *, no nos deja '\0' para finalizar array. El 9 es el final. ¿Podríamos hacerlo char *? Sí, pero los indicadres son 0, 1, 2, integers. Podríamos hacerlo '0', '1' y '2', pero no quiero.
    if (ft_quotes (prompt->input, &prompt->dict_quotes)== -1) //1. Asegurar 100% comillas principales cerradas y generar dict_quotes (&: para que se actualicen los valores = se informe por primera vez el diccionario dict_quotes). Mando &prompt, para que se actualice el diccionario de vuelta.
    {
        ft_puterror("syntax error: unclosed quotes\n");
        return(-1);
    }
    if (ft_pipe_after_pipe(prompt->input))
    {
        ft_puterror("syntax error near unexpected token `||'\n");
        return (-1);
    }
    if (ft_strlen(prompt->input) == 0)
        return (-1); //input vacío
    //test dictionary
    printf(BLUE);
    //printf("test dictionary, len = %d\n", (int)ft_strlen(prompt->dict_quotes)); //ya ezin leike ze dict_quotes da int *
    int len_input;
    int i;
    i = 0;
    len_input = ft_strlen(prompt->input);
    while (len_input > 0)
    {
        printf("dictionary[%d] = %d\n", i, prompt->dict_quotes[i]);
        len_input--;
        i++;
    }
    printf(RESET_COLOR);
    //init_instructions(input, prompt, dictionary); //to consider if pipe is pipe or not.
    //prompt->arr_index_pipes = ft_where_r_pipes(&prompt);
    if (ft_where_r_pipes(&prompt) == -1)
        return (-1);
    if (prompt->nb_of_pipes > 0)
        ft_split_input(&prompt);
    return (0);
    //printf(AQUAMARINE"RESULTADO SPLITEADO:\n");
    /*i = 0;
	while (nb_of_substr > 0)
	{
		printf(AQUAMARINE"substr%d = %s\n"RESET_COLOR, i, prompt->total_substr_input[i]);
		nb_of_substr--;
		i++;
	}*/
    //una función a la que yo pueda llamar y me devuelva si me encuentro dentro o fuera de comillas. Hola, cuando encuentro un echo o algo de esto (edozer gauza), checkeo con esta función aber si estoy dentro o fuera para ver cómo debo actuar.
}

// void ft_begin(int argc, char **argv, char **env)
// {
//     t_prompt prompt;

//     (void)argc;
//     (void)argv;
//     (void)env;
//     prompt.input = readline("minishell-1.0$ "); //ya nos genera input, 1 cadena con las comillas etc.
//     add_history(prompt.input);
//     //checkear posibles errores a devolver
//     //analizar qué habrá que hacer
//     printf(YELLOW);
//     printf("input a analizar = %s, len = %d\n", prompt.input, (int)ft_strlen(prompt.input));
//     printf(RESET_COLOR);
//     //prompt = NULL;
//     ft_get_substr(&prompt);
//     printf(AQUAMARINE"00_minichell.c - ft_begin| RTDO. SUBSTR\n"RESET_COLOR);
//     if (prompt.nb_of_substr == 1)
//         printf(AQUAMARINE"             1 box: %s\n"RESET_COLOR, prompt.input);
//     else
//     {
//         printf(AQUAMARINE"RESULTADO SPLITEADO:\n"RESET_COLOR);
//         int i;
//         int tmp_to_debug_nb_of_substr;
//         i = 0;
//         tmp_to_debug_nb_of_substr = prompt.nb_of_substr;
//         while (tmp_to_debug_nb_of_substr > 0)
// 	    {
//             printf(AQUAMARINE"substr%d = %s\n"RESET_COLOR, i, prompt.total_substr_input[i]);
//             tmp_to_debug_nb_of_substr--;
//             i++;
// 	    }
//     }
//     //printf(YELLOW"nb_of_boxes = %d\n"RESET_COLOR, prompt.nb_of_substr);
//     ft_gen_boxes(&prompt); //no quiero que se actualice nada, solo pase la info
//     //ft_exec
// }

// int main(int argc, char **argv, char **env)
// {
//     (void)argc;
//     (void)argv;
//     (void)env;
//     ft_print_welcome();
//     while(1)
//         ft_begin(argc, argv, env);
// }