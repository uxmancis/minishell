/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   02_boxes_7_dollar_6.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uxmancis <uxmancis@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 17:59:29 by uxmancis          #+#    #+#             */
/*   Updated: 2024/06/16 12:49:27 by uxmancis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/*Checks whether if dollar is found outside of quotes
*   or inside double quotes (inside single quotes is a no).
*
*   I could just say tmp_dict_quotes[i] != 1.
*   I just feel == 0 || == 2 is a little safer though.
*
*   tmp_to_compare = (*box)->rest_info_potential_cmd word, but
*   the updated version. P.ej.: imagine it's already been updated 
*   because ofother dollars before
*/
int	is_dollar(char *word_to_be_checked, t_x_y_word x_y, int *tmp_dict_quotes)
{
	//printf("     "YELLOW"is_dollar"RESET_COLOR" | rest_info_potential_cmd[%d][%d] = %c\n", x_y.index_x, x_y.index_y, (*box)->rest_info_potential_cmd[x_y.index_x][x_y.index_y]);
	printf("     y = %d\n", x_y.index_y);
	//printf(GREEN"--\n"RESET_COLOR);
	//printf("     tmp_dict_quotes[%d]= %d\n", x_y.index_y, tmp_dict_quotes[x_y.index_y]);
	//if (tmp_to_compare[x_y.index_y] == '$' && (tmp_dict_quotes[x_y.index_y] == 0 || tmp_dict_quotes[x_y.index_y] == 2))
	if (word_to_be_checked[x_y.index_y] == '$' && (tmp_dict_quotes[x_y.index_y] == 0 || tmp_dict_quotes[x_y.index_y] == 2))
	{
		//printf("     yes! dollar, y =%d :)\n", x_y.index_y);
		return (1);
	}
	return (0);
}

int	next_is_space_or_end(char *word_to_be_updated, t_x_y_word x_y)
{
    int	len_word;

	len_word = ft_strlen(word_to_be_updated);
	if (x_y.index_y == len_word - 1) //END: $ in las position
		return (1);
	if ((x_y.index_y + 1) < len_word) //SPACE: si todavía sí hay más posiciones (a way to prevent overflow), then check if próxima posición es un ' '
	{
		if (word_to_be_updated[x_y.index_y + 1] == ' ')
			return (1);
	}
    return (0);
}

int	next_is_sec_dollar(char *word_to_be_updated, t_x_y_word x_y)
{
	int	len_word;

	//printf("next_is_sec_dollar | rest_info_potential_cmd[%d][%d] = %c\n", x_y.index_x, x_y.index_x, (*box)->rest_info_potential_cmd[x_y.index_x][x_y.index_y]);
	len_word = ft_strlen(word_to_be_updated);
	if ((x_y.index_y + 1) < len_word) //a way to prevent overflow
	{
		if (word_to_be_updated[x_y.index_y + 1] == '$')
		{
			//printf("                         second dollar identified!\n");
			return (1);
		}
	}
	//printf("                         no second dollar\n");
	return (0);
}

void	cpy_word(char *str_src, char **str_dst)
{
	int	len;
	int	i;

	len = ft_strlen(str_src);
	i = 0;
	while (len > 0)
	{
		(*str_dst)[i] = str_src[i];
		i++;
		len--;
	}
	//printf("               str_dst = "YELLOW"%s\n"RESET_COLOR, *str_dst);
}

int ft_get_pid_int(void)
{
	int fd;
	char buffer[10];
	ssize_t bytesRead;
	int i;
	int pid;
	// Abrir el archivo /proc/self/stat
	fd = open("/proc/self/stat", O_RDONLY);
	if (fd == -1)
	{
		ft_puterror("Failed to open /proc/self/stat\n");
		return (-1);
	}
	// Leer el contenido del archivo
	bytesRead = read(fd, buffer, sizeof(buffer) - 1);
    if (bytesRead == -1) {
        ft_puterror("Failed to read from /proc/self/stat");
        close(fd);
        return (-1);
    }
	// Asegurarse de que el buffer esté terminado en null
    buffer[bytesRead] = '\0';
    // Extraer el PID (primer valor en el archivo /proc/self/stat)
    i = 0;
	pid = 0;
	while (buffer[i] >= '0' && buffer[i] <= '9') {
        pid = pid * 10 + (buffer[i] - '0');
        i++;
    }
    //printf("El PID del proceso actual es: %d\n", pid);
	// Cerrar el archivo
    close(fd);
	return (pid);
}

/*get_len_pid
*
*	Returns:
*		-1: Error
*/
char *ft_get_pid_str()
{
	//int	len_process_pid;
	char *pid_str;
	int pid;

	pid = ft_get_pid_int();
	pid_str = basic_itoa(pid);
	//len_process_pid = ft_strlen(pid_str);
	return (pid_str);
}
