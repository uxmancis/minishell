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

void	ft_init_input(t_prompt *data)
{
	data->input = NULL;
	data->prompt = NULL;
	data->dict_quotes = NULL;
	data->nb_of_pipes = 0;
	data->nb_of_substr = 0;
	data->line_infd = 0;
	data->line_outfd = 0;
	data->total_substr_input = NULL;
	data->arr_index_pipes = NULL;
}

void	ft_free_input(t_prompt *data)
{
	if (data->input)
		free(data->input);
	if (data->prompt)
		free(data->prompt);
	if (data->dict_quotes)
		free(data->dict_quotes);
	if (data->total_substr_input)
		ft_free_char(data->total_substr_input, data->nb_of_substr);
	if (data->arr_index_pipes)
		free(data->arr_index_pipes);
}

/*
*   -1: Error, back to readline
*           get_substr: -1 : Unclosed quotes
*           ft_gen_boxes: -1: Unclosed quotes
*/
int	ft_begin(t_prompt *data)
{
	ft_init_input(data);
	if (!(data->prompt = ft_put_name_system(data)))
		free(data->prompt);
	if (!(data->input = readline(data->prompt)))
		exit(EXIT_SUCCESS);
	if (data->input && ft_strlen(data->input) > 0)
	{
		add_history(data->input);
		rl_replace_line("", 0);
		rl_redisplay();
	}
	if (ft_get_substr(data) == -1 || ft_gen_boxes(data) == -1)
	{
		ft_free_input(data);
		return (-1);
	}
	ft_free_input(data);
	return (0);
}

void	handle_signal(int signal)
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
		printf("\nSeñal desconocida recibida\n");
}

int	handle_signal_for_process(pid_t pid, int sig, const char *error_message)
{
	(void)sig;
	if (signal(pid, handle_signal) == SIG_ERR)
	{
		perror(error_message);
		return (-1);
	}
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	t_prompt			*data;
	struct sigaction	sa;

	(void)argv;
	if (argc != 1)
		perror("Error: No arguments are allowed.\n");
	data = ft_init_data(envp);
	sa.sa_handler = handle_signal;
	//sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	ft_print_welcome();
	rl_initialize();
	using_history();
	if (sigaction(SIGINT, &sa, NULL) == -1
		|| sigaction(SIGQUIT, &sa, NULL) == -1
		|| sigaction(SIGTSTP, &sa, NULL) == -1) 
	{
		perror("Error al establecer el manejador de señales");
		return (-1);
	}
	while (1)
		ft_begin(data);
	return (0);
}
