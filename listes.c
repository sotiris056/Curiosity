#include <stdio.h>
#include <string.h>
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
	cel -> indice = 0;
	cel -> suivant = seq -> tete;
	seq -> tete = cel;
}

void ajout_en_queue(sequence_t * seq, char c)
{
	cellule_t * cel, * cel_cour;
    cel = nouvelleCellule();
    cel -> command = c;
    if (seq -> tete == NULL)
    {
        seq -> tete = cel;
    }
    else
    {
		cel_cour = seq -> tete;
        while (cel_cour -> suivant != NULL)
        {
			cel_cour = cel_cour -> suivant;
        }
        cel_cour -> suivant = cel;
    }
}

int longueur(sequence_t * seq)
{
	int l = 0;
	cellule_t * cel = seq -> tete;
	if (seq -> tete == NULL)
	{
		return 0;
	}
	while (cel != NULL)
	{
		l++;
		cel = cel -> suivant;
	}
	return l;
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
		if (texte[i] != ' ' && texte[i] != '\n')
		{
			ajout_en_queue(seq, texte[i]);
		}
    }
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

bool est_vide(sequence_t * pile)
{
	return pile -> tete == NULL;
}

void empiler (sequence_t * pile, char c)
{
	ajout_en_tete(pile, c);
}

void empiler_str(sequence_t * pile, char * c)
{
	cellule_t * cel = nouvelleCellule();
	strcpy(cel -> valeur, c);
	cel -> indice = 1;
	cel -> suivant = pile -> tete;
	pile -> tete = cel;
}

char depiler (sequence_t * pile)
{
	char ret;
	cellule_t * tmp;
	ret = pile -> tete -> command;
	tmp = pile -> tete -> suivant;
	pile -> tete -> suivant = NULL;
	pile -> tete = tmp;
	return ret;
}

void afficher_pile(sequence_t * pile)
{
	assert (pile); /* Le pointeur doit être valide */
	cellule_t * cel = pile -> tete;
	if (pile -> tete == NULL)
	{
		printf("La pile est vide.\n");
		return;
	}
	printf("Pile: ");
	while (cel != NULL)
	{
		if (cel -> indice == 0)
		{
			printf("%c ", cel -> command);
		}
		else
		{
			printf("%s ", cel -> valeur);
		}
		cel = cel -> suivant;
	}
}