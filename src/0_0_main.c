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
	// data->vars = NULL;
}

void	ft_free_prompt(t_prompt *data)
{
    t_vars *tmp;
    int i;

    i = 0;
    free(data->input);
    free(data->prompt);
    free(data->dict_quotes);
    ft_free_char(data->total_substr_input, data->nb_of_substr);
    free(data->arr_index_pipes);
    while (data->vars != NULL) {
        tmp = data->vars->next;
        free(data->vars->name);
        free(data->vars->val);
        free(data->vars);
        data->vars = tmp;
    }
    if (data->arr_boxes != NULL) {
        while (data->arr_boxes[i] != NULL) {
            ft_free_box(data->arr_boxes[i]);
            free(data->arr_boxes[i]);
            data->arr_boxes[i] = NULL;
            i++;
        }
    }
    free(data->arr_boxes);
    ft_free_envp(data);
    free(data);
}


void	ft_free_input(t_prompt *data)
{
    free(data->input);
    data->input = NULL;
    free(data->prompt);
    data->prompt = NULL;
    free(data->dict_quotes);
    data->dict_quotes = NULL;
    ft_free_char(data->total_substr_input, data->nb_of_substr);
    data->total_substr_input = NULL;
    free(data->arr_index_pipes);
    data->arr_index_pipes = NULL;
}

/*
 *   -1: Error, back to readline
 *           get_substr: -1 : Unclosed quotes
 *           ft_gen_boxes: -1: Unclosed quotes
 */

void handle_eof()
{
    if (isatty(STDIN_FILENO)) // Modo interactivo
    {
        write(STDOUT_FILENO, "exit\n", 5);
        exit(0);
    }
}
int	ft_begin(t_prompt *data)
{
	ft_init_input(data);
	if (!(data->prompt = ft_put_name_system(data)))
		free(data->prompt);
	if (!(data->input = readline(data->prompt)))
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
	t_prompt *data;
	(void)argv;

	if (argc != 1)
		perror("Error: No arguments are allowed.\n");
	if (!(data = ft_init_data(envp)))
		perror("Error: Memory allocation failed.\n");
	ft_print_welcome();
	rl_initialize();
	using_history();
	ft_signal_handler();
	while (1) {
        ft_begin(data);
    }
}
