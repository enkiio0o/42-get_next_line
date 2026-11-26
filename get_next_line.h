#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
#   endif

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>

//get_next_line.c
char    *get_next_line(int fd);
char    *update_rest(char *rest_buf);
char    *get_line(char *rtn_line);
char    *read_line(int fd, char *line_save);
char *read_loop(int fd, char *line_save, char *buf_read);

//gnl_utils.c
char    *gnl_join_free(char *saved_line, char *buff_read);
int gnl_strchr(char *string, char searched_char);
int gnl_strlen(char *string);
void    *gnl_calloc(size_t n_elements,size_t n_bytes);
void    gnl_bzero(void *s, size_t n_elem);

#endif