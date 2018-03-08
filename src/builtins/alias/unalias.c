/*
** unalias.c for unalias in /home/manass_j/rendu/PSU_2015_42sh
** 
** Made by jonathan manassen
** Login   <manass_j@epitech.net>
** 
** Started on  Thu May 26 01:56:39 2016 jonathan manassen
** Last update Sat Jun  4 17:35:12 2016 jonathan manassen
*/

#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include "my.h"
#include "./include/alias.h"

void	save_alias(char **alias)
{
  int	fd;
  int	i;

  if ((fd = open(".shrc", O_CREAT | O_TRUNC | O_RDWR, 0644)) == -1)
    return;
  i = 0;
  while (alias[i])
    {
      my_fprintf(fd, "alias %s=\'%s\'\n", alias[i], alias[i + 1]);
      i = i + 2;
    }
  close(fd);
}

char	**delete_alias(char *str, char **alias, int i, int k)
{
  char	**name;
  int	j;

  name = get_name(str, i);
  j = 0;
  while (name[j])
    {
      i = 0;
      while (alias[i])
	{
	  if (check_builtin(name[j], alias[i]) != -1)
	    {
	      alias = delete_env_line(alias, i, 0, 0);
	      alias = delete_env_line(alias, i, 0, 0);
	      i = i - 2;
	    }
	  i = i + 2;
	}
      free(name[j]);
      j = j + 1;
    }
  if (k == 0)
    save_alias(alias);
  return (alias);
}

char	**launch_unalias(char *str, char **alias, int j, int *work)
{
  int	i;

  if ((i = check_builtin(str, "unalias")) != -1 &&
      check_str_space(str, i) == 1)
    {
      my_printf("unalias: Too few arguments.\n");
      *work = 1;
      return (alias);
    }
  if ((i = check_builtin(str, "unalias")) != -1 || j == 1)
    {
      if (j == 1)
	i = check_builtin("unset", "unset");
      alias = delete_alias(str, alias, i, j);
    }
  return (alias);
}
