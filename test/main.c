/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmickey <hmickey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 13:17:10 by hmickey           #+#    #+#             */
/*   Updated: 2021/03/23 16:51:11 by hmickey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

int main(int argc, char **argv, char **envp)
{
	t_term	term;

	term.termtype = getenv("minishell");
	term.tgetent = tgetent(term.termbuf, term.termtype);
	// while (1)
	// {
	// if (key_enter == 1)
		printf("%s\n", "PIZDA");
	// }
	int ent;
	lines   = tgetnum("li");
	columns = tgetnum("co");
	while ((ent = tgetnum("@8") < 0))
	{
		sleep(1);
		printf("pizda\n");
	}
	
	printf("lines   (li) = %d\n", lines);	// высота терминала
	printf("columns   (co) = %d\n", columns);	 // ширина терминала
	printf("enter   (en) = %d\n", ent);	 // ширина терминала
}


//gcc main.c -ltermcap