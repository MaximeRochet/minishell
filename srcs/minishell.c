/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmasse <cmasse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 16:07:22 by cerisemasse       #+#    #+#             */
/*   Updated: 2021/10/21 13:18:26 by cmasse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(int ac, char **av, char **env)
{
	t_shell *shell;
	(void)ac; 
	(void)av;


	shell = ft_calloc(sizeof(t_shell), 1);
	//ft_format_struct(shell);
	init_env(env, shell);
	//shell.str_cmd = (char *)calloc(sizeof(char),1);
	//if(!shell.str_cmd)
	//{
	//   printf("Malloc failure");
	//  return (0);
	//}
	while(!shell->str_cmd || ft_strncmp(shell->str_cmd, "exit", 4))
	{
		recup_prompt(shell);
		shell->str_cmd = readline(shell->prompt);
		if(shell->str_cmd && strlen(shell->str_cmd) > 0)
		{	
			add_history(shell->str_cmd);
			parsing(shell);
			print_list_cmd(shell->list_cmd);
			execution(shell);
			shell->list_cmd = NULL;
			//ft_format_struct(shell);
			//free(shell.str_cmd);
		}
	}
	dprintf(1, "exit");
	free(shell->str_cmd);
	return (0) ;
}
