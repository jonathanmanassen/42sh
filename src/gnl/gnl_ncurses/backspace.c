/*
** backspace.c for 42sh in /home/manass_j/rendu/PSU_2015_42sh
** 
** Made by jonathan manassen
** Login   <manass_j@epitech.net>
** 
** Started on  Sat Jun  4 19:40:22 2016 jonathan manassen
** Last update Sat Jun  4 20:00:16 2016 jonathan manassen
*/

#include <stdlib.h>
#include "my.h"

char	*backspace(char c, char *str, int *i, int *curpos)
{
  char	*tmp;
  int	j;

  if (c == 127 && str != NULL && *curpos > 0)
    {
      if ((tmp = malloc(sizeof(char*) * my_strlen(str))) == NULL)
	exit(0);
      j = -1;
      while (++j < *i - (*i - *curpos) - 1)
	tmp[j] = str[j];
      while (str[++j])
	tmp[j - 1] = str[j];
      tmp[j - 1] = '\0';
      *i = *i - 1;
      *curpos = *curpos - 1;
      free(str);
      return (tmp);
    }
  return (str);
}

char	*alt_backspaces(char *str, int *i, int *curpos)
{
  int	j;

  str = backspace(127, str, i, curpos);
  j = *i - (*i - *curpos) - 1;
  while (*curpos > 0 && ((str[j] >= 'a' && str[j] <= 'z') ||
			 (str[j] >= 'A' && str[j] <= 'Z') ||
			 (str[j] >= '0' && str[j] <= '9')))
    {
      str = backspace(127, str, i, curpos);
      j = *i - (*i - *curpos) - 1;
    }
  return (str);
}
