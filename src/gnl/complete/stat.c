/*
** stat.c for 42sh in /home/manass_j/rendu/PSU_2015_42sh/bonus
** 
** Made by jonathan manassen
** Login   <manass_j@epitech.net>
** 
** Started on  Mon May 23 17:00:04 2016 jonathan manassen
** Last update Sat Jun  4 19:21:28 2016 jonathan manassen
*/

#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include "my.h"
#include "./include/complete.h"

int	write_stat(char *tab, int col)
{
  struct stat	sb;

  if (stat(tab, &sb) == -1)
    return (col);
  if (sb.st_mode & S_IXUSR && !(S_ISDIR(sb.st_mode)))
    my_putchar('*');
  if (sb.st_mode & S_IXUSR && !(S_ISDIR(sb.st_mode)))
    col = col - 1;
  return (col);
}

void	check_if_slash_space(char *str, int *l, int *k)
{
  int	i;

  i = -1;
  *l = 0;
  *k = 0;
  while (str[++i])
    {
      if (str[i] == '/')
	*k = 1;
      if (str[i] == ' ')
	*l = 1;
    }
}

char	*change_str_for_stat(char *tab, char *str, int j)
{
  int	i;
  int	k;
  char	*tmp;

  if ((tmp = malloc(sizeof(char*) * (my_strlen(tab) + j + 2))) == NULL)
    exit(0);
  i = j;
  while (i > 0 && str[i] != ' ')
    i = i - 1;
  if (str[i] == ' ')
    i = i + 1;
  k = 0;
  while (i < j)
    tmp[k++] = str[i++];
  j = 0;
  while (tab[j])
    tmp[k++] = tab[j++];
  tmp[k] = '\0';
  return (tmp);
}
