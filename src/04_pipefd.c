/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   04_pipefd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbonilla <dbonilla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 03:12:56 by dbonilla          #+#    #+#             */
/*   Updated: 2024/06/22 21:17:06 by dbonilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "../inc/minishell.h"

// // int create_pipe(t_box *box)
// // {
// //     int i;
// //     i = 0;
// //     // Crea los pipes necesarios

// //     while (i < box->nb_pipes)
// //     {
// //         printf(WHITE"       nb_pipes ✅"RESET_COLOR BLUE" [%d] \n", box->nb_pipes);
// 	//         if (pipe(box->pipefd + 2 * i) == -1)
// 	//         {
// 	//             perror("Could not create pipe");
// 	//             return (-1);
// 	//         }
// 	//
// 	// Imprime el descriptor de archivo de lectura y escritura para cada pipe
// 	//         printf(BLUE"Pipe [%d] -> "RESET_COLOR"READ[0]: [%d],WRITE[1]: [%d]\n",
// //            i, box->pipefd[i + 2 * i], box->pipefd[i + 1]);
// //         i++;
// //     }
// //     printf(WHITE"Number of pipes created: "RESET_COLOR BLUE"[%d]\n",box->nb_pipes);
// 	//     return (0);
// 	// }

// 	int create_pipe(t_box *box, int box_id)
// 	{
// 		int i;
// 		char c;

// 		(void)box_id;
// 		i = 0;
// 		printf("NUMBER OF PIPES: %i\n\n", box->nb_pipes);
// 		while (i < box->nb_pipes)
// 		{
// 			box->pipefd[i] = malloc(2 * sizeof(int));
// 			if (box->pipefd[i] == NULL)
// 			{
// 				perror("malloc");
// 				return (-1);
// 			}
// 			if (pipe(box->pipefd[i]) == -1)
// 			{
// 				perror("pipe");
// 				return (-1);
// 			}
// 			printf(BLUE "PIPEFD[%d] -> READ[0]: [%d], WRITE[1]: [%d]\n" RESET_COLOR,
// 				   i, box->pipefd[i][0], box->pipefd[i][1]);
// 			// TESTING EDER
// 			printf("\n\n\nPIPE FDS:\nPipe[0]= %i\nPipe[1]= %i\n\n\n",box->pipefd[i][0], box->pipefd[i][1]);
// 			//
// 			i++;
// 		}
// 		if (box->nb_pipes == 1)
// 		{
// 			write(box->pipefd[0][1], "*", 1);
// 			read(box->pipefd[0][0], &c, 1);
// 		}
// 		printf("El char es: %c\n", c);
// 		printf(WHITE "Number of pipes created: " RESET_COLOR BLUE "[%d]\n", i);
// 		return (0);
// 	}

// 	int baby_sister_for_the_childs(int input, int output, t_box *box)
// 	{
// 		(void)box;
// 		printf(BLUE "Redirecting ...\n" RESET_COLOR);
// 		printf(YELLOW "Before dup2 - Input FD <- : %d, STDIN: %d\n" RESET_COLOR,
// 			   input, STDIN_FILENO);
// 		printf(YELLOW "Before dup2 - Output FD -> : %d, STDOUT: %d\n" RESET_COLOR,
// 			   output, STDOUT_FILENO);
// 		if (output == -1)
// 			output = 1;
// 		if (input == -1)
// 			input = 0;
// 		if (input != STDIN_FILENO)
// 		{
// 			// dup2(input, STDOUT_FILENO);
// 			dup2(input, STDIN_FILENO);
// 			// perror("dup2 input_fd");
// 			close(input);
// 			// exit(EXIT_FAILURE);
// 		}
// 		if (output != STDOUT_FILENO)
// 		{
// 			// if (output != STDOUT_FILENO)
// 			// dup2(output, STDIN_FILENO);
// 			dup2(output, STDOUT_FILENO);
// 			// perror("dup2 output_fd");
// 			close(output);
// 			// exit(EXIT_FAILURE);
// 		}
// 		//}
// 		//{
// 		//}
// 		printf(GREEN "After dup2 - Input FD: %d <- STDIN: %d\n" RESET_COLOR, input,
// 			   STDIN_FILENO);
// 		printf(GREEN "After dup2 - Output FD: %d -> STDOUT: %d\n" RESET_COLOR,
// 			   output, STDOUT_FILENO);
// 		printf(GREEN "Redirection successful!\n" RESET_COLOR);
// 		return (0);
// 	}
