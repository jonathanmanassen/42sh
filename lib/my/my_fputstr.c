/*
** my_putstr.c for d4ex3 in /home/mei_c/rendu/Piscine_C_J04
** 
** Made by christophe mei
** Login   <mei_c@epitech.net>
** 
** Started on  Thu Oct  1 11:49:58 2015 christophe mei
** Last update Sat Apr  2 17:09:11 2016 christophe mei
*/

#include <unistd.h>

int	my_fputstr(int fd, char *str)
{
  int	i;

  i = 0;
  while (str[i])
    i = i + 1;
  write(fd, str, i);
  return (0);
}
