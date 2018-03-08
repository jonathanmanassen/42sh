/*
** init.c for 42sh in /home/manass_j/rendu/PSU_2015_42sh
** 
** Made by jonathan manassen
** Login   <manass_j@epitech.net>
** 
** Started on  Tue May 31 17:34:12 2016 jonathan manassen
** Last update Sat Jun  4 19:10:03 2016 jonathan manassen
*/

#include <stdlib.h>
#include "my.h"
#include "./include/misc.h"

void	init_structs(t_prog *prog, t_shrc *shrc)
{
  if ((shrc->set = malloc(sizeof(char**) * 1)) == NULL)
    exit(0);
  shrc->set[0] = NULL;
  shrc->history = init_history();
  shrc->alias = init_alias(-1);
  prog->quit = -2;
  prog->work = 0;
}
