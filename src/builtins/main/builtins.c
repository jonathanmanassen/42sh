/*
** builtins.c for minishell1 in /home/manass_j/rendu/PSU_2015_minishell1
** 
** Made by jonathan manassen
** Login   <manass_j@epitech.net>
** 
** Started on  Tue Jan 12 17:17:02 2016 jonathan manassen
** Last update Sun Jun  5 22:26:49 2016 jonathan manassen
*/

#include <limits.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "my.h"

extern int	leave;

int	check_letter(char *str, char c)
{
  int	i;

  i = 0;
  while (str[i] && str[i] == ' ')
    i = i + 1;
  if (str[i] == c)
    return (i);
  return (-1);
}

int	check_builtin(char *word, char *comm)
{
  int	i;
  int	j;

  i = 0;
  j = 0;
  while (word[i] && word[i] == ' ')
    i = i + 1;
  while (word[i] && comm[j])
    {
      if (word[i] == comm[j])
	{
	  i = i + 1;
	  j = j + 1;
	}
      else
	return (-1);
    }
  if ((word[i] == '\0' || word[i] == ' ') && comm[j] == '\0')
    return (i);
  return (-1);
}

int	launch_exit(char *str, int i, t_prog *prog)
{
  int	j;

  if ((i = (check_builtin(str, "exit"))) != -1)
    {
      while (str[i])
	{
	  if ((str[i] < '0' || str[i] > '9') && str[i] != ' ' && str[i] != '-')
	    return (-1);
	  if (str[i] == '-' && (str[i + 1] < '0' || str[i + 1] > '9'))
	    return (-1);
	  if (str[i] >= '0' && str[i] <= '9')
	    if (str[i + 1] < '0' || str[i + 1] > '9')
	      if (str[i + 1] != '\0' && check_str_space(str, i + 1) == 0)
		return (-1);
	  i = i + 1;
	}
      if (check_str_space(str, check_builtin(str, "exit") + 1) == 1)
	return (prog->work);
      j = my_getnbr(str);
      return (j);
    }
  return (prog->quit);
}

void	launch_env(char *str, char **env)
{
  int	i;

  i = 0;
  if (check_builtin(str, "env") != -1)
    {
      while (env[i])
	{
	  my_printf("%s\n", env[i]);
	  i = i + 1;
	}
    }
}
