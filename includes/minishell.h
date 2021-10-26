/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cerisemasse <cerisemasse@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 16:12:47 by cerisemasse       #+#    #+#             */
/*   Updated: 2021/10/22 15:16:57 by cerisemasse      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef MINISHELL_H
# define MINISHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <signal.h>
#include <stdbool.h>
#include <limits.h>
#include <pwd.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <sys/types.h>
# include "../libft/libft.h"

typedef struct s_list_env
{
	char			*content;
	char			*name;
	struct s_list_env	*next;

}				t_list_env;

typedef struct s_list_cmd
{

	char			*cmd;
	char                	**arg;
	int                 	pipe;
	char **input; // <
	char **output; // >
	// int                 	*fd[4];
	struct s_list_cmd	*next;
	struct s_list_cmd	*prev;
}				t_list_cmd;

typedef struct s_shell
{
	char            *str_cmd;
	char			*prompt;
	int				quit;

	t_list_cmd		*list_cmd;
	t_list_env      *env;
}					t_shell;

typedef struct s_fonc
{
	char	*name;
	void	(*fct)(t_shell *shell);
}			t_fonc;

// LIST
void    ft_add_back_cmd(t_list_cmd **n, t_list_cmd *new);

//void	ft_add_front_cmd(t_list_cmd **n, t_list_cmd *new);
t_list_cmd	*ft_new_cmd(char **arg);
void		ft_add_back_env(t_list_env **alst, t_list_env *new);
t_list_env	*ft_lstnew_env(void *content, void *name);

// UTILS 
//void	ft_get_path(t_shell *shell, char *c);
char	*ft_strstr(char *str, char *to_find);
void	print_list_cmd(t_list_cmd *list);
void	print_shell(t_shell *shell);
int		char_is_in(char *str, char c);
int	ft_index_strchr(const char *s, int c);


void	print_env(t_list_env *lst);
char	*ft_get_env(t_shell *shell, char *name);

// PARSING
// PARSING_INIT
void    init_env(char **env, t_shell *shell);
void    ft_format_struct(t_shell *shell);
int		parsing(t_shell *shell);
int		ft_valide_quote_str(t_shell *shell);

// 	PARSING_VAR
void 	ft_check_variable(t_shell *shell);
void  	ft_replace_var(t_shell *shell, int i);
char	*ft_delete_var(int start, int end, t_shell *shell);
char	*ft_paste_name_var(int start,  char *var, t_shell *shell);


// PARSING_PIPE
char	*ft_replace_pipe_str(char *str, char c);
char	**ft_split_pipe_str(char *str);
void	ft_split_arg_str(t_shell *shell, char **str_split);

// PARSING_CMD

void	ft_remove_quote_cmd(t_shell *shell);
void	ft_path_cmd(t_shell *shell);
void	ft_check_exist_path(t_shell *shell);



// PARSING_REDIRECTION

void    ft_fill_redir(t_shell *shell);

//FONCTION PRINCIPALES
void	recup_prompt(t_shell *shell);
char	*shearch_in_env(t_list_env *env, char *name);

//EXECUTION
int execution(t_shell *shell);
int find_function(t_shell *shell);

//BUILT-IN
void fonction_cd(t_shell *shell);
void fonction_echo(t_shell *shell);
void fonction_env(t_shell *shell);
void fonction_export(t_shell *shell);
void fonction_unset(t_shell *shell);
void fonction_pwd(t_shell *shell);
void fonction_execve(t_shell *shell);

#endif
