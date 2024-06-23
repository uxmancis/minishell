/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+
	+:+     */
/*   By: dbonilla <dbonilla@student.42.fr>          +#+  +:+
	+#+        */
/*                                                +#+#+#+#+#+
	+#+           */
/*   Created: 2024/04/14 10:37:02 by uxmancis          #+#    #+#             */
/*   Updated: 2024/05/19 16:48:25 by dbonilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H

#define DEF_COLOR "\033[0;39m"
#define GRAY "\033[0;90m"
#define RED "\033[0;31m"
#define GREEN "\033[0;92m"
#define YELLOW "\033[0;93m"
#define BLUE "\033[0;94m"
#define MAGENTA "\033[0;95m"
#define CYAN "\033[0;96m"
#define WHITE "\033[0;97m"
#define RESET_COLOR "\033[0m"
#define AQUAMARINE "\033[0;96m"

#define MAX_FILENAME_LENGTH 256

#include "../Libft/inc/libft.h"
#include <dirent.h>
#include <fcntl.h>
#include <readline/history.h>
#include <readline/readline.h>
#include <signal.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <termios.h>
#include <unistd.h>

typedef enum e_red_type t_red_type;
typedef struct s_prompt t_prompt;
typedef struct s_box t_box;
typedef struct s_vars t_vars;
typedef struct s_cmd t_cmd;

typedef struct s_x_y_word
{
    int index_x;
    int index_y;
}   t_x_y_word;

enum e_red_type
{
	NO_REDIRECTION, // 0
	OUTFILE_APPEND, // 1: >> añade
	OUTFILE_STRONG, // 2: > sobreescribe "trunc"
	INFILE,			// 3: <
	HEREDOC			// 4: <<
};

struct s_box
{
	int heredoc_fd;
	char *input_substr; // Substr virgen
	// int     id_substr;
	// pdte. dict_quotes
	int *dict_quotes;
	int nb_of_redir;		   // number of redirecciones
	int **dict_red_index_type; //[0]: index, [1]: type

	// About redirecciones:
	int nb_of_heredocs;
	char **words_hrdc; // delimiter words
	char **words_hrdc_tmp; // delimiter words
	int is_infile;
	// YES[1]/NO[0] is there any infile '<' along dict_red_index_type
	int nb_of_infile;	 // How many infile
	char **words_infile; // infile filenames
	char **words_infile_tmp; // infile filenames
	int is_outfile_append;
	// YES[1]/NO[0] is there any outfile_append '>>' along dict_red_index_type
	int nb_of_outfile_append;	 // How many outfile append
	char **words_outfile_append; // outfile filenames
	char **words_outfile_append_tmp; // outfile filenames
	int is_outfile_strong;
	// YES[1]/NO[0] is there any outfile_append '>' along dict_red_index_type
	int nb_of_outfile_strong;	 // How many outfile strong
	char **words_outfile_strong; // outfile filenames
	char **words_hrdc_tmp; // delimiter words
	/* TEMP */
	char **words_infile_tmp; // infile filenames
	char **words_outfile_append_tmp; // outfile filenames
	char **words_outfile_strong_tmp; // outfile filenames

	// About command, flags and argumentos:
	char *what_to_take;
	int nb_of_words_rest;
	int *index_beginning_words_rest;
	char **rest_info_potential_cmd;

	//Others, for convenience:
    pid_t tmp_pid; //i believe i've finally not used the variable  
    char *tmp_pid_str; //i believe i've finally not used the variable
    char flag_word_or_cmd; //'W' or 'C' to tell what are we aiming to expand   


	// CMDS
	char **envp;
	char **command;
	int nb_substr;
	int heredoc;
	int fd_in;
	int close_in;
	int fd_out;
	int close_out;
	int nb_cmd;
	int nb_pipes;
	int child;
	int *pids;
	// int     parent_pid;
	char **cmd_options;
	char *cmd_path;

	// t_prompt *prompt;
	// EDER
	int dflt_in;
	int dflt_out;
};

