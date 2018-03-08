/*
** get_execute.h for 42sh in /home/manass_j/rendu/PSU_2015_42sh/src/execute/get_execute
** 
** Made by jonathan manassen
** Login   <manass_j@epitech.net>
** 
** Started on  Fri Jun  3 21:18:07 2016 jonathan manassen
** Last update Fri Jun  3 23:16:11 2016 jonathan manassen
*/

#ifndef GET_EXECUTE_H_
# define GET_EXECUTE_H_

typedef struct	s_coord
{
  int		i;
  int		k;
}		t_coord;

char	*launch_turn_alias(t_shrc*, char*, t_prog*);

#endif /* !GET_EXECUTE_H_ */
