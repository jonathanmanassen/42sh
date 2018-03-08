/*
** double_redirect.c for 42sh in /home/manass_j/rendu/PSU_2015_42sh
** 
** Made by jonathan manassen
** Login   <manass_j@epitech.net>
** 
** Started on  Sun Jun  5 16:52:59 2016 jonathan manassen
** Last update Sun Jun  5 22:49:55 2016 jonathan manassen
*/

#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include "my.h"
#include "./include/redirections.h"

int	init_double_redirect(char *redirect, char *redirect_d, int *i)
{
  char	*str;
  int	fd;

  if ((fd = open(".tmp", O_WRONLY | O_CREAT | O_TRUNC, 0644)) == -1)
    exit(0);
  while ((str = get_next_line(0)) != NULL &&
	 ((*i == 4 && check_builtin(str, redirect) == -1) ||
	  (*i >= 7 && check_builtin(str, redirect_d) == -1)))
    {
      write(fd, str, my_strlen(str));
      write(fd, "\n", 1);
      free(str);
    }
  close(fd);
  if ((fd = open(".tmp", O_RDONLY)) == -1)
    *i = -1;
  return (fd);
}
