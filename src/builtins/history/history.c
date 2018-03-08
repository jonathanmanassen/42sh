/*
** history.c for 42sh in /home/manass_j/rendu/PSU_2015_42sh
** 
** Made by jonathan manassen
** Login   <manass_j@epitech.net>
** 
** Started on  Fri May 20 21:36:13 2016 jonathan manassen
** Last update Sat Jun  4 17:36:14 2016 jonathan manassen
*/

#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include "my.h"
#include "./include/history.h"

void	save_history(char **history)
{
  int	fd;
  int	i;

  i = 0;
  if (history != NULL && history[0] != NULL &&
      isatty(0) == 1 && isatty(1) == 1)
    {
      if ((fd = open(".history", O_CREAT | O_TRUNC | O_RDWR, 0644)) == -1)
	return;
      while (history[i])
	{
	  write(fd, history[i], my_strlen(history[i]));
	  write(fd, "\n", 1);
	  i = i + 1;
	}
    }
}

char	**move_back_double_array(char **env, int j, int k, int l)
{
  char	**tmp;

  while (env[j])
    j = j + 1;
  if ((tmp = malloc(sizeof(char**) * (j + 2))) == NULL)
    exit(0);
  j = -1;
  while (env[++j])
    {
      if (++l >= 0)
	{
	  k = -1;
	  while (env[j][++k]);
	  if ((tmp[l] = malloc(sizeof(char*) * (k + 1))) == NULL)
	    exit(0);
	  k = -1;
	  while (env[j][++k])
	    tmp[l][k] = env[j][k];
	  tmp[l][k] = '\0';
	}
      free(env[j]);
    }
  tmp[l + 1] = NULL;
  free(env);
  return (tmp);
}

char	*get_str(int nb)
{
  char	*str;
  int	i;
  int	tmp;

  tmp = nb;
  i = 0;
  while (tmp > 0)
    {
      tmp = tmp / 10;
      i = i + 1;
    }
  tmp = i;
  i = i - 1;
  if ((str = malloc(sizeof(char*) * (i + 1))) == NULL)
    exit(0);
  while (i >= 0)
    {
      str[i] = nb % 10 + '0';
      nb = nb / 10;
      i = i - 1;
    }
  str[tmp] = '\0';
  return (str);
}

char		**realloc_history(char **history, char *str, int k)
{
  int		i;
  int		j;

  if (str == NULL || str[0] == '\0' || str[0] == '!')
    return (history);
  i = 0;
  while (history[i])
    i = i + 1;
  if (i >= 1000)
    history = move_back_double_array(history, 0, 0, -2);
  if (i >= 1000)
    i = 999;
  else
    history = my_realloc_double_array(history, 0, 0);
  if ((history[i] = malloc(sizeof(char*) * (my_strlen(str) + k + 1))) == NULL)
    exit(0);
  j = 0;
  if (k != 0)
    history[i] = put_time_in_history(history[i], &j, 0);
  k = 0;
  while (str[k])
    history[i][j++] = str[k++];
  history[i][j] = '\0';
  history[i + 1] = NULL;
  return (history);
}

char	**init_history(void)
{
  char	**history;
  char	*str;
  int	fd;

  if ((history = malloc(sizeof(char**) * 1)) == NULL)
    exit(0);
  history[0] = NULL;
  if ((fd = open(".history", O_RDONLY)) != -1)
    {
      while ((str = get_next_line(fd)) != NULL)
	history = realloc_history(history, str, 0);
    }
  return (history);
}
