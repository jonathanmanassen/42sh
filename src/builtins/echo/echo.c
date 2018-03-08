/*
** echo.c for 42sh in /home/meyrie_g/rendu/ProgElemB1/CPE_2015_Lemin
** 
** Made by Gabin MEYRIEUX-DREVET
** Login   <meyrie_g@epitech.net>
** 
** Started on  Mon Apr 18 17:13:57 2016 Gabin MEYRIEUX-DREVET
** Last update Sat Jun  4 17:35:34 2016 jonathan manassen
*/

#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <wait.h>
#include <signal.h>
#include "my.h"
#include "./include/echo.h"

char	*epur_str(char *str, int k)
{
  char	*src;
  int	i;
  int	j;

  if ((src = malloc(sizeof(char*) * (my_strlen(str) + 1))) == NULL)
    exit(0);
  j = -1;
  i = k;
  while (str[i] && str[i] == ' ')
    i = i + 1;
  while (str[i])
    {
      if (str[i] == ' ' && (str[i + 1] == '\0' || str[i + 1] == ' '));
      else
	src[++j] = str[i];
      i = i + 1;
    }
  src[j + 1] = '\0';
  return (src);
}

int	check_param_echo(char *word, char *comm, int k)
{
  int	i;
  int	j;

  i = 0;
  j = 0;
  while (word[i])
    {
      if (word[i] == comm[j])
	{
	  while (word[i] == comm[j])
	    {
	      i = i + 1;
	      j = j + 1;
	    }
	  if (j == my_strlen(comm))
	    return (i);
	  else
	    return (k);
	}
      i += 1;
    }
  return (k);
}

void	fork_echo(char *str, int fd[2], int i, int k)
{
  pid_t	pid;
  int	j;

  ((pid = fork()) == -1) ? exit(0) : 0;
  if (pid != 0)
    wait(&pid);
  else
    {
      dup_redirection(k, fd, NULL);
      if ((j = check_param_echo(str, "-n", i)) != i)
	my_printf("%s", epur_str(str, j));
      else
	my_printf("%s\n", epur_str(str, i));
      exit(0);
    }
  if (k > 0)
    close(fd[0]);
  if (k > 4)
    close(fd[1]);
}

void	launch_echo(char *str, t_prog *prog)
{
  int	i;
  int	k;
  int	fd[2];

  str = pars_simple_cote_str(str);
  if ((i = check_builtin(str, "echo")) != -1)
    {
      k = 0;
      check_redirections_execute(str, &k, fd);
      if (k == -1)
	prog->work = 1;
      fork_echo(str, fd, i, k);
    }
}
