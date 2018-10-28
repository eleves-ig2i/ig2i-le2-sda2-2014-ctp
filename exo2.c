//        NOM = SALEZ NATHAN

//  !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
//pas de compilation s�par�e SVP (pour faciliter la correction)


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#define MAX 10

//#define __DEBUG__
typedef enum {HAUT,DROITE,BAS,GAUCHE,FIN} T_Direction;  // pour la question 2


//macro fonctions pour les piles
#define pileVide(p) (p->Sp==0)
#define passerAuPremierFils(p,caseLaby) push(p,caseLaby)
#define passerAuFrereSuivant(p) push(p, pop(p)+1)
#define remonterAuPere(p) pop(p)
#define noeudTerminal(p,critereFin) (p->data[p->Sp].valeur == critereFin)
#define naPlusDeFrere(p, taille) (p->data[p->Sp]==taille)
#define rechercheTerminee(p) pileVide(p)


// Laby1 et Laby2  sont des variables GLOBALES : inutile de les transmettre dans les parametres des fonctions

//POUR LA QUESTION 1
float Laby1[MAX][MAX]={    // c est le tableau de la question 1
        {0.25,0.2,0.4,0.03,7.4,5,7.5,7.8,7,8.22},
        {0.4,	0.12,	0.44,	0.08,	7.41,	7.49,	7.54,	7.88,	7.9,	6.3},
        {0.55,	0.47,	0.09,	7.27,	7.3,	7.09,	7.01,	6.99,	7.91,	7.88},
        {0.64,	0.51,	0.14,	0.45,	7.25,	7.22,	7.21,	5.99,	7.99,	8},
        {2.81,	2.7,	2.9,	1.98,	4.8,	7.1,	7,	8.34,	7,	8.4},
        {2.9,	2.14,	3.24,	3.5,	2.4,	7.04,	7.03,	7.01,	8,	8.44},
        {3.12,	1.43,	3.1,	3.09,	6.88,	6.911,	6.09,	8.79,	8.601,	8.6},
        {3.201,	3.5,	3.49,	3.08,	6.8,	2.34,	8.1,	8.8,	8.501,	8.57},
        {0.15,	3.72,	3.11,	2.98,	6.79,	4.31,	8.8,	8.88,	9,	9.31},
        {5.3,	5.8,	6.4,	6.55,	6.58,	5.8,	9.8,	8.85,	8.99,	9.5}
};


//POUR LA QUESTION 2
float Laby2[MAX][MAX]=    // c est le tableau de la question 2
        {{0.25,	0.3	,0.4,	0.03,	7.5,	8,	7.9,	8.32,	8,	8.22},
         {0.41,	0.12,	0.44,	0.08,	7.41,	7.49,	7.54,	7.88,	7.9,	8.5},
         {0.75,	0.69,	0.09,	7.27,	7.3,	7.09,	7.01,	6.99,	7.91,	7.88},
         {0.84,	1,	0.14,	0.45,	7.25,	7.22,	9.2,	8.15,	7.99,	8},
         {2.81,	2.85,	2.9,	1.98,	4.8,	7.1,	7,	8.34,	9,	8.4},
         {2.9,	2.14,	3.24,	3.5,	2.4,	7.04,	7.03,	7.01,	8,	8.44},
         {3.12,	1.43,	3.1,	3.09,	6.88,	6.911,	6.09,	8.79,	8.601,	8.6},
         {3.201,	3.5,	3.77,	3.08,	6.8,	2.34,	8.87,	8.8,	8.501,	8.57},
         {0.15,	3.72,	3.11,	2.98,	6.79,	4.31,	9.4,	8.88,	9,	9.31},
         {6.2,	5.8,	6.4,	6.55,	6.58,	5.8,	9.8,	9.4,	9.09,	9.5}};




//structure de donnees


typedef struct
{
    float valeur;
    int ligne;
    int colonne;
    int nbPossibilites;
    float suite[4]; // changement du int en float
    /*
     * Exemple 1ere case :
     * La case 0 du tableau suite indique une piste au dessus de la case (-1 si il n'y en a pas)
     * La case 1 du tableau suite indique une piste à droite de la case (il n'y en a une : c'est 0.3)
     * La case 2 du tableau suite indique une piste en dessous de la case (il n'y en a une : c'est 0.41)
     * La case 3 du tableau suite indique une piste à gauche de la case (-1 si il n'y en a pas)
     */

} T_Case;

typedef T_Case T_Elt;

typedef struct
{
    T_Elt *data;
    int Sp;
} T_Pile;


