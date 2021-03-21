#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include "../include/libft.h"
#include "../include/get_next_line.h"
#include <signal.h>

int main(int argc, char **argv, char **envp)
{
	char *line;
	int ret = 1;

	char **line_array;
	int i = -1;
	line_array = malloc(500);
	while (ret)
	{
		ret = get_next_line(0, &line);
		line_array[++i] = line;
	}
	i = -1;
	while(line_array[++i])
		printf("%s\n", line_array[i]);
}








// volatile sig_atomic_t keep_going = 1;

// void catch_alarm (int sig)
// {
//         keep_going = 0;
//         signal (sig, catch_alarm);
// }


// void do_stuff (void)
// {
// 	char a;
// 	read(0, &a, 1);
// 	puts ("Doing stuff while waiting for alarm....");
// }

// int main (void)
// {
// 	signal (SIGALRM, catch_alarm);
// 	alarm (5);
// 	while (keep_going)
// 		do_stuff ();
// 	return EXIT_SUCCESS;
// }