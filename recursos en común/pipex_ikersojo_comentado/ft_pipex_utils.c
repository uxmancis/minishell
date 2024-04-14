/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipex_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uxmancis <uxmancis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 12:22:16 by uxmancis          #+#    #+#             */
/*   Updated: 2024/04/14 12:22:20 by uxmancis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipex_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uxmancis <uxmancis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 22:25:48 by isojo-go          #+#    #+#             */
/*   Updated: 2024/04/13 18:28:11 by uxmancis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_pipex.h"

void	ft_exit_w_error(char *str)
{
	if (ft_strcmp("errno", str) == 0)
	{
		perror("\033[31mError");
		ft_putstr_fd("\033[0;39m", 2);
	}
	else
	{
		ft_putstr_fd("\033[31mError: ", 2);
		ft_putstr_fd(str, 2);
		ft_putstr_fd("\033[0;39m", 2);
	}
	exit(EXIT_FAILURE);
}


/*
*	access: verifica permisos y existencia de archivo.
*				- Permisos: ¿el proceso tiene permiso de acceso (lectura,
*				           escritura o ejecución) al archivo?
*				- Existencia del archivo
*		· Librería: <unistd.h>
*		· Argumentos: access (<pathname>, <mode);
*						- Pathname (const char *): cadena con la ruta del archivo (debe
*									incluir el nombre del archivo al final)
*						- Mode (int): especifica tipo de acceso a verificar. Puede
*									  tomar 1 o más valores combinador mediante '|'.
*										> R_OK: comprobar si legible
*										> W_OK: comprobar si escribible
*										> X_OK: comprobar si ejecutable
*										> F_OK: comprobar si existe
*		· Devuelve: 0 (Success), -1 (Error de acceso)
*	
*/
static char	*ft_get_path(char *cmd, char **envp) //para obtener ruta completa de comando a ejecutar a partir de su nombre.
{
	int		i;
	char	**path_tab;
	char	*path;
	char	*aux;

	i = 0;
	while (ft_strnstr(*(envp + i), "PATH", 4) == NULL)
		i++;
	path_tab = ft_split(*(envp + i), ':');
	i = 0;
	while (*(path_tab + i))
	{
		aux = ft_strjoin(*(path_tab + i), "/");
		path = ft_strjoin(aux, cmd);
		free (aux);
		free (*(path_tab + i++));
		if (access(path, F_OK) == 0) //access: para verificar si un proceso tiene permiso de accesso a un archivo, o i existe un archivo. 
			break ;
	}
	while (*(path_tab + i))
		free (*(path_tab + i++));
	free (path_tab);
	return (path);
}

void	ft_space_to_tab(char **arg)
{
	char	*str;

	str = *arg;
	while (*str)
	{
		if (*str == 34 || *str == 39)
		{
			while (*str && (*str != 34 || *str != 39))
			{
				if (*str == ' ')
					*str = 9;
				str++;
			}
		}
		str++;
	}
}

static void	ft_tab_to_space(char **arg)
{
	char	*str;
	int		i;
	int		len;

	str = *arg;
	i = 0;
	while (*(str + i))
	{
		if (*(str + i) == 9)
			*(str + i) = ' ';
		i++;
	}
	len = i;
	if (*str == 34 || *str == 39)
	{
		i = 0;
		while (i < (len - 2))
		{
			*(str + i) = *(str + i + 1);
			i++;
		}
		*(str + i) = '\0';
	}
}

/*
*	ft_get_path: obtener ruta completa de comando a ejecutar a partir de su nombre, 
*				para poder pasarle esta ruta a execve.
*		· ¿Cómo? busca en las variables de entorno del programa las rutas en las
*				que podría encontrarse el comando especificado y devuelve la 
*				primera ruta válida.
*
*	execve (path, argv, env): ejecuta un programa en un proceso existente.
*	//execve: librería <unistd.h>
*		const char *path: ruta del archivo ejecutable (puede ser absoluta
*						  o variable la ruta)
*		char *const argv[]: argumentos pasados al programa. En arg[0] debe
*						  ser el nombre del programa. El último elemento
*						  debe ser puntero nulo (NULL), indica final del arr.
*		char *const envp[]: variables de entorno para el programa que se está
*							ejecutando.
*
*/
void	ft_run_command(char *arg, char **envp) //arg: comando a ejecutar, envp: array de punteros a cadenas = variables de entorno para el programa que se va a ejecutar
{
	char	**cmd;
	char	*cmd_path;
	int		i;
	int		error_flag;

	error_flag = 0;
	ft_space_to_tab(&arg); //cadena: comando y argumentos separados por espacios
	cmd = ft_split(arg, ' '); //zela por espacios? Baina, si ha convertido espacios en tabulaciones lehenau?
	i = 0;
	while (*(cmd + i))
		ft_tab_to_space((cmd + i++));
	cmd_path = ft_get_path(*(cmd + 0), envp); //access a distintos paths, generamos el correcto.
	if (execve(cmd_path, cmd, envp) == -1) //execve devuelve -1 si error. Si Success = no devuelve nada.
		error_flag = 1;
	i = 0;
	while (*(cmd + i))
		free (*(cmd + i++));
	free (cmd); 
	free (cmd_path);
	if (error_flag == 1)
		ft_exit_w_error("Command not found\n");
}