//////////////////////////////////////
//fonctions de gestion de piles
//////////////////////////////////////
void afficherElement(T_Elt caseActuelle, T_Elt casePrecedente)
{
    if( caseActuelle.ligne == casePrecedente.ligne + 1 )
    {
        printf("BAS ");
    }
    else if ( caseActuelle.ligne == casePrecedente.ligne - 1 )
    {
        printf("HAUT ");
    }
    else if( caseActuelle.colonne == casePrecedente.colonne + 1 )
    {
        printf("DROITE ");
    }
    else if( caseActuelle.colonne == casePrecedente.colonne - 1)
    {
        printf("GAUCHE ");
    }
    else if( caseActuelle.valeur == casePrecedente.valeur )
    {
        printf("\n");
    }
    else
        printf("ERREUR ");
}

void init(T_Pile *p)
{
    p->data = (T_Elt *) malloc(sizeof(T_Elt));
    assert(p->data!=NULL);
    p->Sp = 0;
}

void push(T_Pile *p, T_Elt e)
{
    p->Sp++;
    p->data = (T_Elt *) realloc(p->data, (p->Sp+1)*sizeof(T_Elt));
    assert(p->data!=NULL);
    //Insertion de la valeur envoy�e en param�tre
    p->data[p->Sp]=e;
}

T_Elt pop(T_Pile *p)
{
    T_Elt e = {0.0,0,0};
    if(!pileVide(p))
    {
        e=p->data[p->Sp--];
        p->data = (T_Elt *) realloc(p->data, (p->Sp+1)*sizeof(T_Elt));
    }
    return e;
}

// Ici, un noeud non valide correspond à une pile dont la DERNIERE case a :
// 0 possibilité de continuer
// ET Sa valeur ne vaut pas 9.5
int noeudValide(T_Pile *p)
{
    int i;
    T_Elt caseActuelle = pop(p);
    push(p,caseActuelle);

    if( caseActuelle.nbPossibilites == 0 && caseActuelle.valeur != 9.5 )
        return 0;
    else
        return 1;

}




//Renvoie 0 si affichage impossible (car pile VIDE), 1 sinon
int afficher(T_Pile *p)
{
    if(pileVide(p))
    {
        return 0;
    }
    //La pile est non vide
    T_Pile temp;
    T_Elt eltActuel,eltPrecedent={0.25,0,0,2,{-1,0.3,0.41,-1}};;
    init(&temp);
    int i, max=p->Sp;
    for(i=1 ; i<=max ; i++)
    {

        eltActuel=pop(p);
        afficherElement(eltActuel,eltPrecedent);
        push(&temp, eltActuel);
        eltPrecedent = eltActuel;
    }

    for(i=1 ; i<=max ; i++)
    {
        push(p, pop(&temp));
    }

    return 1; //Car affichage r�ussi
}




//////////////////////////////////////
//code donn� pour la question 2 de la partie 2
//////////////////////////////////////

void trouverDirectionSuivante(T_Case caseActuelle,T_Direction * directionCaseSuivante)
{
    // On prend la première direction possible.
    for(int i=0; i<3;i++)
    {
        if( caseActuelle.suite[i] != -1) {
            *directionCaseSuivante = (T_Direction) i;
            return;
        }
    }
    // On est à la fin d'un chemin
    *directionCaseSuivante = FIN;
}

void trouverNbPossibilites(T_Case * caseActuelle)
{
    caseActuelle->nbPossibilites = 0;

    if( caseActuelle->ligne +1 < MAX && caseActuelle->valeur < Laby2[ caseActuelle->ligne+1 ][ caseActuelle->colonne] ) {
        caseActuelle->nbPossibilites++;
        caseActuelle->suite[BAS] = Laby2[ caseActuelle->ligne+1 ][ caseActuelle->colonne];
    }

    if( caseActuelle->colonne +1 < MAX && caseActuelle->valeur < Laby2[ caseActuelle->ligne ][ caseActuelle->colonne+1] ) {
        caseActuelle->nbPossibilites++;
        caseActuelle->suite[DROITE] = Laby2[ caseActuelle->ligne ][ caseActuelle->colonne+1];
    }
    if( caseActuelle->ligne -1 >= 0 && caseActuelle->valeur < Laby2[ caseActuelle->ligne - 1 ][ caseActuelle->colonne]) {
        caseActuelle->nbPossibilites++;
        caseActuelle->suite[HAUT] = Laby2[ caseActuelle->ligne - 1 ][ caseActuelle->colonne];
    }
    if ( caseActuelle->colonne - 1 >= 0 && caseActuelle->valeur < Laby2[ caseActuelle->ligne ][ caseActuelle->colonne - 1])
    {
        if( caseActuelle->nbPossibilites < 3) {
            caseActuelle->nbPossibilites++;
            caseActuelle->suite[GAUCHE] = Laby2[ caseActuelle->ligne ][ caseActuelle->colonne - 1];
        }
        else
            printf("ERREUR TROUVER NB POSSILITES");
    }


}


