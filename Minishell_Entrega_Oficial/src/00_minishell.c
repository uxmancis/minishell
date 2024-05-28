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

void ft_get_substr(t_prompt *prompt)
{    
    //int nb_of_substr;
    //conclusiones análisis: ¿qué conclusiones quiero?
    //1. número de comandos a ejecutar = número de procesos hijo a crear
    prompt->nb_of_substr = 1;
    prompt->dict_quotes = malloc(sizeof(int) * (ft_strlen(prompt->input) + 1));
    prompt->dict_quotes[ft_strlen(prompt->input)] = '0'; //es para indicar final de array. Al ser int *, no nos deja '\0' para finalizar array. El 9 es el final. ¿Podríamos hacerlo char *? Sí, pero los indicadres son 0, 1, 2, integers. Podríamos hacerlo '0', '1' y '2', pero no quiero.
    if (ft_quotes (prompt->input, &prompt->dict_quotes)== -1) //1. Asegurar 100% comillas principales cerradas y generar dict_quotes (&: para que se actualicen los valores = se informe por primera vez el diccionario dict_quotes). Mando &prompt, para que se actualice el diccionario de vuelta.
        ft_puterror_exit("syntax error: unclosed quotes\n");
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
    ft_where_r_pipes(&prompt);
    if (prompt->nb_of_pipes > 0)
        ft_split_input(&prompt);
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