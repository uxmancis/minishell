/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbonilla <dbonilla@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 22:15:17 by dbonilla         #+#    #+#             */
/*   Updated: 2024/05/06 22:10:02 by dbonilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void ft_begin(t_prompt *data)
{
    if (!(data->prompt= ft_put_name_system(data)))
        free(data->prompt);
       
    if(!(data->input = readline(data->prompt)))
        exit(EXIT_SUCCESS);
    if (data->input && ft_strlen(data->input) > 0)
    {
        add_history(data->input);
        rl_replace_line("", 0);
        rl_redisplay();
    }
    // Importante que se pueda vertificar con un if para de esta manera evitar problemas en un futuro
    ft_get_substr(data);
    ft_gen_boxes(data);  	
}

void handle_signal(int signal) 
{
    if (signal == SIGINT)
    {
        printf("\n");
        rl_on_new_line();
        // rl_replace_line("", 0);
        rl_redisplay();
        // received_signal = 1;
    }
    else if (signal == SIGQUIT)
    {
        printf("\nQuit (core dumped)\n");
        rl_on_new_line();
        // rl_replace_line("", 0);
        rl_redisplay();
    }
    else if (signal == SIGTERM)
    {
        printf("\nexit\n");
        exit(0);
    }
    else 
    {
        printf("\nSeñal desconocida recibida\n");
    }
}

int handle_signal_for_process(pid_t pid, int sig, const char *error_message) 
{
    (void)sig;
    if (signal(pid, handle_signal) == SIG_ERR) 
    {
        perror(error_message);
        return -1;
    }
    return 0;
}

int main(int argc, char **argv, char **envp)
{

	t_prompt *data;
    struct sigaction sa;

	(void)argv;
	(void)envp;
	if (argc != 1)
		perror("Error: No arguments are allowed.\n");
	data = ft_init_data(envp);
    sa.sa_handler = handle_signal;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;


	// else
	ft_print_welcome();
	rl_initialize();
	using_history();
    if (sigaction(SIGINT, &sa, NULL) == -1 ||
        sigaction(SIGQUIT, &sa, NULL) == -1 ||
        sigaction(SIGTSTP, &sa, NULL) == -1) 
    {
        perror("Error al establecer el manejador de señales");
        return -1;
    }
	while (1)
		ft_begin(data);

}
