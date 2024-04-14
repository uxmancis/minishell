/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analyse_input.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uxmancis <uxmancis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 10:53:21 by uxmancis          #+#    #+#             */
/*   Updated: 2024/04/14 11:47:38 by uxmancis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void ft_comillas(char *input)
{
    int i; 

    i = 0;
    printf(RED);
    printf(">> entrada en bucle - análisis comillas\n");
    printf(RESET_COLOR);
    while (input[i] != '\0')
    {
        if (input[i] == '\'')
        {
            printf(YELLOW);
            printf("        ENTRADA comillas simples, input[%d] = %c\n", i, input[i]);
            printf(RESET_COLOR);
            i++;
            printf("i++, line 29, input[%d] = %c\n", i, input[i]);
            while (/*input[i] != '\0' && */input[i] != '\'')
            {
                printf("             dentro comillas simples, input[%d] = %c\n", i, input[i]);
                i++;
                printf("             i++, line 33, input[%d] = %c\n", i, input[i]);
            }
            printf(YELLOW);
            printf("        SALIDA comillas simples, input[%d] = %c\n\n", i, input[i]);
            printf(RESET_COLOR);
            //i++;
            //printf("             i++, line 42, input[%d] = %c\n", i, input[i]);
        }
        if (input[i] == '\"')
        {
            printf(MAGENTA);
            printf("        ENTRADA comillas DOBLES, input[%d] = %c\n", i, input[i]);
            printf(RESET_COLOR);
            i++;
            while (/*input[i] != '\0' && */input[i] != '\"')
            {
                printf("             dentro comillas DOBLES, input[%d] = %c\n", i, input[i]);
                i++;
                printf("             i++, line 44, input[%d] = %c\n", i, input[i]);
            }
            printf(MAGENTA);
            printf("        SALIDA comillas DOBLES, input[%d] = %c\n\n", i, input[i]);
            printf(RESET_COLOR);
            //i++;
            //printf("             i++, line 60, input[%d] = %c\n", i, input[i]);
        }
        printf("i++, line 49, input[%d] = %c\n", i, input[i]);
        i++;
    }
    printf(GREEN);
    printf("<< salida de bucle - análisis comillas\n");
    printf(RESET_COLOR);
}

void ft_analyse_input(char *input)
{
    //declarar estructura que va a devolver: con todas las instrucciones
    
    //conclusiones análisis: ¿qué conclusiones quiero?
    //1. número de comandos a ejecutar = número de procesos hijo a crear
    ft_comillas(input);
    //2. obtener 
}