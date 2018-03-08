/*
** get_next_line.c for get_next_line in /home/mei_c/rendu/CPE/CPE_2015_getnextline
** 
** Made by christophe mei
** Login   <mei_c@epitech.net>
** 
** Started on  Thu Jan  7 14:35:11 2016 christophe mei
** Last update Sun Jun  5 21:46:00 2016 jonathan manassen
*/

#include <sys/ioctl.h>
#include <stdio.h>
#include <curses.h>
#include <stdlib.h>
#include <unistd.h>
#include "my.h"
#include "./include/gnl_ncurses.h"

int	key;

int	is_alphanumeric(char *str, int i)
{
  if (key == 6)
    i = i - 1;
  if (i < 0)
    return (0);
  if ((str[i] >= 'A' && str[i] <= 'Z') ||
      (str[i] >= 'a' && str[i] <= 'z') ||
      (str[i] >= '0' && str[i] <= '9'))
    return (1);
  return (0);
}

char	*special_chars(char *str, int curpos[2], int fd, char c)
{
  if (c == 4 && str[0] == '\0')
    return (NULL);
  else if (c == 4)
    {
      my_putchar('\n');
      launch_write_ls(no_options(count_files(str), str), str, -1, 0);
    }
  if (c == 9)
    str = auto_complete(str, &curpos[0], &curpos[1]);
  if (c == 12)
    my_printf("\e[0;0H\e[2J");
  if (c == 16)
    key = 1;
  if (curpos[0] == 0)
    str[0] = '\0';
  if (curpos[0] != 0)
    str = my_realloc_ncurses(str);
  if (c == 13)
    {
      if (fd == 0)
	my_printf("\n");
      return (str);
    }
  return (str);
}

char	*keypad_func(char *str, char **history, int *hist, int curpos[2])
{
  if (key != 0)
    {
      if (key == 1 || key == 2)
	*hist = (key == 1) ? *hist + 1 :  *hist - 1;
      *hist = (*hist < 0) ? 0 : *hist;
      if ((key == 4 || key == 6) && curpos[1] > 0)
	curpos[1] = curpos[1] - 1;
      else if ((key == 3 || key == 5) && curpos[1] < curpos[0])
	curpos[1] = curpos[1] + 1;
      else if (key == 1 || key == 2)
	{
	  str = get_history(str, history, hist, &curpos[0]);
	  curpos[1] = curpos[0];
	}
      if (key == 5)
	while (curpos[1] < curpos[0] &&
	       is_alphanumeric(str, curpos[0] - (curpos[0] - curpos[1])) == 1)
	  curpos[1] = curpos[1] + 1;
      else if (key == 6)
	while (curpos[1] > 0 &&
	       is_alphanumeric(str, curpos[0] - (curpos[0] - curpos[1])) == 1)
	  curpos[1] = curpos[1] - 1;
      key = 0;
    }
  return (str);
}

char	*get_next_line_ncurses(const int fd, char **env, char **history)
{
  char	*str;
  char	c;
  int	curpos[2];
  int	hist;

  str = init_get_next_line(curpos, &hist);
  while (read(fd, &c, 1) > 0)
    {
      if ((str = special_chars(str, curpos, fd, c)) == NULL)
	return (NULL);
      if (c == 13)
	if (fd == 0)
	  return (str);
      if (is_printable(c, &str, curpos) == 1)
	str = put_char_in_str(str, c, &curpos[0], &curpos[1]);
      str = keypad_func(str, history, &hist, curpos);
      show_get_next_line(str, env, fd, curpos);
    }
  return ((curpos[0] == 0) ? NULL : str);
}
