/*
** error.c for minishell1 in /home/manass_j/rendu/PSU_2015_minishell1
** 
** Made by jonathan manassen
** Login   <manass_j@epitech.net>
** 
** Started on  Sun Jan 24 19:29:10 2016 jonathan manassen
** Last update Sun Jun  5 22:38:29 2016 jonathan manassen
*/

#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include "my.h"
#include "./include/misc.h"

void	write_error(char *exe, int fd)
{
  if (check_all_builtins(exe) == 1)
    {
      my_fprintf(2, exe);
      if (errno == EACCES)
	my_fprintf(2, ": Permission denied.\n");
      else if (errno == ENOEXEC)
	my_fprintf(2, ": Exec format error. Binary file not executable.\n");
      else
	my_fprintf(2, ": Command not found.\n");
      write(fd, "1", 1);
    }
}

int	check_all_builtins(char *str)
{
  if (check_builtin(str, "echo") != -1 || check_builtin(str, "alias") != -1 ||
      check_builtin(str, "setenv") != -1 || check_builtin(str, "env") != -1 ||
      check_builtin(str, "history") != -1 || check_letter(str, '!') != -1 ||
      check_builtin(str, "unsetenv") != -1 ||
      check_builtin(str, "unalias") != -1 || check_builtin(str, "set") != -1 ||
      check_builtin(str, "exit") != -1 || check_builtin(str, "unset") != -1 ||
      check_builtin(str, "cd") != -1)
    return (0);
  return (1);
}

int	test_invalid_null_redirect(char *str)
{
  int	i;

  i = -1;
  while (str[++i] && str[i] == ' ');
  if (str[i] == '>' || str[i] == '<')
    i = (str[i + 1] == '>' || str[i + 1] == '<') ? i + 1 : i;
  else
    return (0);
  while (str[++i] && str[i] != ' ');
  if (check_str_space(str, i) == 1)
    return (1);
  return (0);
}

int	test_invalid_null(char *str)
{
  int	i;

  i = -1;
  while (str[++i] && str[i] == ' ');
  if (str[i] == '|')
    return (1);
  i = -1;
  while (str[++i])
    if (str[i] == '|' && (check_str_space(str, i + 1)) == 1)
      return (1);
  i = -1;
  while (str[++i])
    if (str[i] == '|')
      {
	while (str[++i] && str[i] == ' ');
	if (str[i] == '|')
	  {
	    while (str[++i] && str[i] == ' ')
	      if (str[i] == '|')
		return (1);
	  }
      }
  return (test_invalid_null_redirect(str));
}
