/*
** is_printable.c for 42sh in /home/manass_j/rendu/PSU_2015_42sh
** 
** Made by jonathan manassen
** Login   <manass_j@epitech.net>
** 
** Started on  Tue May 31 16:52:59 2016 jonathan manassen
** Last update Sat Jun  4 21:51:34 2016 jonathan manassen
*/

#include <ncurses/curses.h>
#include "my.h"
#include "./include/gnl_ncurses.h"

extern int	key;

int	is_printable_3(char c, char **str, int curpos[2], int *i)
{
  if (c == 127)
    {
      if (*i == 0)
	*str = backspace(c, *str, &curpos[0], &curpos[1]);
      else
	*str = alt_backspaces(*str, &curpos[0], &curpos[1]);
      *i = 0;
    }
  else if ((*i == 91 || *i == 53 || *i == 51) && (c >= 65 && c <= 68))
    {
      key = c - 64;
      key = ((*i == 53 || *i == 51) && key > 2) ? key + 2 : key;
      *i = 0;
    }
  else
    return (0);
  return (1);
}

int	is_printable_2(char c, char **str, int curpos[2], int *i)
{
  if (*i == 27 && c != 127)
    *i = c;
  else if (*i == 'O')
    {
      if (c == 70 && curpos[1] < curpos[0])
	curpos[1] = curpos[0];
      else if (c == 72)
	curpos[1] = 0;
      *i = 0;
    }
  else if (*i == 51 && c == 126)
    {
      if (curpos[1] < curpos[0])
	{
	  curpos[1] = curpos[1] + 1;
	  *str = backspace(127, *str, &curpos[0], &curpos[1]);
	}
      *i = 0;
    }
  else
    return (0);
  return (1);
}

int	is_printable(char c, char **str, int curpos[2])
{
  static int i;

  if (is_printable_2(c, str, curpos, &i) == 1);
  else if (is_printable_3(c, str, curpos, &i) == 1);
  else if (i == 49 || i == 59 || i == 79 || i == 91 || c == 91 || c == 27)
    i = c;
  else if (c >= 32 && c <= 126)
    {
      i = 0;
      return (1);
    }
  else
    i = 0;
  return (0);
}
