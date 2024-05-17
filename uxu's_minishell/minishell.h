/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uxmancis <uxmancis@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 10:37:02 by uxmancis          #+#    #+#             */
/*   Updated: 2024/05/17 17:10:52 by uxmancis         ###   ########.fr       */
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
# define GRASS "\033[0;32m"


# include <unistd.h> //write
# include <readline/readline.h> //readline - Además, al compilar, añadir flag -lreadline. Ex.: gcc -lreadline -o minishell minishell.c
# include <readline/history.h>
# include <stdlib.h> //exit EXIT FAILURE
# include <stdio.h> //printf

/*Stores info about the received prompt*/
typedef struct s_prompt
{
    char *input; //Input virgen
    int *dict_quotes; //'0': outside of quotes, '1' inside single quotes, '2' inside double quotes
    int nb_of_pipes; //-1: pipe wrong position, 0: no pipe, >0: number of pipes
    int *arr_index_pipes; //index of pipes
    int nb_of_substr;
    char **total_substr_input; //Input dividido en n cadenas (en base a pipes fuera de comillas)
}   t_prompt;

typedef struct s_box
{   char    *input_substr; //Substr virgen
    //int     id_substr;
    //pdte. dict_quotes
    int     *dict_quotes;
    int     nb_of_redir; //number of redirecciones
    int     **dict_red_index_type; //[0]: index, [1]: type

    //About redirecciones:
    int     nb_of_heredocs;
    char    **words_hrdc; //delimiter words
    int     is_infile; //YES[1]/NO[0] is there any infile '<' along dict_red_index_type
    int     nb_of_infile; //How many infile
    char    **words_infile; //infile filenames
    int     is_outfile_append; //YES[1]/NO[0] is there any outfile_append '>>' along dict_red_index_type
    int     nb_of_outfile_append; //How many outfile append
    char    **words_outfile_append; //outfile filenames
    int     is_outfile_strong; //YES[1]/NO[0] is there any outfile_append '>' along dict_red_index_type
    int     nb_of_outfile_strong; //How many outfile strong
    char    **words_outfile_strong; //outfile filenames

    //About command, flags and argumentos:

}   t_box;

typedef enum e_red_type
{
    NO_REDIRECTION, //0
    OUTFILE_APPEND, //1: >>
    OUTFILE_STRONG, //2: >
    INFILE, //3: <
    HEREDOC //4: <<
}   t_red_type;

//00_minishell.c
void ft_begin(int argc, char **argv, char **env);
void ft_get_substr(t_prompt *prompt);

//01_input_pipe.c
void ft_where_r_pipes(t_prompt **prompt); //función Índice - Principal
int ft_is_pipe(t_prompt **t_prompt); //¿Hay pipes en posición válida? Y/N/Cuántos
void set_index_pipe(t_prompt **prompt); //¿En qué posición están estos pipes? Input: dictionary. Output: arr_index_pipes

//01_input_quotes.c
//int ft_quotes(t_prompt **prompt);
int ft_quotes(char *input, int **dict_quotes);
//int ft_quotes_2(t_prompt **prompt, int i);
int ft_quotes_2(char *input, int **dict_quotes, int i);
//int ft_quotes_3(t_prompt **prompt, int i);
int ft_quotes_3(char *input, int **dict_quotes, int i);
int ft_where_r_u (int index, int *dictionary);

//01_input_split.c
void ft_split_input(t_prompt **prompt);
char *ft_split_from_to(int start, int end, char *src_input);
//char	**ft_split_input(t_prompt prompt);

//02_boxes.c
void ft_gen_boxes(t_prompt *prompt);
void ft_boxes_init(t_prompt *prompt, int substr_id);
void get_dict_quotes(t_box *box);
void generate_substr(t_prompt *prompt, int substr_id, t_box *box);
void ft_strcpy (char *str_src, char **str_dst);

