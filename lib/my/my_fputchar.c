/*
** my_putchar.c for my_putchar in /home/mei_c/rendu/Piscine_C_J07/lib/my
** 
** Made by christophe mei
** Login   <mei_c@epitech.net>
** 
** Started on  Tue Oct  6 09:59:14 2015 christophe mei
** Last update Sat Apr  2 17:09:01 2016 christophe mei
*/

#include <unistd.h>

void	my_fputchar(int fd, char c)
{
  write(fd, &c, 1);
}