/* STR*/
struct s_vars
{
	char *name;
	char *val;
	int is_exp;
	struct s_vars *next;
};

/*Stores info about the received prompt*/
struct s_prompt
{
	char *input;	  // Input virgen
	char *prompt;	  // Prompt del sistema
	int *dict_quotes; //'0': outside of quotes, '1' inside single quotes,'2' inside double quotes
	int nb_of_pipes;  //-1: pipe wrong position, 0: no pipe, >0: number of pipes
	int nb_of_substr;
	// int line_infd;
	// int line_outfd;
	char **envp;
	char **total_substr_input;
	// Input dividido en n cadenas (en base a pipes fuera de comillas)
	int *arr_index_pipes; // index of pipes
	t_vars *vars;
	// t_box *box;
	// ---------------CAMBIOS ANDER------------
	int pipefd[2];
	int fd_aux;
	int pid;
	int tmp_in;
	int tmp_out;
	// ----------------------------------------
	t_box	**arr_boxes;
};

/*
*   w2update = word to update
*/
typedef struct s_word_and_dictquotes
{
    char *w2update;
    int *dict_q_to_update;
    int x;
    int y;
    int ind_pid_str;
    int ind_old_word;
    int ind_dollar;
    int ind_new_word;
    int keep_new_len_word;
    int len_val;
    int new_len;
    int ind_val;
    int len_str_to_find;
    int keep_len_new_word;
    char *tmp_val;
}   t_w_d;

// minishell.c
//  void ft_begin(t_prompt *data);

// 00_minishell.c
void ft_free_input(t_prompt *data);
void ft_free_prompt(t_prompt *data);
//  void ft_begin(int argc, char **argv, char **env);
int ft_get_substr(t_prompt *prompt);
// 00_env_data.c
void ft_import_envp(t_prompt *data, char **envp);
int ft_setenv_local(t_vars *list, char *name, char *value, int overwrite);

// 00_init_env
t_prompt *ft_init_data(char **envp);
t_vars *ft_getenv_local(t_vars *line, char *name);
t_vars *ft_varsnew(char *name, char *value);

// 01_input_pipe.c
int ft_where_r_pipes(t_prompt **prompt); // función Índice - Principal
int ft_is_pipe(t_prompt **t_prompt);
// ¿Hay pipes en posición válida? Y/N/Cuántos
void set_index_pipe(t_prompt **prompt);
// ¿En qué posición están estos pipes? Input: dictionary. Output: arr_index_pipes

// 01_input_quotes.c
//  int ft_quotes(t_prompt **prompt);
int ft_quotes(char *input, int **dict_quotes);
// int ft_quotes_2(t_prompt **prompt, int i);
int ft_quotes_2(char *input, int **dict_quotes, int i);
// int ft_quotes_3(t_prompt **prompt, int i);
int ft_quotes_3(char *input, int **dict_quotes, int i);
// int ft_where_r_u (int index, int *dictionary);

// 01_input_split.c
void ft_split_input(t_prompt **prompt);
char *ft_split_from_to(int start, int end, char *src_input);
// char	**ft_split_input(t_prompt prompt);

//02_boxes_1_init_1.c
void	get_single_str(t_prompt *prompt, t_box **box);

//02_boxes_1_init_2.c
void	ft_free_box(t_box *box);

// 02_boxes.c
int ft_gen_boxes(t_prompt *prompt);
int ft_box_init(t_box **box, t_prompt *prompt, int substr_id);
int get_dict_quotes(t_box **box);
void generate_substr(t_prompt *prompt, int substr_id, t_box **box);
void ft_strcpy(char *str_src, char **str_dst);

// 02_boxes_init.c
void ft_free_char(char **words, int nb_of_words);
void ft_free_tab(char **words);

void ft_free_int(int **words, int nb_of_words);
void ft_boxes_initialize(t_box **box);

