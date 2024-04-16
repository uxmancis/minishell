/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uxmancis <uxmancis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 10:37:02 by uxmancis          #+#    #+#             */
/*   Updated: 2024/04/16 20:30:17 by uxmancis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define DEF_COLOR "\033[0;39m"
# define GRAY "\033[0;90m"
# define RED "\033[0;31m"
# define GREEN "\033[0;92m"
# define YELLOW "\033[0;93m"
# define BLUE "\033[0;94m"
# define MAGENTA "\033[0;95m"
# define CYAN "\033[0;96m"
# define WHITE "\033[0;97m"
# define RESET_COLOR   "\033[0m"


# include <unistd.h> //write
# include <readline/readline.h> //readline - Además, al compilar, añadir flag -lreadline. Ex.: gcc -lreadline -o minishell minishell.c
# include <readline/history.h>
# include <stdlib.h> //exit

/*Stores info about the received prompt*/
typedef struct s_prompt
{
    int are_there_pipes; //-1: no pipe, >0:number of pipes
}   t_prompt;

//minishell.c
void ft_begin(int argc, char **argv, char **env);

//analyse_input.c
int ft_quotes(char *input, char **dictionary);
int ft_quotes_2(char *input, char **dictionary, int i);
int ft_quotes_3(char *input, char **dictionary, int i);
void init_instructions(char *input, t_prompt *prompt);

void ft_analyse_input(char *input, t_prompt *prompt);

//utils.c
int	ft_putchar_fd(int c, int fd);
int	ft_putstr_fd(char *str, int fd);
void	ft_print_welcome(void);
size_t	ft_strlen(char *str);
//void	ft_puterror_exit(char *str);
void ft_puterror(char *str);
int	ft_strncmp(const char *s1, const char *s2, size_t n);

#endif