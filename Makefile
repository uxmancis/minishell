NAME		=	minishell
LIBFT		=	Libft/libft.a
INC			= 	inc/
BINDIR		=	bin/
SRC_DIR		= 	src/
OBJ_DIR		=	objs/

SRC 		= $(addprefix $(SRC_DIR), $(SRC_FILES))
SRC_FILES	=	0_0_main.c \
				000_debug_mode_1.c \
				000_debug_mode_2.c \
				000_debug_mode_3.c \
				000_debug_mode_4.c \
				00_env_data.c \
				00_init_env.c \
				00_minishell.c \
				01_input_pipe_1.c \
				01_input_pipe_2.c \
				01_input_quotes.c \
				01_input_split.c \
				02_boxes_1_init_1.c \
				02_boxes_1_init_2.c \
				02_boxes_1_init_3.c \
				02_boxes_2_redir_1.c \
				02_boxes_2_redir_2.c \
				02_boxes_2_redir_3.c \
				02_boxes_2_redir_4.c \
				02_boxes_3_hrdc_1.c \
				02_boxes_3_hrdc_2.c \
				02_boxes_4_infile.c \
				02_boxes_5_outfile_append.c \
				02_boxes_5_outfile_strong.c \
				02_boxes_6_cmd_1.c \
				02_boxes_6_cmd_2.c \
				02_boxes_6_cmd_3.c \
				02_boxes_6_cmd_4.c \
				02_boxes_6_cmd_5.c \
				02_boxes_7_dollar_1.c \
				02_boxes_7_dollar_2.c \
				02_boxes_7_dollar_3.c \
				02_boxes_7_dollar_4.c \
				02_boxes_7_dollar_5.c \
				02_boxes_7_dollar_6.c \
				02_boxes_7_dollar_7.c \
				02_boxes_7_dollar_8.c \
				02_boxes_7_dollar_9.c \
				02_boxes_7_dollar_10.c \
				02_boxes_red_utils_1.c \
				02_boxes_red_utils_2.c \
				02_boxes_utils_nav.c \
				02_boxes_word_utils_hrdc.c \
				02_boxes_word_utils_infile.c \
				02_boxes_word_utils_outf_app.c \
				02_boxes_word_utils_outf_str.c \
				03_initialize_cmd.c \
				03_redirects.c \
				03_command_path.c \
				03_command_path_2.c \
				04_generate_forks.c \
				04_pipefd.c \
				05_here_docs.c \
				06_cd_bulting.c \
				06_cd_bulting_2.c \
				06_exec_builting.c \
				06_exec_builting_2.c \
				06_export.c \
				06_unset.c \
				07_close.c \
				07_signals.c \
				09_exit.c \
				09_puterror.c \
				10_utils_1.c \
				10_utils_2.c

# main_redirections.c 
				
OBJS_FILES	= $(SRC:$(SRC_DIR)%.c=$(OBJ_DIR)%.o)

CC			= gcc -fsanitize=address -g3
FLAGS		= -Wall -Wextra -Werror
# LIBS		=  -lreadline
RM			= rm -rf

DEF_COLOR = \033[0;39m
GRAY = \033[0;90m
RED = \033[0;31m
GREEN = \033[0;92m
YELLOW = \033[0;93m
BLUE = \033[0;94m
MAGENTA = \033[0;95m
CYAN = \033[0;96m
WHITE = \033[0;97m
CLEAR = \033[0m
OKLOGO = \033[80G\033[32m[OK]\033[0m\n

all:		$(NAME)

$(NAME): build_message $(BINDIR)$(NAME)

build_message:
#	@echo "$(BLUE)COMPILING MINISHELL...$(CLEAR)"

$(BINDIR)$(NAME): $(OBJS_FILES) $(LIBFT)
	@$(CC) -o ./$(BINDIR)/$(NAME) $(FLAGS) $(OBJS_FILES) $(LIBFT) -I$(INC) -lreadline
	@echo "$(GREEN)MINISHELL COMPILED SUCCESFUL!$(CLEAR)"

$(LIBFT):
	@make -C Libft/

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
		@mkdir -p $(OBJ_DIR)
		@mkdir -p $(BINDIR)
		@$(CC) $(FLAGS) -I$(INC) -c $< -o $@
						
clean:
		@echo "$(YELLOW)FILES REMOVED!$(DEF_COLOR)"
		@$(RM) $(OBJ_DIR)
		@$(RM) $(BINDIR)
		@make -C Libft/ clean
			
fclean:		clean
			@$(RM)  $(NAME)
			@make -C Libft/ fclean
			@echo "$(RED)$(NAME) REMOVED!$(DEF_COLOR)"
			
re:			fclean all
run:
			@make re
			./bin/minishell
.PHONY:		all clean fclean re libft 