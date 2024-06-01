/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   04_generate_forks.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uxmancis <uxmancis@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 17:42:33 by dbonilla          #+#    #+#             */
/*   Updated: 2024/06/01 16:42:34 by uxmancis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"



                                                                        /*          
                                                                                    Start
                                                                                    |
                                                                                    V
                                                                            Create Pipes [0]     Create Pipes [1]     ... Create Pipes [n-1]
                                                                                    |                     |                     |
                                                                                    V                     V                     V
                                                                                Pipe 0               Pipe 1               ... Pipe n-1
                                                                            ------------         ------------         ... ------lo------
                                                                            | read | write |     | read | write |     ... | read | write |
                                                                            |  3   |   4   |     |  5   |   6   |     ... |   ...        |
                                                                            ------------         ------------         ... ------------
                                                                                    |                     |                     |
                                                                                    V                     V                     V
                                                                            Fork Child 0         Fork Child 1          ... Fork Child n
                                                                                    |                     |                     |
                                                                        Is Child? No --->    Is Child? No --->    ... Is Child? No --->
                                                                                    |                     |                     |
                                                                                Yes                   Yes                   Yes
                                                                                    |                     |                     |
                                                                        Redirect stdin to       Redirect stdin to      ... Redirect stdin to
                                                                        previous pipe's read    pipe 0's read end      pipe n-2's read end
                                                                        end if i != 0           (fd 3)                 (fd ...)
                                                                        (fd ...)                |                     |
                                                                                    |                     |                     |
                                                                        Redirect stdout to      Redirect stdout to     Redirect stdout to
                                                                        current pipe's write    pipe 1's write end     pipe n-1's write end
                                                                        end if i != NUM_PIPES   (fd 6)                 (fd ...)
                                                                        (fd ...)                |                     |
                                                                                    |                     |                     |
                                                                            Close all pipes       Close all pipes     ... Close all pipes
                                                                                    |                     |                     |
                                                                                Execute              Execute             ... Execute
                                                                                "command0"           "command1"           "commandn"
                                                                                using execve         using execve         using execve
                                                                                    |                     |                     |
                                                                            (if execve fails)       (if execve fails)     ... (if execve fails)
                                                                            Print error and         Print error and       Print error and
                                                                            exit                   exit                   exit
                                                                                    |                     |                     |
                                                                                Parent                 Parent               Parent
                                                                                Closes all             Closes all           Closes all
                                                                                pipes                  pipes                pipes
                                                                                    |                     |                     |
                                                                                Wait for               Wait for             Wait for
                                                                                child to finish        child to finish      child to finish
                                                                                    |<-------------------|<-------------------|<-------------------
                                                                                    |
                                                                                Yes
                                                                                    |
                                                                                No
                                                                                    |
                                                                                    V
                                                                                End/ */


                                                                                /*-----------------------
                                                                                |     PIPEFD[0]       |
                                                                                | [0] (read) | [1] (write) |
                                                                                -----------------------
                                                                                |     PIPEFD[1]       |
                                                                                | [0] (read) | [1] (write) |
                                                                                ----------------------- */




 /*       PIPE 0               PIPE 1               PIPE 2
      ------------         ------------         ------------
     | read | write |     | read | write |     | read | write |
     |  3   |   4   |     |  3   |   4   |     |  3   |   4   |
      ------------         ------------         ------------
           ^                     ^                     ^
           |                     |                     |
     ------------         ------------         ------------
    |   Child 0   |       |   Child 1   |       |   Child 2   |       |   Child 3   |
    |  stdout (4) |       | stdin (3)   |       | stdin (3)   |       | stdin (3)   |
    |             |------>| stdout (4)  |------>| stdout (4)  |------>| stdout      |
    --------------         --------------        --------------        --------------
    |   Parent    |       |   Parent    |       |   Parent    |       |   Parent    |
    |  stdin (3)  |       | stdin (3)   |       | stdin (3)   |       | stdin (3)   |
    |             |------>| stdout (4)  |------>| stdout (4)  |------>| stdout      |
    --------------         --------------        --------------        --------------*/
