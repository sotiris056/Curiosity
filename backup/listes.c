#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#ifdef NCURSES
#include <ncurses.h>
#endif
#include "listes.h"


/*
 *  Auteur(s) :
 *  Date :
 *  Suivi des Modifications :
 *
 */

bool silent_mode = false;

void ajout_en_tete(sequence_t * seq, char c)
{
    cellule_t * cel = nouvelleCellule();
    cel -> command = c;
    cel -> suivant = seq -> tete;
    seq -> tete = cel;
}

cellule_t* nouvelleCellule (void)
{
    cellule_t * cel = (cellule_t *)malloc(sizeof(cellule_t));
    cel -> suivant = NULL;
    return cel;
}

void detruireCellule (cellule_t * cel)
{
    free(cel);
}

void conversion (char *texte, sequence_t *seq)
{
  for (int i = 0; texte[i] != '\0'; i++)
  {
    ajout_en_tete(seq, texte[i]);
  }
  cellule_t *cel = nouvelleCellule();
  seq -> tete = cel;
  cel -> command = texte[0];
  cellule_t *cel_cour = cel;
  int i = 1;
  while (texte[i] != '\0')
  {
    cellule_t *nouv_cel = nouvelleCellule();
    nouv_cel -> command = texte[i];
    cel_cour -> suivant = nouv_cel;
    cel_cour = nouv_cel;
    i++;
  }
  cel_cour -> suivant = NULL;
}

void afficher (sequence_t* seq)
{
  assert (seq); /* Le pointeur doit être valide */
  cellule_t * cel = seq -> tete;
  if (seq -> tete == NULL)
  {
    printf("La liste des instructions pour le robot est vide.\n");
    return;
  }
  while (cel != NULL)
  {
	
    printf("%c", cel -> command);
    cel = cel -> suivant;
  }
}

/*Acte II : Creation d'une pile pour manipulation d'entiers*/

sequence_t * creer_pile()
{
  sequence_t * pile = (sequence_t *) malloc (sizeof(sequence_t));
  pile -> tete = NULL;
  return pile;
}

/*void empiler*/