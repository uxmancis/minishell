/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   00_minishell.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uxmancis <uxmancis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 10:27:41 by uxmancis          #+#    #+#             */
/*   Updated: 2024/05/01 10:18:28 by uxmancis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void ft_get_substr(t_prompt *prompt)
{    
    //int nb_of_substr;
    //conclusiones análisis: ¿qué conclusiones quiero?
    //1. número de comandos a ejecutar = número de procesos hijo a crear
    prompt->nb_of_substr = 1;
    prompt->dict_quotes = malloc(sizeof(int) * (ft_strlen(prompt->input) + 1));
    prompt->dict_quotes[ft_strlen(prompt->input)] = '0'; //es para indicar final de array. Al ser int *, no nos deja '\0' para finalizar array. El 9 es el final. ¿Podríamos hacerlo char *? Sí, pero los indicadres son 0, 1, 2, integers. Podríamos hacerlo '0', '1' y '2', pero no quiero.
    if (ft_quotes (&prompt)== -1) //1. Asegurar 100% comillas principales cerradas y generar dict_quotes (&: para que se actualicen los valores = se informe por primera vez el diccionario dict_quotes). Mando &prompt, para que se actualice el diccionario de vuelta.
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
        printf("dictionary[%d] = %c\n", i, prompt->dict_quotes[i]);
        len_input--;
        i++;
    }
    printf(RESET_COLOR);
    //init_instructions(input, prompt, dictionary); //to consider if pipe is pipe or not.
    //prompt->arr_index_pipes = ft_where_r_pipes(&prompt);
    ft_where_r_pipes(&prompt);
    if (prompt->arr_index_pipes == 0)
    {
        printf("no pipes found, go analize the box directly\n");
        //no pipes found --> ir directamente a analizar caja
    }
    else if (prompt->arr_index_pipes > 0) //pipes found
    {
        printf(YELLOW"MINISHELL.C (ft_get_substr): yes pipes found\n"RESET_COLOR);
        printf(YELLOW"NB_OF_PIPES = %d\n"RESET_COLOR, prompt->nb_of_pipes);
        //total_substr_input = ft_split_input(&prompt);
        prompt->nb_of_substr = ft_split_input(&prompt);
        /*i = 0;
        while (prompt->arr_index_pipes[i] != '0')
        {
            printf(YELLOW"arr_index_pipes[%d] = %d\n"RESET_COLOR, i, prompt->arr_index_pipes[i]);
            i++;
        }*/
    }
    printf(AQUAMARINE"RESULTADO SPLITEADO:\n");
    /*i = 0;
	while (nb_of_substr > 0)
	{
		printf(AQUAMARINE"substr%d = %s\n"RESET_COLOR, i, prompt->total_substr_input[i]);
		nb_of_substr--;
		i++;
	}*/
    //una función a la que yo pueda llamar y me devuelva si me encuentro dentro o fuera de comillas. Hola, cuando encuentro un echo o algo de esto (edozer gauza), checkeo con esta función aber si estoy dentro o fuera para ver cómo debo actuar.
}

void ft_begin(int argc, char **argv, char **env)
{
    t_prompt prompt;

    (void)argc;
    (void)argv;
    (void)env;
    prompt.input = readline("minishell-1.0$ "); //ya nos genera input, 1 cadena con las comillas etc.
    add_history(prompt.input);
    //checkear posibles errores a devolver
    //analizar qué habrá que hacer
    printf(YELLOW);
    printf("input a analizar = %s, len = %d\n", prompt.input, (int)ft_strlen(prompt.input));
    printf(RESET_COLOR);
    //prompt = NULL;
    ft_get_substr(&prompt);
    int i;
    int tmp_to_debug_nb_of_substr;
    i = 0;
    tmp_to_debug_nb_of_substr = prompt.nb_of_substr;
	while (tmp_to_debug_nb_of_substr > 0)
	{
		printf(AQUAMARINE"substr%d = %s\n"RESET_COLOR, i, prompt.total_substr_input[i]);
		tmp_to_debug_nb_of_substr--;
		i++;
	}
    //printf(YELLOW"nb_of_boxes = %d\n"RESET_COLOR, prompt.nb_of_substr);
    ft_analyse_boxes(&prompt); //no quiero que se actualice nada, solo pase la info
    //ft_exec
}

int main(int argc, char **argv, char **env)
{
    (void)argc;
    (void)argv;
    (void)env;
    ft_print_welcome();
    while(1)
        ft_begin(argc, argv, env);
}