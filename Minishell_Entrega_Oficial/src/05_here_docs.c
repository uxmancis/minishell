/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   05_here_docs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uxmancis <uxmancis@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 18:28:26 by uxmancis          #+#    #+#             */
/*   Updated: 2024/06/02 09:41:01 by uxmancis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int handle_heredoc(t_box **box)
{
    int tmp_nbr_of_hrdc;
    // int word_index = 0;
    int pipefd[2];

    // Crear un nuevo pipe
    if (pipe(pipefd) == -1) 
    {
        perror("pipe");
        return -1;
    }
    tmp_nbr_of_hrdc = (*box)->nb_of_heredocs;
    while (tmp_nbr_of_hrdc != 0 )
    {
        char *line;
        while ((line = readline("heredoc>")) != NULL && (*box)->words_hrdc[0] != NULL)
        {
            printf(GREEN "          line = %s\n" RESET_COLOR, line);
            if (ft_strcmp(line, (*box)->words_hrdc[0]) == 0)
            {
                (*box)->words_hrdc++;
                free(line);
                break;
            }
            free(line);
            write(pipefd[1], "\n", 1);  // Escribe un salto de línea en el pipe
        }
        close(pipefd[1]);  // Cierra el extremo de escritura del pipe

        // Aquí puedes leer del extremo de lectura del pipe en el proceso padre
        char buffer[1024];
        ssize_t count;
        while ((count = read(pipefd[0], buffer, sizeof(buffer)-1)) > 0) {
            buffer[count] = '\0';
            printf("%s", buffer);
        }

        printf("tmp_nbr_of_hrdc = %d\n", tmp_nbr_of_hrdc);  
        tmp_nbr_of_hrdc--;
    }
    close(pipefd[0]);
    // handle_signal(SIGINT);  // Llamar a handle_signal con SIGINT  // Enviar SIGINT
  // Cierra el extremo de lectura del pipe cuando se ha terminado de leer
    return 0;
}