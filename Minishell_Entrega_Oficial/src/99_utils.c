/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   99_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uxmancis <uxmancis@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 11:04:48 by uxmancis          #+#    #+#             */
/*   Updated: 2024/05/26 17:05:25 by uxmancis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

// int ft_isspace(int c)
// {
// 	if (c == ' ' || c == '\t' || c == '\n' || c == '\r' || c == '\f' || c == '\v')
// 		return (1);
//     return (0);
// }

void	*ft_calloc(size_t count, size_t size)
{
	void			*dst;
	unsigned char	*temp;
	size_t			total;

	// i = 0;
	total = size * count;
	dst = malloc (total);
	if (!dst)
		return (0);
	temp = dst;
	while (total > 0)
	{
		*temp = '\0';
		temp++;
		total--;
	}
	return (dst);
}
/*int main(void)
{
	size_t mem_size;
	size_t str_size;
	char *str = "uxu";


	str_size = ft_strlen(str);
	printf("%s", ft_calloc(str_size, sizeof(char)));
}*/

// /* DESCRIPTION:
// Outputs the char c to the file descriptor fd.
// The function returns the number of characters printed and -1 if fails to print.
// ---------------------------------------------------------------------------- */
int	ft_putchar_fd(int c, int fd)
{
	write(fd, &c, 1);
	return (1);
}

/* DESCRIPTION:
Outputs the string s to the file descriptor fd.
The function returns the number of characters printed and -1 if fails to print.
---------------------------------------------------------------------------- */
int	ft_putstr_fd(char *str, int fd)
{
	int	count;

	count = 0;
	if (!str)
		return (write(fd, "(null)", 6));
	while (*str)
	{
		count += ft_putchar_fd(*str, fd);
		str++;
	}
	return (count);
}

size_t	ft_strcpyy(char *dst, const char *src)
{
	size_t	i;
	char	*pt_src;

	pt_src = (char *)src;
	i = 0;
	while (pt_src[i] != '\0')
	{
		{
			dst[i] = pt_src[i];
			i++;
		}
		dst[i] = 0;
	}
	while (src[i])
		i++;
	return (i);
}
char	*ft_strcat(char *dest, const char *src)
{
	size_t	i;

	i = 0;
	while (*(dest + i))
		i++;
	while (*src)
		*(dest + i++) = *src++;
	*(dest + i) = '\0';
	return (dest);
}

int ft_sstrncmp(char *str, char c)
//Fuction to find the position of the equal sign
{
	int	i;

	i = 0;
	while (*(str + i))
	// loop to iterate over the string "str" for the length of the string
	{
		if (*(str + i) == c)
			// If the character at position "i" is equal to the character "c" return the position "i"
			return (i);
		i++;
	}
	return (-1);
}

void	ft_print_welcome(void)
{
	ft_putstr_fd("\n", 1);
	ft_putstr_fd(MAGENTA, 1);
	ft_putstr_fd("                                                     \n", 1);
	ft_putstr_fd("           :::      ::::::::                         \n", 1);
	ft_putstr_fd("         :+:      :+:    :+:                         \n", 1);
	ft_putstr_fd("       +:+ +:+         +:+                           \n", 1);
	ft_putstr_fd("     +#+  +:+       +#+        \t\tminishell 42 by:  \n", 1);
	ft_putstr_fd("   +#+#+#+#+#+   +#+           \t\tdbonilla          \n", 1);
	ft_putstr_fd("        #+#    #+#             \t\tuxmancis          \n", 1);
	ft_putstr_fd("       ###   ########.fr                             \n", 1);
	ft_putstr_fd("                                                     \n", 1);
	ft_putstr_fd(DEF_COLOR, 1);
}

char	*ft_put_name_system(t_prompt *data)
{
    char *sysname;
    char *user_name;
    char *pwd;
    if (!(ft_getenv_local(data->vars, "LOGNAME")) || !(ft_getenv_local(data->vars, "PWD")))
            return (printf("Error: No user or pwd\n"), NULL);
    user_name = ft_getenv_local(data->vars, "USER")->val;
    pwd = ft_getenv_local(data->vars, "PWD")->val;
    if ((!(sysname = (char *)malloc(ft_strlen(user_name) + ft_strlen(pwd) + 200))))
        return (NULL); // its important to return 0 if malloc fails
    ft_strcpyy(sysname, "\033[31m@");
    ft_strcat(sysname, user_name);
    ft_strcat(sysname, " ➜ ");
    ft_strcat(sysname, pwd);
    ft_strcat(sysname, " $ \033[0m");
    data->prompt = sysname;
    
    return (sysname);
}

int ft_ischarset(char c, const char *set)
{
    int i;

    i = 0;
    while (*(set + i))
    {
        if(*(set + i) == c)
                return(1);
        i++;
        
    }
    return(0);
}


// size_t	ft_strlen(const char *str)
// {
// 	size_t	i;

// 	i = 0;
// 	while (str[i] != '\0')
// 	{
// 		i++;
// 	}
// 	return (i);
// }

// int	ft_strncmp(const char *s1, const char *s2, size_t n)
// {
// 	size_t	i;

// 	i = 0;
// 	while ((s1[i] != '\0' || s2[i] != '\0') && i < n)
// 	{
// 		if (s1[i] == s2[i])
// 		{	
// 			i++;
// 		}
// 		else
// 			return ((unsigned char ) s1[i] - (unsigned char) s2[i]);
// 	}
// 	return (0);
// }

// int	ft_atoi(const char *str)
// {
// 	int	i;
// 	int	sign;
// 	int	num;

// 	i = 0;
// 	sign = 1;
// 	num = 0;
// 	while (str[i] != '\0')
// 	{
// 		while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n'
// 			|| str[i] == '\r' || str[i] == '\v' || str[i] == '\f')
// 			i++;
// 		if (str[i] == '+' || str[i] == '-')
// 		{
// 			if (str[i++] == '-')
// 				sign = -1;
// 		}
// 		while (str[i] >= '0' && str[i] <= '9')
// 		{	
// 			num = (num * 10) + (str[i] - 48);
// 			i++;
// 		}
// 		return (num * sign);
// 	}
// 	return (0);
// }









// int handle_heredoc(t_box **box)
// {
//     int tmp_nbr_of_hrdc;
//     int word_index = 0;
//     char *tmp_words_hrdc;
//     tmp_words_hrdc = (*box)->words_hrdc[word_index];
//     tmp_nbr_of_hrdc = (*box)->nb_of_heredocs;
//     while (tmp_nbr_of_hrdc > 0 )
//     {
//         char *line;
//         while ((line = readline("heredoc >")) != NULL)
//         {
//             if (box != NULL && *box != NULL && (*box)->words_hrdc != NULL && word_index < (*box)->nb_of_heredocs)
//             {
//                 printf("primera palabra %s", (*box)->words_hrdc[word_index]);
//             }
//             else
//             {
//                 printf("Error: Invalid access\n");
// }
//             // printf("primera palbra %s", (*box)->words_hrdc[word_index]);
//             if (strcmp(line, (*box)->words_hrdc[word_index]) == 0) 
//             {
//                 word_index++;  // Incrementa word_index solo cuando se encuentra la coincidencia
//                 free(line);
//                 break;
//             }
//             write(STDOUT_FILENO, ">", 1);  // Escribe el símbolo ">" en la consola
//             write(STDOUT_FILENO, line, strlen(line));  // Escribe la línea en la consola
//             write(STDOUT_FILENO, "\n", 1);  // Escribe un salto de línea en la consola
//             free(line);
//         }
//         tmp_nbr_of_hrdc--;
//     }
//     return 0;
// }