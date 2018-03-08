/*
** simple_cote.c for 42sh in 
** 
** Made by Gabin MEYRIEUX-DREVET
** Login   <meyrie_g@epitech.net>
** 
** Started on  Tue Apr 19 14:33:17 2016 Gabin MEYRIEUX-DREVET
** Last update Sat Jun  4 17:35:30 2016 jonathan manassen
*/

#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <wait.h>
#include <signal.h>
#include "my.h"
#include "./include/echo.h"

char	*delayed_str(char *str, int i)
{
  int	j;

  j = i - 1;
  while (str[++j])
    str[j] = str[j + 1];
  return (str);
}

char	*check_simple_cote(char *str, int i, int mod)
{
  int	j;

  j = i;
  while (str[j] && str[j] != 39)
    {
      if (str[j] == '\\' && mod == 1)
	{
	  str = delayed_str(str, j);
	  (str[j] == 'a') ? str[j] = '\a' : 0;
	  (str[j] == 'b') ? str[j] = '\b' : 0;
	  (str[j] == 't') ? str[j] = '\t' : 0;
	  (str[j] == 'n') ? str[j] = '\n' : 0;
	  (str[j] == 'v') ? str[j] = '\v' : 0;
	  (str[j] == 'f') ? str[j] = '\f' : 0;
	  (str[j] == 'r') ? str[j] = '\r' : 0;
	}
      else if (str[j] == '\\' && mod == 0)
	str = delayed_str(str, j);
      j += 1;
    }
  (str[j] == 39) ? str = delayed_str(str, j) : 0;
  return (str);
}

char	*pars_simple_cote_str(char *str)
{
  int	i;

  i = 0;
  while (str[i])
    {
      if (str[i] == 39)
	{
	  str = delayed_str(str, i);
	  str = check_simple_cote(str, i, 1);
	}
      i += 1;
    }
  str = check_simple_cote(str, 0, 0);
  return (str);
}
