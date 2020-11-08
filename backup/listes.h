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


#endif
