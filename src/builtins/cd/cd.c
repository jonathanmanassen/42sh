/*
** cd.c for minishell2 in /home/manass_j/rendu/PSU_2015_minishell2
** 
** Made by jonathan manassen
** Login   <manass_j@epitech.net>
** 
** Started on  Sat Apr  9 19:40:02 2016 jonathan manassen
** Last update Sat Jun  4 17:35:24 2016 jonathan manassen
*/

#include <limits.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include "my.h"
#include "./include/cd.h"

extern int	leave;

char	*return_to_home(char **env)
{
  int	i;
  int	j;
  int	k;
  char	*path;

  i = 0;
  j = 5;
  if ((k = find_line_in_env("HOME", env)) != -1)
    {
      if ((path = malloc(sizeof(char*) * (my_strlen(env[k]) - 4))) == NULL)
	exit(0);
      while (env[k][j])
	path[i++] = env[k][j++];
    }
  path[i] = '\0';
  return (path);
}

char	*hard_cd(char *str, int i, int j)
{
  char	*path;

  if ((path = malloc(sizeof(char*) * (my_strlen(str) - i))) == NULL)
    exit(0);
  while (str[i] != ' ' && str[i] != '\0')
    path[++j] = str[i++];
  path[j + 1] = '\0';
  return (path);
}

char	*find_path(char *str, int i, char **env, char *pwd)
{
  char	*path;
  int	j;

  j = -1;
  if ((check_str_space(str, i) == 1 ||
       (str[i] == '~' && check_str_space(str, i + 1) == 1)) &&
      find_line_in_env("HOME", env) != -1)
    path = return_to_home(env);
  else if (str[i] == '-')
    {
      if (pwd == NULL)
	pwd = getcwd(NULL, PATH_MAX + 1);
      if ((path = malloc(sizeof(char*) * (my_strlen(pwd) + 1))) == NULL)
	exit(0);
      while (pwd[++j])
	path[j] = pwd[j];
      path[j] = '\0';
    }
  else
    path = hard_cd(str, i, j);
  return (path);
}

void		launch_cd(char *str, char **env, int *work)
{
  char		*path;
  int		i;
  static char	*pwd;

  if ((i = check_builtin(str, "cd")) != -1)
    {
      while (str[i] != '\0' && str[i] == ' ')
	i = i + 1;
      path = find_path(str, i, env, pwd);
      pwd = getcwd(NULL, PATH_MAX + 1);
      if (chdir(path) == -1)
	{
	  if (errno == EACCES)
	    my_printf("%s: Permission denied.\n", path);
	  else if (errno == ENOTDIR)
	    my_printf("%s: Not a directory.\n", path);
	  else
	    my_printf("%s: No such file or directory.\n", path);
	  *work = 1;
	}
      free(path);
    }
}