// 02_boxes_redir.c
int get_redirections(t_box **box);
int ft_fill_red_info(t_box **box);
int set_red_index_type(t_box **box);
int set_red_greater_than(t_box **box, int *i, int index_of_arr);
int set_red_less_than(t_box **box, int *i, int index_of_arr);
int ft_get_numof_redir(t_box **box);
char *ft_enum_to_str(int enumerator);
int check_if_three_redirs(t_box **box, int i);

// 02_boxes_rest.c
int get_rest(t_box **box, t_prompt **prompt);
int ft_get_numof_heredocs(t_box **box);
int ft_confirmed_end(t_box **box);
void get_arr_heredoc(int **arr_ind_heredoc, t_box **box);
int are_all_delimiters(int *arr_word_yes_no, t_box **box, t_red_type red_type);

// 02_boxes_hrdc_1.c
int ft_heredocs(t_box **box, enum e_red_type);
int ft_get_numof_heredocs(t_box **box);
void ft_check_delimiter(t_box **box);
void get_arr_heredoc(int **arr_ind_heredoc, t_box **box);
void get_end_arr(int **arr_end, t_box **box, int *arr_ind_heredoc);

// 02_boxes_hrdc_2.c
int get_ind(int hrdc_ind_in_substr, t_box **box);
void get_delimiters(int *arr_ind_heredoc, t_box **box);
void get_word(int start, int end, t_box **box, int heredoc_nb);

// 02_boxes_red_utils.c
int get_nb_of_red_type(t_box **box, t_red_type red_type);
void get_specif_index_red(int **arr_ind_red_type, t_box **box,
						  t_red_type red_type);
void get_word_red(int **arr_word_yes_no, t_box **box, int *arr_ind_red_type,
				  t_red_type red_type);
void get_word_mgmt(int *arr_ind_red_type, t_box **box, t_red_type red_type);
int ft_check_first_word(t_box **box, t_red_type red_type);

// 02_boxes_utils_nav.c
int has_end_last_check(int start, int end, t_box **box);
int is_last_redir(t_box **box, int index_current_heredoc);
int has_end_word(int index_hrdc_in_substr, t_box **box, int red_nb_x);

// 02_boxes_4_infile.c
int ft_infiles(t_box **box, t_red_type red_type);
int is_infile(t_box **box);
int ft_get_numof_infile(t_box **box);

// 02_boxes_5_outfile_append.c
int ft_outfile_append(t_box **box, t_red_type red_type);
int is_red_type(t_box **box, t_red_type red_type);
// generic para todos (NEW)
int ft_get_numof_red_type(t_box **box, t_red_type red_type);
// generic para todos (NEW)

// 02_boxes_5_outfile_strong.c
int ft_outfile_strong(t_box **box, t_red_type red_type);

// 02_boxes_6_cmd_1.c
int	ft_cmd_args(t_box **box, t_prompt **prompt);

// 02_boxes_6_cmd_2.c
void init_what_to_take(t_box **box);
void mark_redir(t_box **box);
void mark_word_2(int start, int end, t_box **box);
void mark_word(t_box **box);
int is_last_redir_2(t_box **box, int nb_redir_x);

// 02_boxes_6_cmd_3.c
int rest_numof_words(t_box **box);
void rest_get_ind_beginning_words(t_box **box);
int possible_cases(t_box **box, int index);
void cpy_1_word(t_box **box, int nb_of_word);

//02_boxes_6_cmd_4.c
int	ft_get_what_to_take(t_box **box);

// 02_boxes_7_dollar_1.c
void	expand_infile_words(t_box **box, t_prompt **prompt);
int find_dollars_and_replace(t_box **box, t_x_y_word x_y,
							 int **tmp_dict_quotes_word, t_prompt **prompt);
void check_dollars_expansion(t_box **box, t_prompt **prompt);

// 02_boxes_7_dollar_2.c
void	cpy_arr_with_len_2(int *arr_src, int **arr_dst, int len);
void	replace_env(char **w2up, t_x_y_word x_y, char *tmp_val, int **tmp_dict_quotes_word);
char	*get_word_2(char *old_word_before_free, t_x_y_word x_y);
void cpy_to_val(char *str_src, char **str_dst);
char	*get_word_4(char *old_word_before_free, t_x_y_word x_y);

