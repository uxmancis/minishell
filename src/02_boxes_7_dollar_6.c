/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   02_boxes_7_dollar_6.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uxmancis <uxmancis@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 17:59:29 by uxmancis          #+#    #+#             */
/*   Updated: 2024/06/23 21:41:56 by uxmancis         ###   ########.fr       */
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
	if (word_to_be_checked[x_y.index_y] == '$'
		&& (tmp_dict_quotes[x_y.index_y] == 0
			|| tmp_dict_quotes[x_y.index_y] == 2))
		return (1);
	return (0);
}

int	next_is_space_or_end(char *word_to_be_updated, t_x_y_word x_y)
{
	int	len_word;

	len_word = ft_strlen(word_to_be_updated);
	if (x_y.index_y == len_word - 1)
		return (1);
	if ((x_y.index_y + 1) < len_word)
	{
		if (word_to_be_updated[x_y.index_y + 1] == ' ')
			return (1);
	}
	return (0);
}

int	next_is_sec_dollar(char *word_to_be_updated, t_x_y_word x_y)
{
	int	len_word;

	len_word = ft_strlen(word_to_be_updated);
	if ((x_y.index_y + 1) < len_word)
	{
		if (word_to_be_updated[x_y.index_y + 1] == '$')
			return (1);
	}
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
}

int	ft_get_pid_int(int fd, int i, int pid)
{
	char	buffer[10];
	ssize_t	bytesread;

	fd = open("/proc/self/stat", O_RDONLY);
	if (fd == -1)
	{
		ft_puterror("Failed to open /proc/self/stat\n");
		return (-1);
	}
	bytesread = read(fd, buffer, sizeof(buffer) - 1);
	if (bytesread == -1)
	{
		ft_puterror("Failed to read from /proc/self/stat");
		close(fd);
		return (-1);
	}
	buffer[bytesread] = '\0';
	i = 0;
	pid = 0;
	while (buffer[i] >= '0' && buffer[i] <= '9')
		pid = pid * 10 + (buffer[i++] - '0');
	return (close(fd), pid);
}
