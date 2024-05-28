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


static void ft_begin(t_prompt *data)
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

int main(int argc, char **argv, char **envp)
{

	t_prompt *data;

	(void)argv;
	(void)envp;
	if (argc != 1)
		perror("Error: No arguments are allowed.\n");
	data = ft_init_data(envp);

	// else
	ft_print_welcome();
	rl_initialize();
	using_history();
	while (1)
		ft_begin(data);

}
