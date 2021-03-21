#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include "../include/libft.h"
#include "../include/get_next_line.h"
#include <signal.h>

int main(int argc, char **argv, char **envp)
{
	char buf[1024];
	getcwd(buf, 1024);
	printf("%s", buf);
}