// 02_boxes_7_dollar_3.c
int	is_in_env(char *old_word_before_free, t_x_y_word x_y, t_prompt **prompt);
void	mng_to_replace_sec_dollar(char  **word_to_be_updated, t_x_y_word x_y, int **tmp_dict_quotes_word);
void	ft_free_word_and_dict(char **w2p, int **tmp_dict_quotes_word);
void finish_to_update_dict_quotes(int **tmp_dict_quotes_word, int new_len,
								  int *tmp_tmp_dict_quotes_word, int len_old_word);
void put_arr(int *arr, int len);
void get_old_word(char *str_src, char **str_dst);

// 02_boxes_7_dollar_4.c
int	get_len_word_2(char *old_word_2_check_before_free, t_x_y_word x_y);
void	replace_delete(char **wtu, char *str_src, t_x_y_word x_y, int len_new_total_word);
void	mng_to_replace_delete(char **word_to_be_updated, t_x_y_word x_y);
void	cpy_arr_with_len(int *arr_src, int *arr_dst, int len);
void fill_with_nine(int **tmp_dict_quotes_word, int len);

// 02_boxes_7_dollar_5.c
int	get_len_word(char *old_word_before_free, t_x_y_word x_y);
int	get_len_word_3(char *word_to_be_updated, t_x_y_word x_y);
void	replace_pid_sec_dollar(t_w_d **w_d, char *kow, int *kod, int nlw);
int is_special_char(char c);

// 02_boxes_7_dollar_6.c
int	is_dollar(char *word_to_be_checked, t_x_y_word x_y, int *tmp_dict_quotes);
int	next_is_space_or_end(char *word_to_be_updated, t_x_y_word x_y);
int	next_is_sec_dollar(char *word_to_be_updated, t_x_y_word x_y);
void cpy_word(char *str_src, char **str_dst);
int get_len_pid(t_box **box);
int	ft_get_pid_int(void);

//02_boxes_7_dollar_8.c
int	next_is_question(char *word_to_be_updated, t_x_y_word x_y);

//02_boxes_7_dollar_9.c
void	get_each_word_up(char **w, int nb_word_x, t_box **box, t_prompt **prompt);
int	no_more_dollars(char *w, t_x_y_word x_y, int *dict);
int	*generate_specif_dict_quotes(t_box **box, char *w, int nb_word_x, char flag);

//02_boxes_7_dollar_10.c
char	*ft_get_pid_str(void);
void	mng_to_replace_env(char **w, t_x_y_word x_y, t_prompt **p, int **dict);

// 02_boxes_7_dollar_.c
void ft_free(void *arr);
int get_nb_of_dollars(t_box **box, int ind);
void ft_replace(t_box **box, int ind, char *str_after);
char *basic_itoa(int nb);
void fill_tmp_dict_quotes(t_box **box, int **tmp_dict_quotes_word, int len,
						  int start);

// 02_boxes_word_utils_hrdc.c
void	get_word_hrdc_1(t_box **box, int *arr_ind_red_type);
void get_word_hrdc_2(int start, int end, t_box **box, int heredoc_nb);

// 02_boxes_word_utils_infile.c
void get_word_infile_1(t_box **box, int *arr_ind_red_type);
void get_word_infile_2(int start, int end, t_box **box, int red_type_nb_x);

// 02_boxes_word_utils_outf_app.c
void get_word_outf_app_1(t_box **box, int *arr_ind_red_type);
void get_word_outf_app_2(int start, int end, t_box **box,
						 int red_type_nb_x);

// 02_boxes_word_utils_outf_str.c
void get_word_outf_str_1(t_box **box, int *arr_ind_red_type);
void get_word_outf_str_2(int start, int end, t_box **box,
						 int red_type_nb_x);

