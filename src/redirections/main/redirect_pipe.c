/*
** redirect_pipe.c for minishell2 in /home/manass_j/rendu/PSU_2015_minishell2
** 
** Made by jonathan manassen
** Login   <manass_j@epitech.net>
** 
** Started on  Mon Apr 11 19:18:39 2016 jonathan manassen
** Last update Sat Jun  4 18:40:36 2016 jonathan manassen
*/

#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include "my.h"
#include "./include/redirections.h"

void	close_fd(int fd[2], int fd2[2], int i, t_prog *prog)
{
  if (i == 1)
    {
      close(fd2[1]);
      dup2(fd2[0], 0);
      close(fd[0]);
      close(fd2[0]);
    }
  if (i == 2)
    {
      close(fd2[0]);
      dup2(fd2[1], 1);
      dup2(fd[0], 0);
      close(fd[0]);
      close(fd2[1]);
    }
  if (i == 3)
    {
      close(fd2[0]);
      (prog->k == 3) ? dup2(fd2[1], prog->fd) : dup2(fd2[1], 1);
      (prog->k == 1 || prog->k == 2) ? dup2(fd[0], prog->fd) : dup2(fd[0], 0);
      close(fd[0]);
      close(fd2[1]);
    }
}

void	launch_redirect_pipe(t_prog *prog)
{
  if (prog->k == 1 || prog->k == 2)
    dup2(prog->fd, 1);
  else if (prog->k == 3)
    dup2(prog->fd, 0);
}

int	check_ambiguous(char **str)
{
  int	j;
  int	k;

  j = -1;
  while (str[++j] != NULL)
    {
      k = -1;
      if (str[j] != NULL)
	while (str[j][++k])
	  if ((str[j][k] == '>' && str[j + 1] != NULL)  ||
	      (str[j][k] == '<' && j != 0))
	    {
	      my_printf("Ambiguous output redirect.\n");
	      return (-1);
	    }
    }
  return (j - 1);
}

int	find_redirect_pipe(char **str, t_prog *prog)
{
  int	i;
  int	j;

  if ((j = check_ambiguous(str)) == -1)
    return (-1);
  i = 0;
  if (check_redirections_syntax(str[j], &i) == -1)
    if (check_second_redirections_syntax(str[j], &i) == -1)
      return (-1);
  if (i == 0)
    prog->redirect = check_redirections(str[j], &i, -1, 0);
  else
    prog->redirect = check_second_redirections(str[j], &i);
  prog->k = i;
  if (prog->redirect != NULL)
    {
      if (prog->k == 1)
	prog->fd = open(prog->redirect, O_CREAT | O_RDWR | O_TRUNC, 0644);
      else if (prog->k == 2)
	prog->fd = open(prog->redirect, O_CREAT | O_RDWR | O_APPEND, 0644);
      else if (prog->k == 3)
	prog->fd = open(prog->redirect, O_RDONLY);
    }
  return (0);
}

int	check_if_redirection(char *str)
{
  int	i;

  i = -1;
  while (str[++i])
    if (str[i] == '>' || str[i] == '<')
      return (1);
  return (-1);
}
