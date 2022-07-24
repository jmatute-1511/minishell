/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmatute- <jmatute-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 15:46:48 by jmatute-          #+#    #+#             */
/*   Updated: 2022/07/24 21:49:27 by jmatute-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void			signal_handler(int signum)
{
	
	if (signum == SIGINT && g_proc > 0)
		kill(g_proc, SIGCONT);
	if (signum == SIGINT && g_proc == 0)
	{
		write(0, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}
void print(void)
{
	printf(YEL"• ▌ ▄ ·. ▪   ▐ ▄ ▪  .▄▄ ·  ▄ .▄▄▄▄ .▄▄▌  ▄▄▌  \n");
	printf(BYEL"·██ ▐███▪██ •█▌▐███ ▐█ ▀. ██▪▐█▀▄.▀·██•  ██•  \n");
	printf(BGRN"▐█ ▌▐▌▐█·▐█·▐█▐▐▌▐█·▄▀▀▀█▄██▀▐█▐▀▀▪▄██▪  ██▪  \n");
	printf(GRN"██ ██▌▐█▌▐█▌██▐█▌▐█▌▐█▄▪▐███▌▐▀▐█▄▄▌▐█▌▐▌▐█▌▐▌\n");
	printf(BLU"▀▀  █▪▀▀▀▀▀▀▀▀ █▪▀▀▀ ▀▀▀▀ ▀▀▀ · ▀▀▀ .▀▀▀ .▀▀▀ \n");
	printf(COLOR_RESET" \n");
}

void free_cmds(t_cmd_line **lst)
{
	t_cmd_line *aux;
	t_cmd_line *aux2;
	
	aux2 = NULL;
	aux = (*lst);
	while (aux)
	{
		if (aux->input)
			free(aux->input);
		if(aux->output)
			free(aux->output);
		if (aux->first_arg)
			free(aux->first_arg);
		if(aux->arguments)
			free(aux->arguments);
		if(aux->raw_cmd)
			free(aux->raw_cmd);
		aux2 = aux;
		aux = aux->next;
		free(aux2);
	}
	(*lst) = NULL;	
}

int main(int argc,char **argv,char **envp)
{
	t_myvars	*myvars;
	t_cmd_line	*lst;
	char		*str;

	(void)argc;
	(void)argv;
	myvars = NULL;
	//atexit(f_leaks);
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, SIG_IGN);
	print();
	myvars = start_vars(myvars,envp);
	while (1)
	{
		g_proc = 0;
		str = NULL;
		str = readline("Myshell%---->");
		if (str == NULL)
		{
			free_vars(&myvars);
			printf("exit\n");
			exit(myvars->stat);
		}
		if (ft_strcmp(str, "") != 0)
			add_history(str);
		if (init_nodes(&lst, &myvars, str) == 0)
		{
			//print_cmd(&lst);
			if(lst)
				execute_cmds(&lst, &myvars);
		}
		free(str);
	}
}