int create_pipes(t_cmd *cmd_data)
{
    int nb_cmds = cmd_data->nb_cmds;
    int i = 0;
    while ( i < nb_cmds ) 
    {
        cmd_data->pipefd[i] = malloc(2 * sizeof(int));
        if (cmd_data->pipefd[i] == NULL) 
        {
            perror("malloc");
            return -1;
        }
        if (pipe(cmd_data->pipefd[i]) == -1) {
            perror("pipe");
            return -1;
        }
        printf(BLUE"        pipefd ->  OUT_INDEX '<' | [%d] "RESET_COLOR GREEN" WRITE[1]: " " [%d] \n", i, cmd_data->pipefd[i][0]);
        printf(BLUE"        pipefd ->  IN_INDEX '>' | [%d] "RESET_COLOR GREEN" READ[0]:  " " [%d] \n", i, cmd_data->pipefd[i][1]);
        printf(WHITE"          nb_pipefd ✅"RESET_COLOR BLUE" [%d] \n", cmd_data->nb_cmds);
        i++;
        // nb_cmds--;
    }

    return 0;
}


int close_fdin_fdout(t_cmd *cmd_data, int index_child)
{
    (void)index_child;
    printf(RED "Closing... fd_in: [%d]\n" RESET_COLOR, cmd_data->fd_in);
    if (cmd_data->fd_in != -1) {
        close(cmd_data->fd_in);
        cmd_data->fd_in = -1;
    }
    printf(RED "Closing... fd_out: [%d]\n" RESET_COLOR, cmd_data->fd_out);
    if (cmd_data->fd_out != -1) {
        close(cmd_data->fd_out);
        cmd_data->fd_out = -1;
    }
    return (0);
}

int close_pipefd(t_cmd *cmd_data) 
{
    int i = 0;
    int nb_cmds = cmd_data->nb_cmds ;

    while (i < nb_cmds) {
        if (cmd_data->pipefd[i]) {
            printf(BLUE "Closing pipefd [%d] WRITE[1]: [%d] READ[0]: [%d]\n" RESET_COLOR, i, cmd_data->pipefd[i][1], cmd_data->pipefd[i][0]);
            close(cmd_data->pipefd[i][0]);
            close(cmd_data->pipefd[i][1]);
            free(cmd_data->pipefd[i]);
        }
        i++;
    }
    return (0);
}


int  baby_sister_for_the_childs(int input, int output, t_cmd *cmd_data)
{
    (void) cmd_data;
    printf(BLUE "Redirecting ...\n" RESET_COLOR);
    printf(YELLOW "Before dup2 - Input FD: %d, STDIN: %d\n" RESET_COLOR, input, STDIN_FILENO);
    printf(YELLOW "Before dup2 - Output FD: %d, STDOUT: %d\n" RESET_COLOR, output, STDOUT_FILENO);

    if (dup2(output, STDOUT_FILENO) == -1) 
    {
        perror(RED "dup2 output" RESET_COLOR);
        // exit_error(1, d);
        // exit_error(1);
    }
    printf(GREEN "After dup2 - Output FD: %d -> STDOUT: %d\n" RESET_COLOR, output, STDOUT_FILENO);
    if (dup2(input, STDIN_FILENO) =<= -1) 
    {
        perror(RED "dup2 input" RESET_COLOR);
        // exit_error(1, d);
        // exit_error(1);
    }
    printf(GREEN "After dup2 - Input FD: %d -> STDIN: %d\n" RESET_COLOR, input, STDIN_FILENO);


    printf(GREEN "Redirection successful!\n" RESET_COLOR);
    return (0);
}

