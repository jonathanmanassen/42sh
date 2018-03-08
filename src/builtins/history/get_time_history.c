/*
** get_time_history.c for 42sh in /home/manass_j/rendu/PSU_2015_42sh
** 
** Made by jonathan manassen
** Login   <manass_j@epitech.net>
** 
** Started on  Sat May 28 17:29:47 2016 jonathan manassen
** Last update Sat Jun  4 17:36:05 2016 jonathan manassen
*/

#include <stdlib.h>
#include <time.h>
#include "my.h"
#include "./include/history.h"

char	*get_minute(char *history, char *t, int *j)
{
  int	k;

  k = my_strlen(t);
  while (++k <= 2)
    {
      history[*j] = '0';
      *j = *j + 1;
    }
  k = 0;
  while (t[k])
    {
      history[*j] = t[k++];
      *j = *j + 1;
    }
  history[*j] = '\t';
  *j = *j + 1;
  free(t);
  return (history);
}

char	*put_time_in_history(char *history, int *j, int k)
{
  struct tm	*tm;
  time_t	now;
  char		*t;

  now = time(0);
  tm = gmtime(&now);
  t = get_str(tm->tm_hour + 2);
  while (t[k])
    {
      history[*j] = t[k++];
      *j = *j + 1;
    }
  free(t);
  history[*j] = ':';
  *j = *j + 1;
  t = get_str(tm->tm_min);
  history = get_minute(history, t, j);
  return (history);
}
