/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   06_execute_commands.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbonilla <dbonilla@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 18:00:19 by dbonilla          #+#    #+#             */
/*   Updated: 2024/05/16 22:53:10 by dbonilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"


// int execute_multiple_commands(t_box *box) {
//     int fd[2];
//     int prev_fd = 0;
//     int i = 0;
    
//     while (i < box->prompt->nb_of_substr) {
//         pipe(fd);

//         if (fork() == 0) {
//             // Este es el proceso hijo
//             if (prev_fd != 0) {
//                 // No es el primer comando, así que leemos del pipe anterior
//                 dup2(prev_fd, 0);
//                 close(prev_fd);
//             }

//             if (i != box->prompt->nb_of_substr - 1) {
//                 // No es el último comando, así que escribimos en el pipe actual
//                 dup2(fd[1], 1);
//             }

//             close(fd[0]);
//             close(fd[1]);
//         } 
//         else 
//         {          
//             // Este es el proceso padre
//             close(fd[1]);

//             if (prev_fd != 0) {
//                 close(prev_fd);
//             }

//             prev_fd = fd[0];
//         }

//         i++;
//     }

//     return 0;
// }


// int execute_simple_command(t_box *box)
// {
//     // Realizar las redirecciones
//     if (box->infd != -1) {
//         dup2(box->prompt->line_infd, 0);
//         close(box->prompt->line_infd);
//     }
//     if (box->outfd != -1) {
//         dup2(box->prompt->line_outfd , 1);
//         close(box->prompt->line_outfd);
//     }

//     // Verificar si el comando es un comando incorporado
//     if (is_builtin(box->input_substr[0])) {
//         // Ejecutar el comando incorporado
//         execute_bultings(*box);
//     } else {
//         // Ejecuta el comando externo
//         execvp(box->input_substr[0], box->input_substr);
//         perror("execvp");
//         _exit(1);
//     }

//     return 0;
// }

// int execute_commands(t_box *box) 
// {
//     if (box->prompt->nb_of_substr == 1) {
//         // Si solo hay un comando, ejecuta execute_simple_command
//         if (!execute_simple_command(box)) {
//             return 0;
//         }
//     } else if (box->prompt->nb_of_substr > 1) {
//         // Si hay múltiples comandos, ejecuta execute_multiple_commands
//         if (!execute_multiple_commands(box)) {
//             return (0);
//         }
//     }

//     return (1);
// }
