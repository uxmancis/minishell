/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipex.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uxmancis <uxmancis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 12:22:00 by uxmancis          #+#    #+#             */
/*   Updated: 2024/04/14 12:22:01 by uxmancis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_pipex.h"

static void	ft_process(char *str, char **envp)
{
	pid_t	pid;
	int		fd[2];
	int		status;

	if (pipe(fd) == -1) //CREAR TUBERÍA (pipe)
		ft_exit_w_error("errno");
	pid = fork(); //crear nuevo proceso (hijo), duplicando el proceso que la llama (padre). Ahora existen 2 procesos.
	if (pid == -1)
		ft_exit_w_error("errno"); //er
	if (pid > 0) //Código ejecutado por proceso padre
	{
		close(*(fd + 1)); //Cierre de extremo de escritura de la tubería, fd[1]. El proceso padre solo leerá de la tubería.
		dup2(*(fd + 0), STDIN_FILENO); //Redirección entrada proceso padre (tubería, fd[0])
		waitpid(pid, &status, 0); //espera a que el hijo termine
	}
	else //pid == 0, Código ejecutado por proceso hijo
	{
		close(*(fd + 0)); //Cierre de extremo de llectura de a tubería, fd[0].
		dup2(*(fd + 1), STDOUT_FILENO); //Redirección salida proceso hijo, escribe en tubería, fd[1]
		ft_run_command(str, envp); //str = comando a ejecutar
	}
}

static int	ft_args_empty(int argc, char **argv)
{
	int	i;

	i = 0;
	while (i < argc)
	{
		if (ft_strcmp(*(argv + i), "") == 0)
			return (1);
		i++;
	}
	return (0);
}


/*
*	<fcntl.h>
*	· O_RDONLY: el archivo solo debe abrirse para lectura "Open Read-Only".
*	Solo se puede leer, no se puede escribir en él.
*	· O_WRONLY: el archivo solo debe abrirse para escritura "Open Read-Only".
*	Se puede escribir, pero no leer.
*	· O_CREAT: si el archivo no existe, debe crearse. Si el archivo ya existe,
*	esta flag no tiene ningún efecto.
*	· O_TRUNC: el archivo, si existe y si ya contiene datos, se vaciará. La
*	longitud se truncará a 0 antes de abrir e archivo.
*
*	open: devuelve fd (Success), o devuelve -1 (Error) //Librería <fcntl.h>
*	open (<pathname>, <flags>, <mode>):
*		pathname: fd a abrir
*		flags: entero que especifica el modo de apertura y otras opciones. Puede
*			   ser la combinación de varias constantes. P.ej.: O_WRONLY | O_CREAT | O_TRUNC
*		mode: valor octal (p.ej.: 0666) que representa los permisos del archivo que se está
*			  creando. Solo se usa i incluimos flag O_CREAT.
*
*	STDIN_FILENO = 0, línea de comandos //<unistd.h>
*
*/
int	main(int argc, char **argv, char **envp)
{
	int	infd;
	int	outfd;
	int	i;

	if (argc == 5 && !ft_args_empty(argc, argv)) //!ft_args_empty makes sure there is no ""
	{
		infd = open(*(argv + 1), O_RDONLY);//open: abrir archivo1
		if (infd == -1)
			ft_exit_w_error("errno"); //error de open (archivo 1)
		dup2(infd, STDIN_FILENO); //Redirección salida comando 1: STDIN_FILENO (fd = 0) lo que irías a recibir por teclado, no no, recíbelo por infd
		outfd = open(*(argv + 4), O_WRONLY | O_CREAT | O_TRUNC, 0666); //open (archivo2, <flags>, <permisos>)
		if (outfd == -1)
			ft_exit_w_error("errno"); //error de open (archivo 2)
		i = 2;
		while (i < (argc - 2))
			ft_process(*(argv + i++), envp); //TODO
		dup2(outfd, STDOUT_FILENO); //Redirección salida comando 2: STDOUT_FILENO (fd = 1) lo que irías a mostrar por pantalla, no no, mételo en infd
		ft_run_command(*(argv + i), envp); //TODO
		close(infd); //close fd1 (archivo1)
		close(outfd); //close fd2 (archivo2)
	}
	else
		ft_exit_w_error("syntax: ./pipex infile cmd1 cmd2 outfile\n");
	return (EXIT_SUCCESS);
}
