/*
** my_putchar.c for my_putchar in /home/manass_j/rendu/Piscine_C_J07
** 
** Made by jonathan manassen
** Login   <manass_j@epitech.net>
** 
** Started on  Tue Oct  6 09:31:50 2015 jonathan manassen
** Last update Tue Jan 12 15:38:16 2016 jonathan manassen
*/

#include <unistd.h>

void	my_putchar(char c)
{
  write(1, &c, 1);
}
