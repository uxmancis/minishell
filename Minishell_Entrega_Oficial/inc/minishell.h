/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbonilla <dbonilla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 10:37:02 by uxmancis          #+#    #+#             */
/*   Updated: 2024/05/19 16:48:25 by dbonilla         ###   ########.fr       */
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

// # include "../libft/libft.h"
// # include <unistd.h> //write
// # include <readline/readline.h> //readline - Además, al compilar, añadir flag -lreadline. Ex.: gcc -lreadline -o minishell minishell.c
// # include <readline/history.h>
// # include <stdlib.h> //exit EXIT FAILURE
// # include <stdio.h> //printf


/* EXAMPLE OF A STRUCTURE */
#include "../Libft/inc/libft.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <dirent.h>
#include <signal.h>
#include <termios.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stddef.h>


typedef enum   e_red_type   t_red_type;
typedef struct s_prompt     t_prompt;
typedef struct s_box        t_box;
typedef struct s_vars       t_vars;

typedef struct s_x_y_rest_info
{
    int index_x;
    int index_y;
}   t_x_y_rest_info;

enum e_red_type
{
    NO_REDIRECTION, //0
    OUTFILE_APPEND, //1: >>
    OUTFILE_STRONG, //2: >
    INFILE, //3: <
    HEREDOC //4: <<
};

struct s_box
{   char    *input_substr; //Substr virgen
    //int     id_substr;
    //pdte. dict_quotes
    int     infd;
    int     outfd;
    // int		is_infd;
	// int		is_outfd;
    int     pid;
    int     pipefd[2];
    int     *dict_quotes;
    int     nb_of_redir; //number of redirecciones
    int   **dict_red_index_type; //[0]: index, [1]: type

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
    char    *what_to_take;
    int     nb_of_words_rest;
    int    *index_beginning_words_rest;
    char    **rest_info_potential_cmd;

    //Others, for convenience:
    pid_t tmp_pid;
    char *tmp_pid_str;

    t_prompt *prompt;
};                        

/* STR*/
struct s_vars
{
	char			*name;
	char			*val;
	struct s_vars	*next;
	int				is_exp;
};

/*Stores info about the received prompt*/
struct s_prompt
{
    char *input; //Input virgen
    char *prompt; // Prompt del sistema
    int *dict_quotes; //'0': outside of quotes, '1' inside single quotes, '2' inside double quotes
    int nb_of_pipes; //-1: pipe wrong position, 0: no pipe, >0: number of pipes
    int nb_of_substr;
    int line_infd;
    int line_outfd;
    char **total_substr_input; //Input dividido en n cadenas (en base a pipes fuera de comillas)
    int *arr_index_pipes; //index of pipes
    t_vars *vars;
    t_box *box;
} ;



//minishell.c
// void ft_begin(t_prompt *data);

//00_minishell.c
// void ft_begin(int argc, char **argv, char **env);
void ft_get_substr(t_prompt *prompt);

//01_input_pipe.c
void ft_where_r_pipes(t_prompt **prompt); //función Índice - Principal
int ft_is_pipe(t_prompt **t_prompt); //¿Hay pipes en posición válida? Y/N/Cuántos
void set_index_pipe(t_prompt **prompt); //¿En qué posición están estos pipes? Input: dictionary. Output: arr_index_pipes

//01_input_quotes.c
// int ft_quotes(t_prompt **prompt);
int ft_quotes(char *input, int **dict_quotes);
// int ft_quotes_2(t_prompt **prompt, int i);
int ft_quotes_2(char *input, int **dict_quotes, int i);
// int ft_quotes_3(t_prompt **prompt, int i);
int ft_quotes_3(char *input, int **dict_quotes, int i);
// int ft_where_r_u (int index, int *dictionary);

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
void get_rest (t_box *box, t_prompt **prompt);
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
void get_word_red(int **arr_word_yes_no, t_box **box, int *arr_ind_red_type, t_red_type red_type);
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

//02_boxes_6_cmd_1.c
void ft_get_cmd_args(t_box **box, t_prompt **prompt);
void   ft_cmd_args (t_box **box, t_prompt **prompt);

//02_boxes_6_cmd_2.c
void init_what_to_take(t_box **box);
void mark_redir(t_box **box);
void mark_word_2(int start, int end, t_box **box);
void mark_word(t_box **box);
int is_last_redir_2(t_box **box, int nb_redir_x);

//02_boxes_6_cmd_3.c
int rest_numof_words(t_box **box);
void rest_get_ind_beginning_words(t_box **box);
int possible_cases(t_box **box, int index);
void cpy_1_word(t_box **box, int nb_of_word);

//02_boxes_7_dollar.c
void check_dollars_expansion(t_box **box, t_prompt **prompt);
int get_nb_of_dollars(t_box **box, int ind);
void ft_replace (t_box **box, int ind, char *str_after);
char *basic_itoa(int nb);
void get_updated_words(t_box **box, int ind, t_prompt **prompt);

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
//99_utils.c
// int     ft_isspace(int c);
// int	ft_putchar_fd(int c, int fd);
// int	ft_putstr_fd(char *str, int fd);
void    ft_print_welcome(void);
// size_t	ft_strlen(char *str);
//int	ft_atoi(const char *str);
//void	ft_puterror_exit(char *str);
void    ft_puterror_exit(char *str);
void    ft_puterror(char *str);
// int	ft_strncmp(const char *s1, const char *s2, size_t n);


// We will use the following functions to manage the input of the shell
//in the cases of redirections and pipes.
// void here_doc(t_prompt *data);

/* FUNCTIONS FOR INITIALIZING COMMANDS */
int initialize_cmd(t_box *box, t_prompt *data, int substr_id);


/* FUNCTIONS OF THE PIPES */

int create_pipe(t_box *box);
int handle_child_process(t_box *box, t_prompt *data, int id_box);
int handle_parent_process(t_box *box);
int close_files(t_box *box, int i);// int handle_input(t_box *box);

/*  FUNCTIONS OF THE REDIRECTIONS */ 
int handle_redirection(t_box **box, t_prompt *data); 
int handle_output(t_box *box, int i);

/* FUNCTIONS FOR HANDLING DIFFERENT TYPES OF REDIRECTIONS */
int handle_heredoc(t_box **box);
int handle_input_infile(t_box **box);
int handle_output_append(t_box **box,int i);
int handles_output_strong(t_box **box);


/* FUNCTIONS FOR EXECUTING COMMANDS */
int execute_multiple_commands(t_box *box);
int execute_simple_command(t_box *box);
int execute_commands(t_box *box);


/* FUNCTIONS OF SIGNALS */													

int handle_sigint(int sig);
int handle_eof(int sig);
int handle_sigquit(int sig);


/* FUNCTIOS OF ENVIRONMENT */

t_prompt *ft_init_data(char **envp); 
///The ft_init_data function initializes the data structure.
int		ft_setenv_local(t_vars *list, char *name, char *value, int overwrite); 
// This function sets a new variable in the environment local and volcate memory for it
// t_vars *ft_getenv_local(t_vars *line, char *name);
t_vars *ft_getenv_local(t_vars *line, char *name);

// This function searches the environment list to find the environment variable name, 
// and returns a pointer to the corresponding element
t_vars	*ft_varsnew(char *name, char *value); 
// This function creates a new linked list of
// environment local and volcate memory for it
int		ft_sstrncmp(char *str, char c); 
// This fuction compares the first character of a string with a character.
char	*ft_put_name_system(t_prompt *prompt);
// This function sets the name of the system in the prompt of the shell or terminal





#endif