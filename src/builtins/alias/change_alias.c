/*
** change_alias.c for 42sh in /home/manass_j/rendu/PSU_2015_42sh
** 
** Made by jonathan manassen
** Login   <manass_j@epitech.net>
** 
** Started on  Thu Jun  2 11:39:17 2016 jonathan manassen
** Last update Sat Jun  4 19:30:47 2016 jonathan manassen
*/

#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include "my.h"
#include "./include/alias.h"

void	change_alias_file(char **alias)
{
  int	fd;
  int	i;

  if ((fd = open(".shrc", O_WRONLY | O_CREAT | O_TRUNC, 0644)) == -1)
    return;
  i = 0;
  while (alias[i])
    {
      my_fprintf(fd, "alias %s=\'%s\'\n", alias[i], alias[i + 1]);
      i = i + 2;
    }
  close(fd);
}

char	**change_alias(char **alias, char *str, int i)
{
  char	*tmp;
  char	*a;
  int	j;

  if (check_alias_cmd(str, ' ') == -1)
    return (alias);
  j = -1;
  if ((tmp = malloc(sizeof(char*) * (my_strlen(str) + 1))) == NULL)
    exit(0);
  while (str[++j])
    tmp[j] = str[j];
  tmp[j] = '\0';
  tmp = take_away_alias(tmp);
  a = alias_short(tmp, ' ');
  tmp = alias_long(tmp, ' ');
  free(alias[i + 1]);
  if ((alias[i + 1] = malloc(sizeof(char*) * (my_strlen(tmp) + 1))) == NULL)
    exit(0);
  j = -1;
  while (tmp[++j])
    alias[i + 1][j] = tmp[j];
  change_alias_file(alias);
  free(a);
  free(tmp);
  return (alias);
}

int	check_correspondance_change_alias(char *str, char *alias)
{
  int	i;
  int	j;

  i = 0;
  while (str[i] && str[i] == ' ')
    i = i + 1;
  while (str[i] && str[i] != ' ')
    i = i + 1;
  while (str[i] && str[i] == ' ')
    i = i + 1;
  j = 0;
  while (str[i] && alias[j])
    {
      if (str[i] != alias[j])
	return (-1);
      i = i + 1;
      j = j + 1;
    }
  if (str[i] != ' ' || alias[j] != '\0')
    return (-1);
  return (1);
}

int	check_change_alias(char *str, char **alias)
{
  int	i;

  i = 0;
  while (alias[i])
    {
      if (check_correspondance_change_alias(str, alias[i]) != -1)
	return (i);
      i = i + 2;
    }
  return (-1);
}