// 03_initialize_cmd.c
int setup_box(t_box **box, t_prompt *data, int box_id);
int init_data_cmd(t_box **box, t_prompt *data, int box_id);
int init_cmd(t_box **box, t_prompt *data, int box_id);

// int initialize_cmd(t_box **box, t_prompt *data, int substr_box_id);
// char    *get_cmd(t_cmd *cmd_data,  t_prompt *data, t_box **box);
char **ft_getenv_paths(t_prompt *data);
char *get_cmd_path(t_cmd *cmd_data, t_box **box);
char *get_cmd(t_cmd *cmd_data, t_prompt *data, t_box **box);

// 04_generate_forks.c
int create_child_process(t_box *box, t_prompt *data, int box_id);
// int	handle_parent_process(t_prompt *data);

// 03_redirects.c
int close_files(t_box *box);
int handle_input_infile(t_box **box, int index_red);
int handle_output_append(t_box **box, int index_red);
int handle_output_strong(t_box **box, int index_red);
int handle_redirects(t_box **box);
// 05
/*PRODDDDFFFFFFF*/
// static char *ft_lst_to_str(t_vars *tmp) ;
// 03_command_path
int ft_run_command(t_box **box, t_prompt *data);
char *ft_lst_to_str(t_vars *tmp);
int ft_vars_size(t_prompt *data);
char **ft_init_get_path(int *i, char **path, t_prompt *data);
char *ft_get_path(char *cmd, t_prompt *data);
char **ft_gen_envp(t_prompt *data);
char **split_command(t_box **box);
// char *determine_command_path(char *cmd, t_box **box, t_prompt *data);
int ft_vars_size(t_prompt *data);

// 04_piepefd.c
int baby_sister_for_the_childs(int input, int output, t_box *box);
int create_pipe(t_box *box, int boix_id);

// 05_here_docs.c
int handle_heredoc(t_box **box);

// 06_export_unset.c
int ft_delete_node(t_vars **env, char *name);
int ft_unset_builtin(t_prompt **prompt, char **cmd);
int ft_export_builtin(t_prompt *prompt, char **cmd);
int	ft_env_builtin(t_prompt **prompt, char **cmd);

// 06_cd_bulting.c

int ft_cd_builtin(t_prompt **data, char **cmd);
int ft_check_dir_permission(char *path);
void *ft_free_null(void *ptr);
void ft_free_envp(t_prompt *data);
char *ft_strjoin_arr(char **arr, char *del, int length);
char *ft_route_parser(char *route);
void ft_set_pwd(t_prompt **data, char *path);
char *ft_strcat(char *dest, const char *src);

// 06_exec_builtin.c
int is_builtin_command(char *cmd);
int which_cmd(t_box *box, t_prompt **prompt);
int ft_strcmp_2(char *str_2_check, char *cmd);
void ft_putchar(char c);
int ft_builtin_pwd(t_prompt **prompt);

// 07_signals.c
void ft_signal_handler(void);
void ft_signals(int signum);

// 09_exit.c
void ft_exit_builtin(t_prompt *prompt, int status);
void ft_free_custom_envp(t_prompt *data);
void ft_free_vars(t_prompt *data);
void cleanup_command(char **cmd);

// 07_Close.c
int close_pipefd(t_box *box);
int close_fdin_fdout(t_box *box);

// 10_utils.c
char *ft_put_name_system(t_prompt *data);
void ft_print_welcome(void);
int ft_sstrncmp(char *str, char c);
void ft_puterror(char *str);
void ft_putstr(char *str);

// utils_libft.c
size_t ft_strlen(const char *str);
int ft_strcmp(const char *s1, const char *s2);
char *ft_strdup(const char *s1);
char *ft_substr(char const *s, unsigned int start, size_t len);
int ft_isspace(int c);
void *ft_calloc(size_t count, size_t size);
char *ft_strdup(const char *s1);
void *ft_memcpy(void *dst, const void *src, size_t n);
int ft_isalnum(int c);

#endif