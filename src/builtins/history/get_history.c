/*
** get_history.c for 42sh in /home/manass_j/rendu/PSU_2015_42sh/bonus
** 
** Made by jonathan manassen
** Login   <manass_j@epitech.net>
** 
** Started on  Sat May 21 04:07:18 2016 jonathan manassen
** Last update Sat Jun  4 19:11:25 2016 jonathan manassen
*/

#include <stdlib.h>
#include "my.h"
#include "./include/history.h"

char		*get_save_history(char *str, int *hist, int *k)
{
  int		i;
  static char	*save;

  if (save == NULL)
    {
      if ((save = malloc(sizeof(char*) * (my_strlen(str) + 1))) == NULL)
	exit(0);
      i = -1;
      while (str[++i])
	save[i] = str[i];
      save[i] = '\0';
    }
  if (*hist == 0)
    {
      free(str);
      if ((str = malloc(sizeof(char*) * (my_strlen(save) + 1))) == NULL)
	exit(0);
      i = -1;
      while (save[++i])
	str[i] = save[i];
      *k = i;
      str[i] = '\0';
      save = NULL;
    }
  return (str);
}

char	*get_str_history(char **history, char *str, int i, int *k)
{
  int	j;

  if (history[i] != NULL)
    str = get_hist(history[i], 0);
  j = 0;
  while (str[j])
    j = j + 1;
  *k = j;
  if (j < 0)
    *k = 0;
  return (str);
}

char	*get_history(char *str, char **history, int *hist, int *k)
{
  int	i;
  int	j;

  str = get_save_history(str, hist, k);
  if (*hist == 0)
    return (str);
  i = -1;
  while (history[++i]);
  if (*hist > i)
    {
      if (*hist > 0)
	*hist = *hist - 1;
      return (str);
    }
  j = *hist;
  while (j-- > 0)
    i = i - 1;
  str = get_str_history(history, str, i, k);
  return (str);
}
