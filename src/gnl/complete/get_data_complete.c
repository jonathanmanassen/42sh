/*
** get_date_complete.c for 42sh in /home/manass_j/rendu/PSU_2015_42sh/bonus
** 
** Made by jonathan manassen
** Login   <manass_j@epitech.net>
** 
** Started on  Sat May 21 08:37:26 2016 jonathan manassen
** Last update Sat Jun  4 19:20:13 2016 jonathan manassen
*/

#include <dirent.h>
#include <stdlib.h>
#include <curses.h>
#include "my.h"
#include "./include/complete.h"

int	*get_hide(char **tab, char *str, int *hide, int *m)
{
  int	i;
  int	j;
  int	l;

  *m = 0;
  j = 0;
  i = -1;
  while (tab[++i])
    if (hidenp(str, tab[i], 0) == -1)
      hide[j++] = i;
  j = 0;
  l = my_strlen(str);
  while (--l > 0 && str[l] != '/' && str[l] != ' ')
    *m = *m + 1;
  return (hide);
}

char	*get_part_of_word(char *str, char **tab, t_coord c, int i)
{
  int	l;
  int	j;
  char	*tmp;

  l = my_strlen(str);
  while (--l > 0 && str[l] != '/' && str[l] != ' ');
  if ((tmp = malloc(sizeof(char*) * (c.i + l + 1))) == NULL)
    exit(0);
  j = 0;
  if (l > 0)
    {
      while (j <= l)
	{
	  tmp[j] = str[j];
	  j = j + 1;
	}
    }
  free(str);
  l = 0;
  while (l <= c.i + c.k)
    tmp[j++] = tab[i][l++];
  tmp[j] = '\0';
  return (tmp);
}

char	*get_word(char *str, int i, char **tab, int *j)
{
  int	k;
  char	*tmp;

  k = my_strlen(str);
  while (--k > 0 && str[k] != '/' && str[k] != ' ');
  if ((tmp = malloc(sizeof(char*) * (my_strlen(tab[i]) + k + 1))) == NULL)
    exit(0);
  *j = 0;
  if (k > 0)
    while (*j <= k)
      {
	tmp[*j] = str[*j];
	*j = *j + 1;
      }
  free(str);
  k = 0;
  while (tab[i][k])
    {
      tmp[*j] = tab[i][k];
      *j = *j + 1;
      k = k + 1;
    }
  tmp[*j] = '\0';
  return (tmp);
}
