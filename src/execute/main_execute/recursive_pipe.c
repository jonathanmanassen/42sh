/*
** recursive_pipe.c for 42sh in /home/manass_j/rendu/PSU_2015_42sh
** 
** Made by jonathan manassen
** Login   <manass_j@epitech.net>
** 
** Started on  Sat May 21 03:31:29 2016 jonathan manassen
** Last update Sat Jun  4 17:36:47 2016 jonathan manassen
*/

#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <wait.h>
#include <signal.h>
#include "my.h"
#include "./include/main_execute.h"

void	launch_recursive(char ***str, t_prog *prog, char **env, t_shrc *shrc)
{
  if (str[prog->i] != NULL && str[prog->i + 1] != NULL
      && str[prog->i + 2] != NULL)
    {
      prog->i = prog->i + 1;
      recursive(str, prog, env, shrc);
    }
}

void	recursive(char ***str, t_prog *prog, char **env, t_shrc *shrc)
{
  pid_t	pid;
  int	*fd2;
  int	i;

  if ((fd2 = malloc(sizeof(int*) * 2)) == NULL)
    exit(0);
  close(prog->pfd[1]);
  if (pipe(fd2) == -1 || (pid = fork()) == -1)
    return;
  if (pid != 0)
    {
      prog->pfd = fd2;
      launch_recursive(str, prog, env, shrc);
      close_fd(prog->pfd, fd2, 1, prog);
      launch_redirect_pipe(prog);
      check_env_function(str[prog->i + 1], prog, env, shrc);
      exit(0);
    }
  else
    {
      i = (str[prog->i + 1] == NULL) ? 3 : 2;
      close_fd(prog->pfd, fd2, i, prog);
      check_env_function(str[prog->i], prog, env, shrc);
      exit(0);
    }
}
