/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+
	+:+     */
/*   By: dbonilla <dbonilla@student.42urduliz.co    +#+  +:+
	+#+        */
/*                                                +#+#+#+#+#+
	+#+           */
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
 * 
 * if (isatty(STDIN_FILENO)) // Modo interactivo
 */
void	handle_eof(void)
{
	if (isatty(STDIN_FILENO))
	{
		write(STDOUT_FILENO, "exit\n", 5);
		exit(0);
	}
}

int	ft_begin(t_prompt *data)
{
	ft_init_input(data);
	data->prompt = ft_put_name_system(data);
	if (!data->prompt)
		free(data->prompt);
	data->input = readline(data->prompt);
	if (!data->input)
		handle_eof();
	if (data->input && ft_strlen(data->input) > 0)
	{
		add_history(data->input);
		rl_replace_line(" ", 0);
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

int	main(int argc, char **argv, char **envp)
{
	t_prompt	*data;

	(void)argv;
	data = ft_init_data(envp);
	if (argc != 1)
		perror("Error: No arguments are allowed.\n");
	if (!data)
		perror("Error: Memory allocation failed.\n");
	ft_print_welcome();
	rl_initialize();
	using_history();
	ft_signal_handler();
	while (1)
		ft_begin(data);
	return (0);
}
