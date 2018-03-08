/*
** show_alias.c for 42sh in /home/manass_j/rendu/PSU_2015_42sh
** 
** Made by jonathan manassen
** Login   <manass_j@epitech.net>
** 
** Started on  Thu Jun  2 15:55:52 2016 jonathan manassen
** Last update Sat Jun  4 17:35:07 2016 jonathan manassen
*/

#include <stdlib.h>
#include "my.h"
#include "./include/alias.h"

char	**put_tab_in_tabi(char **alias)
{
  char	**tab;
  int	i;
  int	j;

  i = 0;
  while (alias[i])
    i = i + 1;
  if ((tab = malloc(sizeof(char**) * (i + 1))) == NULL)
    exit(0);
  i = 0;
  while (alias[i])
    {
      j = -1;
      if ((tab[i] = malloc(sizeof(char*) * (my_strlen(alias[i]) + 1))) == NULL)
	exit(0);
      while (alias[i][++j])
	tab[i][j] = alias[i][j];
      tab[i][j] = '\0';
      i = i + 1;
    }
  tab[i] = NULL;
  return (tab);
}

char	**sort_alias(char **str, int i, int j, int k)
{
  char	*low;
  char	*low2;

  while (str[i + 2])
    {
      low = my_lowcase(str[i]);
      low2 = my_lowcase(str[k]);
      if (low[j] > low2[j])
	{
	  swap_str(str, i, k);
	  swap_str(str, i + 1, k + 1);
	}
      j = (low[j] == low2[j]) ? j + 1 : 0;
      if (j == 0)
	k = k + 2;
      if (str[k - 1] == NULL || str[k] == NULL)
	{
	  i = i + 2;
	  k = i + 2;
	}
      free(low);
      free(low2);
    }
  return (str);
}

void	show_alias(char **alias)
{
  char	**str;
  int	i;

  if (alias[0] == NULL)
    return;
  str = put_tab_in_tabi(alias);
  sort_alias(str, 0, 0, 2);
  i = 0;
  while (str[i])
    {
      my_printf("%s\t%s\n", str[i], str[i + 1]);
      free(str[i]);
      free(str[i + 1]);
      i = i + 2;
    }
  free(str);
}