//02_boxes_redir.c
int get_redirections(t_box *box);
void ft_fill_red_info(t_box **box);
void set_red_index_type(t_box **box); 
int set_red_greater_than(t_box **box, int *i, int index_of_arr);
int set_red_less_than(t_box **box, int *i, int index_of_arr);
int ft_get_numof_redir(t_box *box);
char *ft_enum_to_str(int enumerator);

//02_boxes_rest.c
void get_rest (t_box *box);
int ft_get_numof_heredocs(t_box **box);
int ft_confirmed_end(t_box **box);
void get_arr_heredoc(int **arr_ind_heredoc, t_box **box);
int are_all_delimiters(int *arr_word_yes_no, t_box **box, t_red_type red_type);

//02_boxes_hrdc_1.c
void ft_heredocs(t_box **box, enum e_red_type);
int ft_get_numof_heredocs(t_box **box);
void ft_check_delimiter(t_box **box);
void get_arr_heredoc(int **arr_ind_heredoc, t_box **box);
void get_end_arr(int **arr_end, t_box **box, int *arr_ind_heredoc);

//02_boxes_hrdc_2.c
int get_ind (int hrdc_ind_in_substr, t_box **box);
void get_delimiters(int *arr_ind_heredoc, t_box **box);
void get_word(int start, int end,t_box **box, int heredoc_nb);

//02_boxes_red_utils.c
int get_nb_of_red_type(t_box **box, t_red_type red_type);
void get_specif_index_red(int **arr_ind_red_type, t_box **box, t_red_type red_type);
void is_word_red(int **arr_word_yes_no, t_box **box, int *arr_ind_red_type, t_red_type red_type);
void get_word_mgmt(int *arr_ind_red_type, t_box **box, t_red_type red_type);
void ft_check_first_word(t_box **box, t_red_type red_type);

//02_boxes_utils_nav.c
int has_end_last_check(int start, int end, t_box **box);
int is_last_redir(t_box **box, int index_current_heredoc);
int has_end_word(int index_hrdc_in_substr, t_box **box, int red_nb_x);

//02_boxes_4_infile.c
int ft_infiles(t_box **box, t_red_type red_type);
int is_infile(t_box **box);
int ft_get_numof_infile(t_box **box);

//02_boxes_5_outfile_append.c
int ft_outfile_append(t_box **box, t_red_type red_type);
int is_red_type(t_box **box, t_red_type red_type); //generic para todos (NEW)
int ft_get_numof_red_type(t_box **box, t_red_type red_type); //generic para todos (NEW)

//02_boxes_5_outfile_strong.c
int ft_outfile_strong(t_box **box, t_red_type red_type);

//02_boxes_word_utils_hrdc.c
void get_word_hrdc_1(t_box **box, int *arr_ind_red_type);
void get_word_hrdc_2(int start, int end, t_box **box, int heredoc_nb);

//02_boxes_word_utils_infile.c
void get_word_infile_1(t_box **box, int *arr_ind_red_type);
void get_word_infile_2(int start, int end, t_box **box, int red_type_nb_x);

//02_boxes_word_utils_outf_app.c
void get_word_outf_app_1(t_box **box, int *arr_ind_red_type);
void get_word_outf_app_2(int start, int end, t_box **box, int red_type_nb_x);

//02_boxes_word_utils_outf_str.c
void get_word_outf_str_1(t_box **box, int *arr_ind_red_type);
void get_word_outf_str_2(int start, int end, t_box **box, int red_type_nb_x);



//98_exec_david.c
void	exec_heredoc(char *delimiter);
int has_end_word(int index_hrdc_in_substr, t_box **box, int red_nb_x);

//99_utils.
int ft_isspace(int c);
int	ft_putchar_fd(int c, int fd);
int	ft_putstr_fd(char *str, int fd);
void	ft_print_welcome(void);
size_t	ft_strlen(const char *str);
//int	ft_atoi(const char *str);
//void	ft_puterror_exit(char *str);
void ft_puterror_exit(char *str);
void ft_puterror(char *str);
int	ft_strncmp(const char *s1, const char *s2, size_t n);

#endif