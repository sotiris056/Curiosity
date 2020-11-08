#ifndef LISTES_H
#define LISTES_H

#define eprintf(...) fprintf (stderr, __VA_ARGS__)

/*
 * Pour réaliser des tests de performance, désactiver tous les affichages en 
 * redéfinissant les fonctions principales (décommenter).
 */
// #define printf(fmt, ...) (0)
// #define eprintf(fmt, ...) (0)
// #define putchar(c) (0)



extern bool silent_mode;



struct cellule {
    char   command;
	char   valeur[3]; //Utilisé pour stocker des valeurs superieurs à 9 dans la pile.
	int    indice; //Utilisé dans la pile: L'indice est fixé à 0 si la valeur stocké est inferieure ou egale à 9, à 1 si elle la valeur stocké est superieure à 9.
    /* vous pouvez rajouter d'autres champs ici */
    struct cellule *suivant;
};
typedef struct cellule cellule_t;

struct sequence {
    cellule_t *tete;
};
typedef struct sequence sequence_t;

sequence_t * creer_pile();

void ajout_en_queue(sequence_t * seq, char c);

void ajout_en_tete(sequence_t * seq, char c);

cellule_t* nouvelleCellule (void);

void detruireCellule (cellule_t*);

void conversion (char *texte, sequence_t *seq);

void afficher (sequence_t* seq);

//Acte II

sequence_t * creer_pile();

bool est_vide(sequence_t * pile);

void empiler (sequence_t * pile, char c);

void empiler_str(sequence_t * pile, char * c);

char depiler (sequence_t * pile);

void afficher_pile(sequence_t * pile);

int longueur(sequence_t * seq);

#endif