void question2()
{
    int affichage,testContinuerBoucle;
    T_Direction directionCaseSuivante = DROITE;
    T_Elt caseSuivante = {0.25,0,0,2,{-1,0.3,0.41,-1}};
    T_Elt caseActuelle = caseSuivante;
    T_Pile *p;
    p = (T_Pile *) malloc(sizeof(T_Pile));

    init(p);
    passerAuPremierFils(p,caseSuivante);
    do{
        testContinuerBoucle=1;
        while(noeudValide(p) && testContinuerBoucle==1)
        {
            if( noeudTerminal(p, Laby2[MAX-1][MAX-1] ) )
            // La profondeur de l'arbre est définie par le chemin menant à la fin du labyrinthe
            // elle est donc variable.
            {
                //Affichage de la solution
                afficher(p);
                testContinuerBoucle=0;
            }
            else
            {
                // Avant de passer au premier fils, on construit la case suivante.
                trouverDirectionSuivante(caseActuelle,&directionCaseSuivante);
                caseSuivante = caseActuelle;
                switch(directionCaseSuivante)
                {
                    case HAUT :
                        caseSuivante.ligne = caseActuelle.ligne -1;
                        break;

                    case DROITE :
                        caseSuivante.colonne = caseActuelle.colonne + 1;
                        break;

                    case BAS :
                        caseSuivante.ligne = caseActuelle.ligne + 1;
                        break;

                    case GAUCHE :
                        caseSuivante.colonne = caseActuelle.colonne - 1;
                        break;

                    default : printf("ERREUR SWITCH ");

                }
                caseSuivante.valeur = Laby2[ caseSuivante.ligne ][ caseSuivante.colonne];
                trouverNbPossibilites(&caseSuivante);

                passerAuPremierFils(p,caseSuivante);
            }
        }

        // Un noeud n'a plus de frère lorsque la case précédente ne contient plus de nouvelles possibilités
        while(!rechercheTerminee(p) && naPlusDeFrere(p, strlen(chaine)))
        {
            remonterAuPere(p);
        }
        if(!rechercheTerminee(p))
        {
            // Avant de passer au frère suivant
            passerAuFrereSuivant(p);
        }
    }while(!rechercheTerminee(p));

}


//////////////////////////////////////
//faire ici  votre code de la question 1 de la partie 2
//////////////////////////////////////

void question1()
{
    T_Pile solutionLaby;
    init(&solutionLaby);
    T_Case caseActuelle = {0.25,0,0};
    push(&solutionLaby,caseActuelle);

    int finPrematureeLaby =0;
    printf("DEPART :\n\n");
    do
    {

        // On recherche d'abord en bas, puis à droite, puis en haut, puis à gauche.
        if( caseActuelle.ligne +1 < MAX && caseActuelle.valeur < Laby1[ caseActuelle.ligne+1 ][ caseActuelle.colonne] ) {      // en bas ?
            caseActuelle.valeur = Laby1[caseActuelle.ligne +1][caseActuelle.colonne];
            caseActuelle.ligne++;
            printf("BAS ");
        }
        else if( caseActuelle.colonne +1 < MAX && caseActuelle.valeur < Laby1[ caseActuelle.ligne ][ caseActuelle.colonne+1] )   // à droite ?
        {
            caseActuelle.valeur = Laby1[caseActuelle.ligne ][caseActuelle.colonne +1];
            caseActuelle.colonne++;
            printf("DROITE ");
        }
        else if( caseActuelle.ligne -1 >= 0 && caseActuelle.valeur < Laby1[ caseActuelle.ligne - 1 ][ caseActuelle.colonne])    // en haut ?
        {
            caseActuelle.valeur = Laby1[ caseActuelle.ligne - 1 ][ caseActuelle.colonne];
            caseActuelle.ligne--;
            printf("HAUT ");
        }
        else if ( caseActuelle.colonne - 1 >= 0 && caseActuelle.valeur < Laby1[ caseActuelle.ligne ][ caseActuelle.colonne - 1]) // à gauche ?
        {
            caseActuelle.valeur = Laby1[caseActuelle.ligne ][caseActuelle.colonne -1];
            caseActuelle.colonne--;
            printf("GAUCHE ");
        }
        else
        {
            finPrematureeLaby = 1;
        }

        if( !finPrematureeLaby )
        {
            push(&solutionLaby,caseActuelle);
        }

    }while( finPrematureeLaby == 0 && caseActuelle.valeur != 9.5 );

    if( finPrematureeLaby )
        printf("\n\nPAS DE CHEMIN !! :(\n");
    else
        printf("\n\nVOUS ETES SORTI !! BRAVO !\n");


}

//////////////////////////////////////
//                    PP
//////////////////////////////////////

int main()
{

    //question1();
    question2();  //contient l algo des permutations

    return 0;
}