int childs(t_cmd *cmd_data, int index_child, t_box **box, t_prompt **data)
{
    printf(RESET_COLOR"\n\nchilds\n");
    // printf("                                                    I = [%d]\n", index_child);
    // printf(BLUE"        pipefd ->  OUT_INDEX '<' | [%d] "RESET_COLOR GREEN" WRITE[1]: " " [%d] \n", index_child, cmd_data->pipefd[index_child][0]);
    // printf(BLUE"        pipefd ->  IN_INDEX '>' | [%d] "RESET_COLOR GREEN" READ[0]:  " " [%d] \n", index_child, cmd_data->pipefd[index_child][1]);                           
    // printf(BLUE "       handle_child | "  RED RESET_COLOR MAGENTA "The PID of the parent process is: "  RED "%d\n" , getppid());
    // printf(BLUE "       handle_child | "  GREEN RESET_COLOR MAGENTA "The PID of the child is: "  GREEN "%d\n" , getpid());                  
    // printf(YELLOW"          box->pipefd[%d][1]: %d\n"RESET_COLOR, index_child, cmd_data->pipefd[index_child][1]);
    if (index_child == 0) {
        baby_sister_for_the_childs(cmd_data->fd_in, cmd_data->pipefd[index_child][1], cmd_data);
    } else if (index_child == cmd_data->nb_cmds) {
        baby_sister_for_the_childs(cmd_data->pipefd[index_child - 1][0], cmd_data->fd_out, cmd_data);
    } else {
        baby_sister_for_the_childs(cmd_data->pipefd[index_child - 1][0], cmd_data->pipefd[index_child][1], cmd_data);
    }
    close_fdin_fdout(cmd_data, index_child);
    which_cmd(box, data);


    // if (cmd_data->cmd_options == NULL || cmd_data->cmd_path == NULL) {
    //     exit(EXIT_FAILURE);
    // }

    // if (execve(cmd_data->cmd_path, cmd_data->cmd_options, cmd_data->envp) == -1) {
    //     perror("execve");
    //     exit(EXIT_FAILURE);
    // }

    return (0);
}

// char	*get_cmd(t_cmd *cmd_data, t_prompt *data)
// {
// 	// char	**env_paths;
// 	// char	*cmd_path;
//     // (void)cmd;
//     (void)data;
// 	// if (access(cmd_data->command[0], F_OK | X_OK) == 0)
// 		// return (ft_strdup(cmd_data->command[0]));
// 	// cmd_data->envp = ft_getenv_local(data);
// 	// if (!env_paths)
// 	// 	return (NULL);
// 	// cmd_path = ft_getenv_local(cmd, env_paths);
// 	// if (!cmd_path)
// 		// msg("command not found", ": ", data->av[data->child + 2], 1);
// 	// free_strs(NULL, env_paths);
// 	// return (cmd_path);
//     return(0);
// }

