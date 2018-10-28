#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

//        NOM = SALEZ

//  !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
//pas de compilation s�par�e SVP (pour faciliter la correction)

typedef int T_Elt;
typedef struct maille
{
    T_Elt elt;
    struct maille *next;
}T_Maille;


/**
 * \brief Macrofonction vérifiant si une liste est vide ou non.
 * \param liste La liste concernée.
 * \author Nathan Salez
 * \version 1.0
 * \date 19/09/2018
 */
#define VIDE(liste) (liste==NULL)


/**
 * \brief Macrofonction retournant l'élément de la maille en tête de liste.
 * \param liste La liste concernée.
 * \author Nathan Salez
 * \version 1.0
 * \date 19/09/2018
 */
#define TETE(liste) (liste->elt)


/**
 * \brief Macrofonction retournant le reste de la liste l.
 * \param l La liste concernée.
 * \author Nathan Salez
 * \version 1.0
 * \date 19/09/2018
 */
#define RESTE(l) (l->next)

//vous pouvez inclure ici vos fonctions de gestion de liste chain�e (� partir de votre fichier liste.c)
T_Maille * creerMaille(T_Elt e,T_Maille * l)
{
    T_Maille * aux = (T_Maille *) malloc( sizeof(struct maille) );
    assert( aux != NULL);

    TETE(aux) = e;
    RESTE(aux) = l;

    return aux;
}

T_Maille * insererEltQueueListe(T_Elt e, T_Maille * liste)
{
    if( VIDE(liste) )
        return creerMaille(e,NULL);

    else    // Récursivité
    {
        if( VIDE(RESTE(liste)) )    // Cas trivial
        {
            RESTE(liste) = creerMaille(e, NULL);
            return liste;
        }
        else
        {
            insererEltQueueListe(e,RESTE(liste));   // Cas général de la récursivité.
            return liste;
        }
    }
}

void afficherElt(T_Elt e)
{
    printf("-->%d",e);
}

T_Maille * insererEltTeteListe(T_Elt e, T_Maille * liste)
{
    return creerMaille(e,liste);
}

/*************** UTILES POUR LES QUESTIONS 2 ET 3 ********************/

unsigned int nbrEltsListe(T_Maille * l)
{
    if( VIDE(l) ) return 0;     // Cas trivial

    return nbrEltsListe(RESTE(l)) +1;    // Cas général de la récursivité
}

T_Elt sommeEltsListe(T_Maille *l)
{
    if( VIDE(l) )
        return 0;
    else
        return TETE(l) + sommeEltsListe(RESTE(l));
}

T_Elt getElementByPosition(unsigned int pos, T_Maille * liste)
{
    if( pos == 0)
        return TETE(liste);
    else
        return getElementByPosition(pos-1,RESTE(liste));
}

void afficherListe(T_Maille * l)
{
    unsigned int nbElts = nbrEltsListe(l),i,j;
    for(i = 0; i < nbElts;i++)
    {
        for(j = 0; j < i; j++ )     // On affiche les espaces "de tabulation"
            printf("  ");

        afficherElt( getElementByPosition(i,l) );
        printf("\n");
    }

}
/********************* UTILES POUR LA QUESTION 4 *************************/
T_Maille * supprimerPremierElementListe(T_Maille * liste)
{
    if( VIDE(liste) )
        return NULL;
    else
    {
        if( VIDE(RESTE(liste)) )
        {
            free(liste);
            return NULL;
        }
        else
        {
            liste=RESTE(liste);
            return liste;
        }
    }
}

int estMembre(T_Maille * liste, T_Elt e)
{
    if( VIDE(liste) )
        return 0;
    else if( TETE(liste) == e )
        return 1;
    else
        return estMembre(RESTE(liste),e);
}

T_Maille * supprimerElementListe(T_Elt e, T_Maille * liste)
{
    // On veut supprimer toutes les occurences d'un élément.
    if( VIDE(liste) )   // Cas 1 : liste vide.
        return liste;

    if( estMembre(liste,e) == 1 )
    {
        RESTE(liste) = supprimerElementListe(e,RESTE(liste));   // Cas général de la récursivité => on supprime d'abord les <e> en fin de liste.

        if( e == TETE(liste) )      // Cas trivial de la récursivité
            return supprimerPremierElementListe(liste);

    }
    return liste;
}

T_Maille * copierListe(T_Maille * src)
{
    if(VIDE(src))
        return NULL;

    return creerMaille(TETE(src),copierListe(RESTE(src)));
}

/****************************************************************/


//QUESTION 1  //////////////////////////////////////////////////////
// A l'aide de l'entier v, on construit la liste chainée de la conjecture.
T_Maille *conjecture(T_Elt v)
{

    // Version itérative
    /*
    T_Maille *liste = NULL;
    if( v <= 0)         // Cas particulier 1 : on a un entier non pris en compte dans la conjecture.
        return liste;

    liste = insererEltTeteListe(v,liste);
    while( v != 1)
    {
        if( v % 2 == 0) // si V est paire alors V reçoit V/2
            v = v/2;
        else            // si V est impaire alors V reçoit (3*V)+1
            v = 3*v+1;
        liste = insererEltQueueListe(v,liste);
    }
    return liste;
     */

    // Version récursive
    if( v <= 0)
        return NULL;

    if( v == 1)
    {
        return insererEltQueueListe(1,NULL);
    }

    if( v % 2 == 0) // si V est paire alors V reçoit V/2
        return insererEltTeteListe(v,conjecture(v/2));
    else            // si V est impaire alors V reçoit (3*V)+1
        return insererEltTeteListe(v,conjecture(3*v+1));
}

//QUESTIONS 2 et 3 //////////////////////////////////////////////////////
int nbElementsEtSomme(T_Maille *L,int *S)
{
    *S = sommeEltsListe(L);
    return nbrEltsListe(L);
}

//QUESTION 4     //////////////////////////////////////////////////////
T_Maille *supprElementsPaires(T_Maille *L)
{

    T_Maille * listeRetour = NULL;
    if ( VIDE(L) )
        return NULL;

    do {
        if( TETE(L)%2 == 1)
            listeRetour = insererEltQueueListe(TETE(L), listeRetour);
        L = supprimerPremierElementListe(L);
    }while( !VIDE(L) );

    return listeRetour;
}

int main() {
    T_Maille *L = NULL;
    int choix, Somme = 0, N;
    T_Elt v;
    do {

        printf(" \n\n\n Exo 1");
        printf("\n 1 : saisir une valeur puis construire la conjecture tcheque sous forme de liste chainee");
        printf("\n 2 : afficher le nombre d'elements et la somme des �l�ments de la liste conjecturee");
        printf("\n 3 : eliminer les valeurs paires de la liste");
        printf("\n 4 : afficher la liste ");

        printf("\n votre choix ");


        scanf("%d", &choix);

        switch (choix) {
            case 1 :
                printf("\n saisissez votre valeur de d�part SVP : ");
                scanf("%d", &v);
                L=conjecture(v);
                break;
            case 2 :
                N=nbElementsEtSomme(L,&Somme);
                printf("\n Nb elements = %d -- Somme = %d",N,Somme);
                break;
            case 3 :
                L=supprElementsPaires(L);

                break;
            case 4 :
                afficherListe(L);
                break;

        }
    } while (choix != 0);

    return 0;
}


