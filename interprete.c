#include <stdio.h>
#include <stdbool.h>
#include <assert.h>
#include <stdlib.h>
#include <ctype.h>
#ifdef NCURSES
#include <ncurses.h>
#endif
#include "listes.h"
#include "curiosity.h"


/*
 *  Auteur(s) :
 *  Date :
 *  Suivi des Modifications :
 *
 */

void stop (void)
{
    char enter = '\0';
    printf ("Appuyer sur entrée pour continuer...\n");
    while (enter != '\r' && enter != '\n') { enter = getchar(); }
}



int interprete (sequence_t* seq, bool debug)
{
    // Version temporaire a remplacer par
    //  - une lecture des commandes dans la liste chainee
    // suivie par
    //  - une interpretation des commandes lues (partie fournie)

    char commande;
	char valeur[10]; //Utilisé en acte II pour stocker dans la pile des valeurs superieurs à 9;
	int value; //Utilisé à partir de l'acte II pour les operations d'addition, soustraction et multiplication
	int compteur; //Utilisé en acte IV pour les blocs des commandes
    int size;
	cellule_t * cel = seq -> tete, * tmp;
	sequence_t * V, * F;
	sequence_t * pile = creer_pile(); //Utilisé à partir de l'acte II
	//sequence_t * pile_tmp = creer_pile();
    //debug = true; /* À enlever par la suite et utiliser "-d" sur la ligne de commandes */

    printf ("Programme:");
    afficher(seq);
    printf ("\n");
    if (debug) stop();
	
	V = (sequence_t *)malloc(sizeof(sequence_t));
	F = (sequence_t *)malloc(sizeof(sequence_t));
    V -> tete = NULL;
	F -> tete = NULL;
	
	commande = cel -> command;
    int ret;         //utilisée pour les valeurs de retour

    while (cel != NULL) 
    {
        switch (commande)
        {
            /* Ici on avance tout le temps, à compléter pour gérer d'autres commandes */

            case 'A':
            case 'a':
                ret = avance();
                if (ret == VICTOIRE)
				{
					seq -> tete = NULL;
					return VICTOIRE; /* on a atteint la cible */
				}
                if (ret == RATE)
				{
					seq -> tete = NULL;
					return RATE;     /* tombé dans l'eau ou sur un rocher */
				}
                break; /* à ne jamais oublier !!! */
            
            case 'G':
            case 'g':
                gauche();
                if (ret == VICTOIRE)
				{
					seq -> tete = NULL;
					return VICTOIRE; /* on a atteint la cible */
				}
                if (ret == RATE)
				{
					seq -> tete = NULL;
					return RATE;     /* tombé dans l'eau ou sur un rocher */
				}
                break; /* à ne jamais oublier !!! */

            case 'D':
            case 'd':
                droite();
                if (ret == VICTOIRE)
				{
					seq -> tete = NULL;
					return VICTOIRE; /* on a atteint la cible */
				}
                if (ret == RATE)
				{
					seq -> tete = NULL;
					return RATE;     /* tombé dans l'eau ou sur un rocher */
				}
                break; /* à ne jamais oublier !!! */
			
			case '0':
			case '1':
			case '2':
			case '3':
			case '4':
			case '5':
			case '6':
			case '7':
			case '8':
			case '9':
				empiler(pile, commande);
				afficher_pile(pile);
				break;
			
			case '+':
				value = depiler(pile) - 48;
				afficher_pile(pile);
				value = value + (depiler(pile) - 48);
				afficher_pile(pile);
				if (value > 9)
				{
					sprintf(valeur, "%d", value);
					empiler_str(pile, valeur);
				}
				else
				{
					value = value + 48; //On ajoute 48 qui est le code Ascii de 0, pour pouvoir stocker la valeur en tant que charactere dans la pile.
					empiler(pile, value);
				}
				afficher_pile(pile);
				break;
			
			case '-':
				value = depiler(pile) - 48;
				afficher_pile(pile);
				value = abs(value - (depiler(pile) - 48));
				afficher_pile(pile);
				if (value > 9)
				{
					sprintf(valeur, "%d", value);
					empiler_str(pile, valeur);
				}
				else
				{
					value = value + 48; //On ajoute 48 qui est le code Ascii de 0, pour pouvoir stocker la valeur en tant que charactere dans la pile.
					empiler(pile, value);
				}
				afficher_pile(pile);
				break;

			case '*':
				value = depiler(pile) - 48;
				afficher_pile(pile);
				value = value * (depiler(pile) - 48);
				afficher_pile(pile);
				if (value > 9)
				{
					sprintf(valeur, "%d", value);
					empiler_str(pile, valeur);
				}
				else
				{
					value = value + 48; //On ajoute 48 qui est le code Ascii de 0, pour pouvoir stocker la valeur en tant que charactere dans la pile.
					empiler(pile, value);
				}
				afficher_pile(pile);
				break;
				
			case 'p':
			case 'P':
				value = depiler(pile) - 48;
				pose(value);
				afficher_pile(pile);
				break;
			
			case 'm':
			case 'M':
				value = depiler(pile) - 48;
				value = mesure(value);
				empiler(pile, value + 48);
				afficher_pile(pile);
				break;
			
			case '{':
				compteur = 1;
				empiler(pile, commande);
				cel = cel -> suivant;
				commande = cel -> command;
				while (compteur != 0)
				{
					if (commande == '{')
					{
						compteur++;
					}
					if (commande == '}')
					{
						compteur--;
					}
					empiler(pile, commande);
					if (commande == '}' && compteur == 0)
					{
						break;
					}
					cel = cel -> suivant;
					commande = cel -> command;
				}
				afficher_pile(pile);
				break;
			
			case '?':
				compteur = 1;
				commande = depiler(pile);
				ajout_en_tete(F, commande);
				while (compteur != 0)
				{
					commande = depiler(pile);
					if (commande == '{')
					{
						compteur--;
					}
					if (commande == '}')
					{
						compteur++;
					}
					ajout_en_tete(F, commande);
				}
				compteur = 1;
				commande = depiler(pile);
				ajout_en_tete(V, commande);
				while (compteur != 0)
				{
					commande = depiler(pile);
					if (commande == '{')
					{
						compteur--;
					}
					if (commande == '}')
					{
						compteur++;
					}
					ajout_en_tete(V, commande);
				}
				printf("V = ");
				afficher_pile(V);
				printf("\nF = ");
				afficher_pile(F);
				printf("\nPile =");
				afficher_pile(pile);
				value = depiler(pile) - 48;
				printf("\nPile = ");
				afficher_pile(pile);
				
				//Suppression des acolades externes
				tmp = F -> tete;
				F -> tete = F -> tete -> suivant;
				detruireCellule(tmp);
				tmp = F -> tete;
				size = longueur(F);
				if (size >= 2)
				{
					while (tmp -> suivant -> suivant != NULL)
					{
						tmp = tmp -> suivant;
					}
					tmp -> suivant = NULL;
				}
				else if (size == 1)
				{
					F -> tete = NULL;
				}
				printf("\nF = ");
				afficher_pile(F);
				
				printf("\nV = ");
				afficher_pile(V);
				if (debug) stop();
				tmp = V -> tete;
				V -> tete = V -> tete -> suivant;
				detruireCellule(tmp);
				tmp = V -> tete;
				size = longueur(V);
				if (size >= 2)
				{
					while (tmp -> suivant -> suivant != NULL)
					{
						tmp = tmp -> suivant;
					}
					tmp -> suivant = NULL;
				}
				else if (size == 1)
				{
					V -> tete = NULL;
				}
				printf("\nV = ");
				afficher_pile(V);
				
				if (value == 0)
				{
					if (!est_vide(F))
					{
						//afficher_pile(F);
						V -> tete = NULL;
						compteur = interprete(F,debug);
					}
					//compteur = interprete(F,debug);
				}
				else
				{
					F -> tete = NULL;
					if (!est_vide(V))
					{
						//afficher_pile(V);
						compteur = interprete(V,debug);
					}
					//afficher_pile(V);
					//compteur = interprete(V,debug);
				}
				F -> tete = NULL;
				V -> tete = NULL;
				
				break;

            default:
                eprintf("Caractère inconnu: '%c'\n", commande);
        }
		cel = cel -> suivant;
		commande = cel -> command;

        /* Affichage pour faciliter le debug */
        afficherCarte();
        printf ("Programme:");
        afficher(seq);
        printf ("\n");
        if (debug) stop();
    }
    /* Si on sort de la boucle sans arriver sur la cible,
     * c'est raté :-( */

    return CIBLERATEE;
}
