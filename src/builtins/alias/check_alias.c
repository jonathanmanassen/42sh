/*
** check_alias.c for 42sh in /home/manass_j/rendu/PSU_2015_42sh
** 
** Made by jonathan manassen
** Login   <manass_j@epitech.net>
** 
** Started on  Tue May 24 15:49:02 2016 jonathan manassen
** Last update Sat Jun  4 19:01:11 2016 jonathan manassen
*/

#include <stdlib.h>
#include <unistd.h>
#include "my.h"
#include "./include/alias.h"

int	check_all_alias(int *a, int i, int k)
{
  int	j;

  j = 0;
  while (j < k - 1)
    {
      if (i == a[j])
	return (-1);
      j = j + 1;
    }
  return (1);
}

int	*realloc_int_tab(int *a, int j)
{
  int	*tmp;
  int	i;

  i = 0;
  while (a[i] != -1)
    i = i + 1;
  if ((tmp = malloc(sizeof(int*) * (i + 1))) == NULL)
    exit(0);
  i = 0;
  while (a[i] != -1)
    {
      tmp[i] = a[i];
      i = i + 1;
    }
  tmp[i] = j;
  tmp[i + 1] = -1;
  return (tmp);
}

char	*launch_turn_alias(t_shrc *shrc, char *str, t_prog *prog)
{
  int	i;
  int	j;
  int	k;
  int	*a;

  if ((a = malloc(sizeof(int*) * 1)) == NULL)
    exit(0);
  a[0] = i = k = -1;
  j = 0;
  while (i != j)
    {
      if (++k > 1)
	{
	  if (check_all_alias(a, i, k) == -1)
	    {
	      prog->work = 1;
	      my_fprintf(2, "Alias loop.\n");
	      return (NULL);
	    }
	}
      j = i;
      str = turn_str_into_alias(shrc->alias, str, &i, 0);
      a = realloc_int_tab(a, i);
    }
  return (str);
}
