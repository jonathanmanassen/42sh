/*
** complete.h for 42sh in /home/manass_j/rendu/PSU_2015_42sh
** 
** Made by jonathan manassen
** Login   <manass_j@epitech.net>
** 
** Started on  Sat Jun  4 04:47:51 2016 jonathan manassen
** Last update Sat Jun  4 18:24:37 2016 jonathan manassen
*/

#ifndef COMPLETE_H_
# define COMPLETE_H_

typedef struct	s_coord
{
  int		i;
  int		k;
}		t_coord;

int	*get_hide(char**, char*, int*, int*);
int	hidenp(char*, char*, int);
char	*get_part_of_word(char*, char**, t_coord, int);
int	write_stat(char*, int);
char	**no_options(int, char*);
char	*get_word(char*, int, char**, int*);
int	count_files(char*);
char	*get_name_opendir(char*, int*);
char	*get_name_opendir_second(char*, int*);
char	*get_name_opendir_current(char*, int*);
char	*change_str_for_stat(char*, char*, int);
char	**get_ls(char**, char*, DIR*, int);

#endif /* !COMPLETE_H_ */
