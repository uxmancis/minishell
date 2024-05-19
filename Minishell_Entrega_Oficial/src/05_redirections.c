/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   05_redirections.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbonilla <dbonilla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 15:40:11 by codespace         #+#    #+#             */
/*   Updated: 2024/05/19 16:21:21 by dbonilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../inc/minishell.h"

// int close_files(t_box *box, int i) 
// {
//     // Accede al i-ésimo elemento del array de estructuras t_box
//     t_box *current_box = box[i];

//     // Si el descriptor de archivo de entrada de la caja actual es diferente al descriptor de archivo de entrada de la línea
//     if (current_box->infd != current_box->prompt->line_infd) {
//         // Cierra el descriptor de archivo de entrada de la caja actual
//         if (close(current_box->infd) == -1) {
//             perror("Error al cerrar infd");
//             return 1;
//         }
//     }
//     // Si el descriptor de archivo de salida de la caja actual es diferente al descriptor de archivo de salida de la línea
//     if (current_box->outfd != current_box->prompt->line_outfd) {
//         // Cierra el descriptor de archivo de salida de la caja actual
//         if (close(current_box->outfd) == -1) {
//             perror("Error al cerrar outfd");
//             return 1;
//         }
//     }
//     // Devuelve 0 para indicar que la función se ha ejecutado correctamente
//     return 0;
// }

// int handle_input_infile(t_box **box)
// {
//     int i = 0;
    
//     while ((*box)->dict_red_index_type[i][3] != -1)
//     {
//         if ((*box)->dict_red_index_type[i][3] == 1 || (*box)->dict_red_index_type[i][3] == 2) {
//             if ((*box)->words_infile[i] != NULL) {
//                 int fd = open((*box)->words_infile[i], O_RDONLY);
//                 if (fd == -1) {
//                     perror((*box)->words_infile[i]);
//                     return -1;
//                 }
//                 (*box)->infd[i] = fd;
//             } else {
//                 printf("Error: No se proporcionó el nombre del archivo de entrada.\n");
//                 return -1;
//             }
//         } else {
//             pipe((*box)->pipe[i]);
//             (*box)->infd[i] = (*box)->pipe[i];
//             (*box)->outfd[i] = (*box)->pipe[i];
//         }
//         i++;
//     }
//     return (0);
// }

// }
// int handle_output_append(t_box *box,int i)
// {
//     if ((*box)->dict_red_index_type[i][3] != -1) {
//         if ((*box)->dict_red_index_type[i][3] == 1) {
//             (*box)->outfd = open((*box)->words_outfile_append[(*box)->dict_red_index_type[i][4] + 1], O_WRONLY | O_CREAT | O_TRUNC, 0666);
//         } else if ((*box)->dict_red_index_type[i][3] == 2) {
//             (*box)->outfd = open((*box)->prompt->total_substr_input[(*box)->dict_red_index_type[i][4] + 1], O_WRONLY | O_CREAT | O_APPEND, 0666);
//         }
//     } else {
//         pipefd((*box)->pipefd);
//         (*box)->infd = (*box)->pipefd[1];
//         (*box)->outfd = (*box)->pipefd[0];
//     }
//     return (0);
// }

// int handle_output(t_box *box, int i) 
// {
//     if (box->dict_red_index_type[i][3] != -1) {
//         if (box->dict_red_index_type[i][3] == 1) {
//             box->outfd = open(box->prompt->total_substr_input[box->dict_red_index_type[i][4] + 1], O_WRONLY | O_CREAT | O_TRUNC, 0666);
//         } else if (box->dict_red_index_type[i][3] == 2) {
//             box->outfd = open(box->prompt->total_substr_input[box->dict_red_index_type[i][4] + 1], O_WRONLY | O_CREAT | O_APPEND, 0666);
//         }
//     } else {
//         pipefd(box->pipefd);
//         box->infd = box->pipefd[1];
//         box->outfd = box->pipefd[0];
//     }
//     return 0;
// }

int handle_heredoc(t_box **box)
{
    int tmp_nbr_of_hrdc;
    int word_index = 0;
    tmp_nbr_of_hrdc = (*box)->nb_of_heredocs;

    printf(YELLOW"handle_heredoc\n"RESET_COLOR);
    while (tmp_nbr_of_hrdc > 0 )
    {
        char *line;

        
        while ((line = readline("heredoc >")) != NULL && (*box)->words_hrdc[word_index] != NULL) 
        {
            printf("primera palbra %s\n", (*box)->words_hrdc[word_index]);
            printf("primera palbra %s\n", (*box)->words_hrdc[word_index + 1]);
            if (ft_strcmp(line, (*box)->words_hrdc[word_index]) == 0) 
            {
                word_index++;
                free(line);
                break;
            }
            write((*box)->outfd, ">", 1);  // Escribe el símbolo ">" en la consola
            write((*box)->outfd, line, strlen(line));  // Escribe la línea en la consola
            free(line);
            write((*box)->outfd, "\n", 1);  // Escribe un salto de línea en la consola
        }
        close((*box)->outfd);  // Cierra la salida actual

        // Abre un nuevo descriptor de archivo para la siguiente redirección
        // Asegúrate de reemplazar "next_redirection_file" con el nombre de archivo de la siguiente redirección
        // (*box)->outfd = open("next_redirection_file", O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);

        if ((*box)->outfd == -1) 
        {
            perror("open");
            return -1;
        }

        printf("tmp_nbr_of_hrdc = %d\n", tmp_nbr_of_hrdc);  
        tmp_nbr_of_hrdc--;
    }
    return 0;
}






int handle_redirection(t_box **box, t_prompt *data)
{
    int tmp_nb_of_red_type;
    int red_type = 0;
    (void) data;

    tmp_nb_of_red_type = (*box)->nb_of_redir;
    printf("               handle_redirection\n");
    while (tmp_nb_of_red_type > 0) 
    {
        // Aquí es donde usarías pid para redirigir la entrada/salida según sea necesario.
        // Por ejemplo, podrías hacer algo como esto:
        if ((*box)->dict_red_index_type[red_type][1] == HEREDOC)
        {
            if (handle_heredoc(box) == -1)
            {  // Llama a la función del heredoc
                return -1;
            }
        }
        write(1, "Error: Invalid redirection type\n", 33);

        // else if ((*box)->dict_red_index_type[red_type][1] == INFILE)
        // {
        //     if (handle_input_infile(box) == -1)
        //     {
        //         return -1;
        //     }   
        // }
        // if ((*box)->dict_red_index_type[red_type][1] == OUTFILE_STRONG) 
        // {
        //     if (handles_output_strong(box) == -1)
        //     {
        //         return -1;
        //     }
        // }
        // else if ((*box)->dict_red_index_type[red_type][1] == OUTFILE_APPEND) 
        // {
        //     if (handle_output_append(box) == -1)
        //     {
        //         return -1;
        //     }
        // }
        // else {
        //     handle_output((*box));  // Aquí se ha cambiado *box a box
        // }

        tmp_nb_of_red_type--;
        red_type++;
    }

    return 0;
}





// int handle_redirection(t_box **box, t_prompt *data)
//  {
//     int tmp_nb_of_red_type;


//     tmp_nb_of_red_type = (*box)->nb_of_redir;
    
//     while (tmp_nb_of_red_type > 0) 
//     {
//     if (ft_strncmp((*box)->prompt->total_substr_input[(*box)->dict_red_index_type[tmp_nb_of_red_type][4]], "<<") == 0)
//         if (handle_heredoc(box, data) == -1)
//         {  // Llama a la función del heredoc
//             return -1;
//         }
//         tmp_nb_of_red_type--;
//     }
//      else if (red_type == INFILE) {
//     handle_input_infile(box);
//     } else if (red_type == OUTFILE_STRONG) {
//         handles_output_strong(box, i);
//     } else if (red_type == OUTFILE_APPEND) {
//         handle_output_append(box, i);
//     } else {
//         handle_output((*box), i);  // Aquí se ha cambiado *box a box
//     }

//     return 0;
// }
