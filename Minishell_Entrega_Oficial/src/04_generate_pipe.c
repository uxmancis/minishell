/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   04_generate_pipe.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbonilla <dbonilla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 17:42:33 by dbonilla          #+#    #+#             */
/*   Updated: 2024/05/19 16:16:41 by dbonilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int create_pipe(t_box *box) 
{
    pid_t pid;

    // Crear un pipe
    if (pipe(box->pipefd) == -1) 
    {
        perror("pipe");
        return -1;
    }

    // Crear un proceso hijo
    pid = fork();
  
    if (pid == -1) 
    {
        perror("fork");
        close(box->pipefd[0]);
        close(box->pipefd[1]);
        return -1;
    }

    box->pid = pid;
    return 0;
}

void handle_child(t_box *box, t_prompt *data) 
{
    printf("               handle_child | Estamos en el proceso hijo\n");
    
    close(box->pipefd[0]);  // Cerrar el extremo de lectura del pipe

    // Guardar los descriptores de archivo originales
    data->line_infd = box->infd;
    data->line_outfd = box->outfd;

    // Redirigir stdout al extremo de escritura del pipe
    dup2(box->pipefd[1], STDOUT_FILENO);
    close(box->pipefd[1]);  // Cerrar el extremo de escritura original del pipe

    printf("el PID del hijo es %d\n",getpid());

    if (handle_redirection(&box, data) != 0) 
    {
        perror("Error al manejar la redirección");
        exit(1);
    }
}

int handle_child_process(t_box *box, t_prompt *data , int substr_id) 
{
    int status;
    (void)substr_id;
    box->pid = fork();
        
    printf(YELLOW"    handle_child_process\n"RESET_COLOR);
    if (box->pid == -1) 
    {
        perror("Error al bifurcar el proceso");
        return 1;
    }
    if (box->pid == 0) 
    {
        handle_child(box, data);
        exit(0);  // Asegúrate de que el proceso hijo termine después de ejecutar el bucle
    }
    else 
    {
        handle_parent_process(box);
        if (waitpid(box->pid, &status, 0) > 0 && WIFEXITED(status) && WEXITSTATUS(status) != 0) 
        {
            return 1;  
        }

        printf("Estamos en el proceso padre, el PID del hijo es %d\n", getpid());
    }

    return 0;
}

int handle_parent_process(t_box *box) 
{
    if (close(box->pipefd[1]) == -1)  // Cerrar el extremo de escritura del pipe
        return -1;

    // Leer la salida del proceso hijo desde el pipe
    char buffer[1024];
    ssize_t numRead = read(box->pipefd[0], buffer, sizeof(buffer));
    if (numRead == -1)
        return -1;

    if (close(box->pipefd[0]) == -1)  // Cerrar el extremo de lectura del pipe
        return -1;

    // Imprimir el PID del proceso hijo
    printf("PID del proceso hijo: %d\n", box->pid);

    return 0;
}