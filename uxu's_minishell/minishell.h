/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uxmancis <uxmancis@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 10:37:02 by uxmancis          #+#    #+#             */
/*   Updated: 2024/04/29 23:35:59 by uxmancis         ###   ########.fr       */
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
#define AQUAMARINE "\033[0;96m"


# include <unistd.h> //write
# include <readline/readline.h> //readline - Además, al compilar, añadir flag -lreadline. Ex.: gcc -lreadline -o minishell minishell.c
# include <readline/history.h>
# include <stdlib.h> //exit EXIT FAILURE
# include <stdio.h> //printf

typedef struct s_box
{
    char    *input_substr;
    int     id_substr;
}   t_box;

/*Stores info about the received prompt*/
typedef struct s_prompt
{
    char *input; //Input virgen
    char **total_substr_input; //Input dividido en n cadenas (en base a pipes fuera de comillas)
    int *dict_quotes; //'0': outside of quotes, '1' inside single quotes, '2' inside double quotes
    int nb_of_pipes; //-1: pipe wrong position, 0: no pipe, >0: number of pipes
    int *arr_index_pipes; //index of pipes
}   t_prompt;

//minishell.c
void ft_begin(int argc, char **argv, char **env);
void ft_get_substr(t_prompt *prompt);

//input_pipe.c
void ft_where_r_pipes(t_prompt **prompt); //función Índice - Principal
int ft_is_pipe(t_prompt **t_prompt); //¿Hay pipes en posición válida? Y/N/Cuántos
void set_index_pipe(t_prompt **prompt); //¿En qué posición están estos pipes? Input: dictionary. Output: arr_index_pipes

//input_quotes.c
int ft_quotes(t_prompt **prompt);
int ft_quotes_2(t_prompt **prompt, int i);
int ft_quotes_3(t_prompt **prompt, int i);
int ft_where_r_u (int index, int *dictionary);

//input_split.c
int ft_split_input(t_prompt **prompt);
char *ft_split_from_to(int start, int end, char *src_input);
//char	**ft_split_input(t_prompt prompt);

//99_utils.c
int ft_isspace(int c);
int	ft_putchar_fd(int c, int fd);
int	ft_putstr_fd(char *str, int fd);
void	ft_print_welcome(void);
size_t	ft_strlen(char *str);
//int	ft_atoi(const char *str);
//void	ft_puterror_exit(char *str);
void ft_puterror_exit(char *str);
void ft_puterror(char *str);
int	ft_strncmp(const char *s1, const char *s2, size_t n);

#endif