/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmatute- <jmatute-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 17:00:35 by jmatute-          #+#    #+#             */
/*   Updated: 2022/07/16 15:38:07 by jmatute-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_nodesize(t_enviroment *lst)
{
	size_t			len;
	t_enviroment	*aux;

	len = 0;
	aux = lst;
	while (aux)
	{
		aux = aux->next;
		len++;
	}
	return (len);
}

void	free_lst_node(t_enviroment *node)
{
	t_enviroment	*aux;

	aux = node;
	free(node->env_var);
	free(node);
}

t_cmd_line	*ft_cmd_nodenew(char *raw_cmd, size_t len)
{
	t_cmd_line	*new;
	char		*not_trim;

	not_trim = NULL;
	new = malloc(sizeof(t_cmd_line));
	if (!new)
		return (NULL);
	not_trim = ft_strldup(raw_cmd, len);
	new->input = NULL;
	new->output = NULL;
	new->first_arg = NULL;
	new->arguments = NULL;
	new->raw_cmd = ft_strtrim(not_trim, " |");
	new->next = NULL;
	free(not_trim);
	return (new);
}

void	ft_cmds_nodeadd_back(t_cmd_line **lst, t_cmd_line **new)
{
	t_cmd_line	*aux;

	if (lst)
	{
		if (*lst == NULL)
		{
			(*lst) = *new;
			return ;
		}
		aux = (*lst);
		while (aux->next)
			aux = aux->next;
		aux->next = *new;
	}
}
