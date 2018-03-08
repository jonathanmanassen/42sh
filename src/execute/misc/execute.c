/*
** execute.c for minishell1 in /home/manass_j/rendu/PSU_2015_minishell1
** 
** Made by jonathan manassen
** Login   <manass_j@epitech.net>
** 
** Started on  Fri Jan 15 16:18:17 2016 jonathan manassen
** Last update Sun Jun  5 21:05:02 2016 jonathan manassen
*/

#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include "my.h"
#include "./include/misc.h"

extern int	leave;

int	find_char(char *str, char c)
{
  int	i;

  i = 0;
  while (str[i])
    {
      if (str[i] == c)
	return (i);
      i = i + 1;
    }
  return (-1);
}

char	**get_basic_path(char **exe, char **env, int *j, char **path)
{
  if (exe[0][0] == '.' || path == NULL ||
      path[0][0] == '\0' || find_char(exe[0], '/') != -1)
    {
      *j = 0;
      if (execve(exe[0], exe, env) == -1 && exe[0][0] != '.' &&
	  find_line_in_env("PATH", env) == -1)
	*j = 1;
      if (find_line_in_env("PATH", env) == -1)
	{
	  if ((path = malloc(sizeof(char**) * 2)) == NULL)
	    exit(0);
	  if ((path[0] = malloc(sizeof(char*) * 9)) == NULL)
	    exit(0);
	  path[0] = "/usr/bin\0";
	  path[1] = NULL;
	}
    }
  return (path);
}

char	**search_path(char **my_env)
{
  char	**path;

  if ((find_line_in_env("PATH", my_env)) == -1)
    path = NULL;
  else
    path = get_path(my_env[find_line_in_env("PATH", my_env)]);
  return (path);
}

void	dup_redirection(int i, int fd[2], t_prog *prog)
{
  (i == 1 || i == 2) ? dup2(fd[0], 1) : 0;
  (i == 3) ? dup2(fd[0], 0) : 0;
  (i == 4) ? dup2(fd[1], 0) : 0;
  if (i >= 5)
    {
      dup2(fd[0], 1);
      dup2(fd[1], 0);
    }
  if (prog != NULL)
    close(prog->fd2[0]);
}

void	check_signal(pid_t pid, int *work)
{
  if (WIFSIGNALED(pid) == 1)
    {
      if (WTERMSIG(pid) == 11)
	my_printf("Segmentation fault\n");
      else if (WTERMSIG(pid) == 8)
	my_printf("Floating exception\n");
      *work = pid + 128;
    }
}
