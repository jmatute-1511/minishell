/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmatute- <jmatute-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 17:23:12 by jmatute-          #+#    #+#             */
/*   Updated: 2022/05/13 21:01:03 by jmatute-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
 #define MINISHELL_H

#include "libft/libft.h"
#include <stdio.h>
#include <unistd.h>
#include <stdarg.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <dirent.h>
#include <sys/types.h>


typedef struct s_enviroment
{
    char 	*env_var;
	void    *next;    
}               t_enviroment;

typedef struct s_myvars
{
    char			*first_pwd;
	t_enviroment	*my_env;
    t_enviroment    *export_env;
    
}               t_myvars;
typedef struct s_vars_env
{

    t_enviroment    *my_env;
    t_enviroment    *export_env;
    char            *str;
    int             count;
    
}           t_vars_env;

typedef struct s_cmd_line
{
    char    *line;
    char    type;
    

}               t_cmd_line;
void			start_vars(t_myvars *myvars, char **envp) ;
void			built_get_pwd(void);
void			built_echo(char *str);
void			open_directory(char *str);
void			built_cd(t_myvars *myvars,char *str);
t_enviroment	*ft_nodenew(char *new_var);
void			ft_nodeadd_back(t_enviroment **lst, t_enviroment **new);
void            ft_nodeadd_alphabet(t_enviroment **lst, t_enviroment **new);
void			free_lst(t_enviroment *node);
void            built_export(t_enviroment **my_env ,t_enviroment **export_env, char *str);
void            print_env(t_enviroment *export_env, char *option);
//int             parse_cmd(char *str);
#endif