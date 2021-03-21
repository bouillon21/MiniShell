#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
#include "libft.h"
# define BUFFER_SIZE 32

int		get_next_line(int fd, char **line);
char	*ft_gnl_strjoin(char const *s1, char const *s2);
char	*ft_gnl_substr(char const *s, unsigned int start, size_t len);

#endif
