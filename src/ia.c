/*
** ia.c for alum1 in /home/brout_m/rendu/projet/Prog_elem/CPE_2015_Allum1
** 
** Made by marc brout
** Login   <brout_m@epitech.net>
** 
** Started on  Wed Feb 10 16:15:38 2016 marc brout
** Last update Wed Feb 10 18:29:54 2016 marc brout
*/

#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include "allum.h"

int		one_thousand_match(int *tab, int h)
{
  int		line;
  int		nb;
  int		test;

  if ((test = is_it_over(0, tab, h)) >= 0)
    return (test);
  while ((line = (rand() % h + 1)) && !(tab[line]));
  nb = rand() % tab[line] + 1;
  tab[line] -= nb;
  if ((test = is_it_over(1, tab, h)) >= 0)
    return (test);
  while ((line = (rand() % h + 1)) && !(tab[line]));
  nb = rand() % tab[line] + 1;
  tab[line] -= nb;
  if ((test = is_it_over(0, tab, h)) >= 0)
    return (test);
  return (one_thousand_match(tab, h));
}

void		attrib_victory(t_ia *ia, int ret, int line, int nb)
{
  if (ret > ia->victories)
    {
      ia->victories = ret;
      ia->line = line;
      ia->nb = nb;
    }
}

char		calc_path_to_victory(t_ia *ia, int *allum, int h)
{
  int		*copy;
  int		ret;
  int		line;
  int		nb;
  int		matches;

  line = 0;
  ia->victories = 0;
  while (++line < h + 2 && !(nb = 0))
    while (++nb <= allum[line])
      {
	matches = 1000;
	ret = 0;
	while (--matches >= 0)
	  {
	    if (!(copy = copy_tab(allum, h)))
	      return (1);
	    copy[line] -= nb;
	    ret += one_thousand_match(copy, h);
	    free(copy);
	  }
	attrib_victory(ia, ret, line, nb);
      }
  return (0);
}

int		first_line(int *tab, int h)
{
  int		i;

  i = -1;
  while (++i < h + 2)
    if (tab[i] > 0)
      break;
  return (i);
}

char		ia_turn(char **tab, int *allum, int h)
{
  t_ia		ia;

  ia.line = first_line(allum, h);
  ia.nb = 1;
  ia.victories = 0;
  write(1, "\nAI's turn...\n", 14);
  if (calc_path_to_victory(&ia, allum, h))
    return (1);
  allum[ia.line] -= ia.nb;
  print_end_turn(0, ia.line, ia.nb);
  set_tab(tab, allum, h);
  show_tab(tab);
  if (show_loser(0, allum, h))
    return (2);
  return (0);
}