int create_child_process(t_cmd *cmd_data, t_prompt *data, t_box **box)
{
    int exit_code;
        (void)exit_code;
        (void)data;

    int nb_cmd = cmd_data->nb_cmds;
    int index_child = 0;
    while (index_child < nb_cmd)
    {
        // cmd_data->cmd_path = get_cmd(cmd_data, data);

        printf(GREEN "       Parent | "  RED RESET_COLOR MAGENTA "The PID of the parent process is: "  RESET_COLOR GRAY "  [%d]  \n" , getppid());
    
        pid_t pid = fork();
        if (pid == -1)
        {
            perror("fork");
            return -1;
        }
        if (!cmd_data->pids)
	    {
		    perror("Error Malloc PIDS allocation");
		    free(cmd_data->pids);
	    }
        if (pid == 0) 
        {
            printf(RED"                     Index_child |  "RESET_COLOR  WHITE" [%d] \n", nb_cmd);   
            printf(GREEN "      Parent | "  RED RESET_COLOR MAGENTA "The PID of the parent process is: "  RESET_COLOR WHITE "  [%d]  \n" , getppid());
            printf(GREEN"       create_child_process | "  RED RESET_COLOR MAGENTA "The PID of the chil process is: "  RED RESET_COLOR WHITE "  [%d]  \n" , getpid());           
            printf(BLUE "       handle_input_infile | "  RED RESET_COLOR MAGENTA"data->infd: "  WHITE " [%d] \n" , cmd_data->fd_in);
	        printf(BLUE "       handle_input_outfile | "  RED RESET_COLOR MAGENTA"data->outfd: "  WHITE " [%d] \n" , cmd_data->fd_out);
            printf(RED"         I =  "RESET_COLOR WHITE"[%d]", index_child);
            printf(BLUE"        pipefd ->  OUT_INDEX '<' | [%d] "RESET_COLOR GREEN" WRITE[1]: " " [%d] \n", index_child, cmd_data->pipefd[index_child][0]);
            printf(BLUE"        pipefd ->  IN_INDEX '>' | [%d] "RESET_COLOR GREEN" READ[0]:  " " [%d] \n", index_child, cmd_data->pipefd[index_child][1]);
            printf(WHITE"          nb_pipefd ✅"RESET_COLOR BLUE" [%d] \n", index_child);
            // sleep (1);
            childs(cmd_data, index_child, box, &data);
            cmd_data->pids[index_child] = pid;

            
            // close_fdin_fdout(cmd_data, index_child);
           
            // printf("I = [%d]\n", index_child);
            // printf(BLUE"        pipefd ->  OUT_INDEX '<' | [%d] "RESET_COLOR GREEN" WRITE[1]: " " [%d] \n", index_child, cmd_data->pipefd[index_child][0]);
            // printf(BLUE"        pipefd ->  IN_INDEX '>' | [%d] "RESET_COLOR GREEN" READ[0]:  " " [%d] \n", index_child, cmd_data->pipefd[index_child][1]);                           
            // printf(BLUE "       handle_child | "  RED RESET_COLOR MAGENTA "The PID of the parent process is: "  RED "%d\n" , getppid());
            // printf(BLUE "       handle_child | "  GREEN RESET_COLOR MAGENTA "The PID of the child is: "  GREEN "%d\n" , getpid());                  
            // printf(YELLOW"          box->pipefd[%d][1]: %d\n"RESET_COLOR, index_child, cmd_data->pipefd[index_child][1]);
            // exit(0);
        } 

                // handle_parent_process(cmd_data);
                // close(cmd_data->pipefd[index_child-1][0]);
                // printf(GRAY" close_pipefd ->> [%d]",cmd_data->pipefd[index_child-1][0]);
                // close(cmd_data->pipefd[index_child-1][1]);
                // printf(GRAY" close_pipefd ->> [%d]",cmd_data->pipefd[index_child-1][1]);
              // Llamar a handle_signal con SIGTSTP  // Enviar SIGTSTP
            //   signal(SIGTSTP, handle_signal);
          
         // Llamar a handle_signal con SIGQUIT  // Enviar SIGQUIT
        index_child++;
        nb_cmd--;
    }
    exit_code = handle_parent_process(cmd_data, index_child);
    // write(1, "End of create_child_process\n", 28);
    return (0);
}

// // Function to handle the parent process
int handle_parent_process(t_cmd *cmd_data, int index_childd) 
{
    (void)index_childd;
    int status;
    pid_t wpid;
    int nb_cmd = cmd_data->nb_cmds;
    int index_child = 0;
    int exit_code = 1;

    printf (WHITE"\n\n------------------------------------------\n\n"RESET_COLOR);
    close_fdin_fdout(cmd_data, index_childd);
    while (index_child >= nb_cmd) 
    {
        wpid = waitpid(cmd_data->pids[index_child], &status, 0);
        if (wpid == cmd_data->pids[index_child]) {
            if (WIFEXITED(status)) {
                exit_code = WEXITSTATUS(status);
            }
        }
        index_child++;
        nb_cmd--;

        printf (RED"\n\nHOLA AQUI ESTAOS EN EL PROCESO PADRE"RESET_COLOR);
    // free(cmd_data->pids[index_child]);
    }
    close_pipefd(cmd_data);
    free(cmd_data->pids);
    return (exit_code);
}

