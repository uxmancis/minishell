/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uxmancis <uxmancis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 10:27:41 by uxmancis          #+#    #+#             */
/*   Updated: 2024/04/14 16:03:05 by uxmancis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void ft_begin(int argc, char **argv, char **env)
{
    char *input;

    (void)argc;
    (void)argv;
    (void)env;
    input = readline("minishell-1.0$ "); //ya nos genera input, 1 cadena con las comillas etc.
    add_history(input);
    //checkear posibles errores a devolver
    //analizar qué habrá que hacer
    printf(YELLOW);
    printf("input a analizar = %s ||| len = %d\n", input, (int)ft_strlen(input));
    printf(RESET_COLOR);
    ft_analyse_input(input);
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