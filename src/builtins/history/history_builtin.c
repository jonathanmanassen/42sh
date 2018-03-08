/*
** history_builtin.c for 42sh in /home/manass_j/rendu/PSU_2015_42sh
** 
** Made by jonathan manassen
** Login   <manass_j@epitech.net>
** 
** Started on  Sat May 28 16:05:27 2016 jonathan manassen
** Last update Sun Jun  5 22:38:54 2016 jonathan manassen
*/

#include <stdlib.h>
#include "my.h"
#include "./include/history.h"

int	check_history(char *word, char *comm)
{
  int	i;
  int	j;

  i = 0;
  j = 0;
  while (word[i] && word[i] == ' ')
    i = i + 1;
  while (word[i] && word[i] != '\t')
    i = i + 1;
  if (word[i] != '\0')
    i = i + 1;
  while (comm[j])
    {
      if (word[i] == comm[j])
	{
	  i = i + 1;
	  j = j + 1;
	}
      else
	return (-1);
    }
  return (i);
}

int	search_errors_history(char *str, int i, int *j, char **history)
{
  int	l;
  int	k;
  char	*tmp;

  *j = 0;
  while (history[*j])
    *j = *j + 1;
  while (str[i] && str[i] == ' ')
    i = i + 1;
  k = i;
  if (str[i] >= '0' && str[i] <= '9')
    return (-1);
  while (str[i] && str[i] != ' ')
    i = i + 1;
  if ((tmp = malloc(sizeof(char*) * (i - k + 1))) == NULL)
    exit(0);
  l = 0;
  while (k < i)
    tmp[l++] = str[k++];
  tmp[l] = '\0';
  k = *j;
  while (--k >= 0)
    if (check_history(history[k], tmp) != -1)
      return (k);
  return (-1);
}

char	*get_hist(char *str, int show)
{
  int	i;
  int	j;
  int	k;
  char	*tmp;

  i = 0;
  while (str[i] && str[i] == ' ')
    i = i + 1;
  while (str[i] && str[i] != '\t')
    i = i + 1;
  if (str[i] != '\0')
    i = i + 1;
  j = i;
  while (str[i])
    i = i + 1;
  if ((tmp = malloc(sizeof(char*) * (i - j + 1))) == NULL)
    exit(0);
  k = 0;
  while (j < i)
    tmp[k++] = str[j++];
  tmp[k] = '\0';
  if (show == 1)
    my_printf("%s\n", tmp);
  return (tmp);
}

int	is_number(char *str)
{
  int	i;

  i = 0;
  while (str[i])
    {
      if (str[i] >= '0' && str[i] <= '9')
	return (1);
      i = i + 1;
    }
  return (-1);
}

char	**launch_history(char *str, t_shrc *shrc, char **env, t_prog *prog)
{
  int	i;
  int	j;

  j = -1;
  if ((i = check_builtin(str, "history")) != -1)
    while (shrc->history[++j])
      my_printf("   %d\t%s\n", j, shrc->history[j]);
  if ((i = check_letter(str, '!')) != -1)
    {
      if ((i = search_errors_history(str, i, &j, shrc->history)) == -1)
	{
	  i = my_getnbr(str);
	  if (i < 0)
	    i = my_strlen_double_array(shrc->history) + i;
	  if (is_number(str) == -1)
	    i = -1;
	}
      if (i < j && i >= 0)
	env = start_exec(get_hist(shrc->history[i], 1), env, shrc, prog);
      else
	my_printf("%s: Event not found\n", str);
    }
  return (env);
}
