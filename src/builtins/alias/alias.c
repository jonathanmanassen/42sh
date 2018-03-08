/*
** alias.c for 42sh in /home/manass_j/rendu/PSU_2015_42sh
** 
** Made by jonathan manassen
** Login   <manass_j@epitech.net>
** 
** Started on  Mon May 23 17:15:24 2016 jonathan manassen
** Last update Sat Jun  4 19:29:51 2016 jonathan manassen
*/

#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include "my.h"
#include "./include/alias.h"

char	**realloc_alias(char **alias, char *str)
{
  int	i;
  int	j;

  if (str == NULL || str[0] == '\0')
    return (alias);
  i = 0;
  while (alias[i])
    i = i + 1;
  alias = my_realloc_double_array(alias, 0, 0);
  if ((alias[i] = malloc(sizeof(char*) * (my_strlen(str) + 1))) == NULL)
    exit(0);
  j = 0;
  while (str[j])
    {
      alias[i][j] = str[j];
      j = j + 1;
    }
  alias[i][j] = '\0';
  alias[i + 1] = NULL;
  return (alias);
}

char	*take_away_alias(char *str)
{
  int	i;
  int	j;

  i = 0;
  while (str[i] && str[i] != ' ')
    i = i + 1;
  j = 0;
  while (str[++i])
    {
      str[j] = str[i];
      j = j + 1;
    }
  str[j] = '\0';
  return (str);
}

char	*alias_short(char *str, char c)
{
  int	i;
  int	j;
  int	k;
  char	*a;

  j = 0;
  i = 0;
  while (str[i] && str[i] != c)
    i = i + 1;
  if ((a = malloc(sizeof(char*) * ((i - j) + 1))) == NULL)
    exit(0);
  k = 0;
  while (j < i)
    a[k++] = str[j++];
  a[k] = '\0';
  return (a);
}

char	*alias_long(char *str, char c)
{
  int	i;
  int	j;

  i = 0;
  while (str[i] && str[i] != c)
    i = i + 1;
  if (c == '=')
    i = i + 2;
  else
    i = i + 1;
  j = 0;
  while (str[i] && str[i] != '\'')
    str[j++] = str[i++];
  str[j] = '\0';
  return (str);
}

char	**init_alias(int fd)
{
  char	**alias;
  char	*str;
  char	*a;

  if ((alias = malloc(sizeof(char**) * 1)) == NULL)
    exit(0);
  alias[0] = NULL;
  if ((fd = open(".shrc", O_RDONLY)) != -1)
    {
      while ((str = get_next_line(fd)) != NULL)
	{
	  if (check_alias_cmd(str, '=') != -1)
	    {
	      str = take_away_alias(str);
	      alias = realloc_alias(alias, (a = alias_short(str, '=')));
	      alias = realloc_alias(alias, alias_long(str, '='));
	      free(a);
	    }
	  free(str);
	}
    }
  close(fd);
  return (alias);
}
