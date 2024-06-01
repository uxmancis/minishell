/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   05_redirects.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uxmancis <uxmancis@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 18:29:16 by uxmancis          #+#    #+#             */
/*   Updated: 2024/06/01 16:46:16 by uxmancis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../inc/minishell.h"

int close_files(t_cmd *cmd_data) 
{
    if (cmd_data->close_in > 1 && cmd_data->fd_in != -1) 
    {
        close(cmd_data->fd_in);
        // cmd_data->fd_in = -1;
    }

    // Cerrar fd_out si fue abierto y marcado para cerrar
    if (cmd_data->close_out > 1 && cmd_data->fd_out != -1) 
    {
        close(cmd_data->fd_out);
        // cmd_data->fd_out = -1;
    }
//     // Devuelve 0 para indicar que la función se ha ejecutado correctamente
    return (0);
}

#define MAX_FILENAME_LENGTH 256

int handle_input_infile(t_box **box, t_cmd *cmd_data, int index_red)
{
    int nb_of_infile = (*box)->nb_of_infile;
    printf(YELLOW);
    int i = 0;
    printf(BLUE "       handle_input_infile | "  RED RESET_COLOR MAGENTA "data->infd: "  GREEN "%d\n" , cmd_data->fd_in);
    printf(BLUE"        nb_infile --> [%d]\n", nb_of_infile);
    printf(BLUE"     WORDS INFILE FILE %s\n"RESET_COLOR, (*box)->words_infile[i]);
    printf(BLUE"     DICT INFILE '<'   [%d]\n"RESET_COLOR, (*box)->dict_red_index_type[index_red][1]);
    if ((*box)->dict_red_index_type[index_red][0] == HEREDOC) 
    {
        cmd_data->fd_in = open("HOLA", O_RDONLY);
        if (cmd_data->fd_in == -1) 
        {
            perror(RED"expanded_filename");
            // i++;
            return (-1);
        }
    }   
    if ((*box)->dict_red_index_type[index_red][0] == OUTFILE_APPEND || (*box)->dict_red_index_type[index_red][0] == OUTFILE_APPEND || (*box)->dict_red_index_type[index_red][0] == NO_REDIRECTION) 
    {
        index_red++;
        return -1;
    }         
    if ((*box)->words_infile[i] != NULL && (*box)->dict_red_index_type[index_red][1] == INFILE)
    {
        if (ft_strlen((*box)->words_infile[i]) >= MAX_FILENAME_LENGTH) 
        {
            printf(RED"Error: El nombre del archivo excede el límite de caracteres permitido.\n");
            return (-1);
        }
        if (cmd_data->fd_in != -1)
        {
            close(cmd_data->fd_in);
        }
        cmd_data->fd_in = open((*box)->words_infile[i], O_RDONLY);
        
        if (cmd_data->fd_in != -1)
        {
            close(cmd_data->fd_in);
            printf (RED"bash: %s: No such file or directory\n", (*box)->words_infile[i]);
            return (-1);
        }
        if (read(cmd_data->fd_in, NULL, 0) == -1) {
            perror(RED"Error al leer el archivo"RESET_COLOR);
            close(cmd_data->fd_in);
        }
    } else 
    {
        printf(RED"Error: No se proporcionó el nombre del archivo de entrada.\n"RESET_COLOR);
        return (-1);
    }
    cmd_data->fd_in = 1;
    printf(BLUE "       END   handle_input_infile | "  RED RESET_COLOR MAGENTA"data->infd: "  GREEN "%d\n" , cmd_data->fd_in);
    printf(WHITE"----------------------------------------------------------------------------\n\n"RESET_COLOR);
    return 0;
}

int handle_output_append(t_box **box, t_cmd *cmd_data, int index_red)
{
    int nb_of_outfile_append = (*box)->nb_of_outfile_append;
    int index_append;
    index_append = 0;
    printf(BLUE "       handle_outfile_append '>>'| "  RED RESET_COLOR WHITE "data->outfd: "  RED"%d\n" , cmd_data->fd_out);
    printf(BLUE"          nb_outfile --> [%d]   \n", nb_of_outfile_append);
    printf(BLUE"         WORDS OUTFILE APPEND '>>' " RESET_COLOR GREEN" [%s] \n"RESET_COLOR, (*box)->words_outfile_append[index_append]);
    printf(BLUE"         DICT OUTFILE APPEND  '>>' " RESET_COLOR GREEN" [%d] \n"RESET_COLOR, (*box)->dict_red_index_type[index_red][1]);
    
    if ((*box)->dict_red_index_type[index_red][1] == INFILE || ((*box)->dict_red_index_type[index_red][1] == NO_REDIRECTION  || (*box)->dict_red_index_type[index_red][1] == OUTFILE_STRONG )) 
    {
        index_red++;
        return -1;
    }
    if ((*box)->words_outfile_append[index_append] != NULL && (*box)->dict_red_index_type[index_red][1] == OUTFILE_APPEND)
    {
        if (ft_strlen((*box)->words_outfile_append[index_append]) >= MAX_FILENAME_LENGTH) 
        {
            printf("Error: El nombre del archivo excede el límite de caracteres permitido.\n");
            return (-1);
        }
        cmd_data->fd_out = open((*box)->words_outfile_append[index_append], O_WRONLY | O_CREAT | O_TRUNC, 0666);
        if (cmd_data->fd_out == -1)
        {
                perror((*box)->words_outfile_append[index_append]);
                return (-1);
        }
    }
    cmd_data->close_out++; // Indicar que se debe cerrar fd_out más tarde
    printf(BLUE "       END   handle_out_append | "  RED RESET_COLOR MAGENTA "data->outfd: "  GREEN "%d\n\n" , cmd_data->fd_out);
    printf(WHITE"----------------------------------------------------------------------------\n\n"RESET_COLOR);
    return (0);
}

int handle_output_strong(t_box **box, t_cmd *cmd_data, int index_red) 
{
    int index_strong = 0;
    int nb_of_outfile = (*box)->nb_of_outfile_strong;

    // index_strong = get_index_in_words(box, (*box)->nb_of_outfile_strong, index_red_in_substr);

    printf(RED"handle_output_strong | index_red = %d\n"RESET_COLOR, index_red);
    printf(RED "       handle_output_strong '>' | "  RED RESET_COLOR WHITE "data->outfd: "  RED"%d\n" , cmd_data->fd_out);
    printf(BLUE"        nb_outfile '>' [%d]\n", nb_of_outfile); 
    printf(MAGENTA"         WORDS STRONG OUTFILE '>'  " RESET_COLOR GREEN" [%s] \n", (*box)->words_outfile_strong[index_strong]);
    printf(MAGENTA"         DICT OUTFILE STRONG '>' " RESET_COLOR GREEN" [%d] \n", (*box)->dict_red_index_type[index_red][1]);
    if ((*box)->dict_red_index_type[index_red][1] == INFILE || (*box)->dict_red_index_type[index_red][1] == NO_REDIRECTION || (*box)->dict_red_index_type[index_red][1] == OUTFILE_APPEND ) 
    {
        index_red++;
        printf("por aqui\n");
        //break;
        return (-1);
    }
    if ((*box)->words_outfile_strong[index_strong] != NULL && (*box)->dict_red_index_type[index_red][1] == OUTFILE_STRONG)
    {
        if (ft_strlen((*box)->words_outfile_strong[index_strong]) >= MAX_FILENAME_LENGTH) 
        {
            printf("Error: El nombre del archivo excede el límite de caracteres permitido.\n");
            return (-1);
        }
        cmd_data->fd_out = open((*box)->words_outfile_strong[0], O_WRONLY | O_CREAT | O_APPEND, 0666);
        if (cmd_data->fd_out == -1)
        {                
                perror((*box)->words_outfile_strong[index_strong]);
                return (-1);
        }
    }
    cmd_data->close_out++; // Indicar que se debe cerrar fd_out más tarde
    printf(BLUE "       END   handle_out_strong | "  RED RESET_COLOR MAGENTA "data->outfd: "  RED "%d\n" , cmd_data->fd_out);
    printf(RED"             outf str - salimos\n"RESET_COLOR);
    printf(WHITE"----------------------------------------------------------------------------\n\n"RESET_COLOR);
    return (0);
}


int handle_redirects(t_box **box, t_cmd *cmd_data)
{
    int tmp_nb_of_red_type;
    int index_red = 0;

    tmp_nb_of_red_type = (*box)->nb_of_redir;
    printf(MAGENTA"            Handle_Redirects\n \n"RESET_COLOR);
    printf("nb_of_redir = %d\n",(*box)->nb_of_redir);
    while (tmp_nb_of_red_type > 0) 
    {
        printf(CYAN"         Current_redirect  " RESET_COLOR GREEN" [%d] \n", index_red);
        if ((*box)->dict_red_index_type[index_red][1] == INFILE)
        {
            printf("        infile was identified\n");
            if (handle_input_infile(box, cmd_data, index_red) == -1)
            {
                return (-1);
                // continue;
            }
            (*box)->words_infile++;
        }
        else if ((*box)->dict_red_index_type[index_red][1] == OUTFILE_STRONG) 
        {
            printf("        outf - strong was identified\n");
            if (handle_output_strong(box, cmd_data, index_red) == -1)
            {
                return (-1);
            }
            (*box)->words_outfile_strong++;

        }
        else if ((*box)->dict_red_index_type[index_red][1] == OUTFILE_APPEND) 
        {
            printf("        outf - append was identified\n");
            if (handle_output_append(box, cmd_data, index_red) == -1)
            {
                return (-1);
            }
            (*box)->words_outfile_append++;
        }
        index_red++;
        tmp_nb_of_red_type--;
    }
    if (close_files(cmd_data) == -1)
    {
            perror(RED"AQUII_>>>>>>"RESET_COLOR);
    }
    return (0);
}





