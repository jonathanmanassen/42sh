/*
** change_env_check.c for minishell1 in /home/manass_j/rendu/PSU_2015_minishell1
** 
** Made by jonathan manassen
** Login   <manass_j@epitech.net>
** 
** Started on  Sun Jan 24 18:22:58 2016 jonathan manassen
** Last update Sat Jun  4 17:35:46 2016 jonathan manassen
*/

#include <stdlib.h>
#include <unistd.h>
#include "my.h"
#include "./include/env.h"

int	check_alphanumeric(char *str, int i, char *name, char c)
{
  int	j;

  while (str[++i] && str[i] == ' ');
  j = i;
  while (str[i] && str[i] != c && i < my_strlen(str))
    {
      if ((str[i] < '0' || str[i] > '9') && (str[i] < 'a' || str[i] > 'z') &&
	  (str[i] < 'A' || str[i] > 'Z') && str[i] != ' ')
	{
	  my_fprintf(2, "%s: Variable name must ", name);
	  if (j == i)
	    my_fprintf(2, "begin with a letter.\n");
	  else
	    my_fprintf(2, "contain alphanumeric characters.\n");
	  return (-1);
	}
      i = i + 1;
    }
  if (i == j && check_builtin(name, "setenv") == -1)
    {
      my_fprintf(2, "%s: Variable name must ", name);
      my_fprintf(2, "begin with a letter.\n");
      return (-1);
    }
  return (0);
}

int	check_correct_change(char *str, int i, char **env, int j)
{
  if (check_alphanumeric(str, i - 1, "setenv", ' ') == -1)
    return (-1);
  if (i > my_strlen(str) || str[i] == '\0')
    launch_env("env", env);
  if (i > my_strlen(str) || str[i] == '\0')
    return (-1);
  if (check_str_space(str, i) == 1)
    launch_env("env", env);
  while (str[i])
    {
      if (check_str_space(str, i) == 1)
	return (-1);
      j = 0;
      while (j++ < 2)
	{
	  while (str[i] == ' ' && str[i])
	    i = i + 1;
	  while (str[i] != ' ' && str[i])
	    i = i + 1;
	}
      if (check_str_space(str, i) == 0)
	write(2, "setenv: Too many arguments.\n", 28);
      return ((check_str_space(str, i) == 0) ? -1 : 0);
    }
  return (0);
}

char	*get_line_name(char *str, int j, int i)
{
  char	*name;

  if ((name = malloc(sizeof(char*) * (i - j + 1))) == NULL)
    exit(0);
  i = 0;
  while (str[j] != ' ' && str[j])
    name[i++] = str[j++];
  name[i] = '\0';
  return (name);
}

char	**check_realloc(char **env, int j)
{
  if (j == -1)
    {
      while (env[++j])
	j = j;
      env = my_realloc_double_array(env, 0, 0);
      env[j + 1] = NULL;
    }
  return (env);
}

char	**malloc_env(char **env, char *str, int i, int j)
{
  if (j != -1)
    free(env[j]);
  if ((env[j] = malloc(sizeof(char*) * (my_strlen(str) - i + 1))) == NULL)
    exit(0);
  return (env);
}
