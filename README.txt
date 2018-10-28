CTP SDA2 2013/2014
-------------------------

NOTES :
"Utilisation" <===> ajout d'une fonction issue de bibliothèque élaborée en TP.
"Ajout" <===> ajout d'une fonction pour une question en particulier.


PARTIE 1 : exo1.c
Question 1 - création de la liste à l'aide de la conjecture :
    Fait (versions récursive et itérative).

Question 2 - affichage de la liste, selon les exigences de l'énoncé :
    Fait (version itérative uniquement, récursivité impossible à priori).
    Utilisation des fonctions afficherListe(), getElementByPosition() et afficherElt().

Question 3 - nombre d'éléments et somme des éléments.
    Fait.
    Utilisation des fonctions récursives sommeEltsListe() et nbrEltsListe()

Question 4 - suppression des éléments pairs.
    Fait (version itérative uniquement, récursivité possible ?).
    Utilisation des fonctions récursives supprimerPremierElementListe(), supprimerElementListe() et estMembre().


PARTIE 2 : exo2.c
Question 1 - parcours d'un labyrinthe à chemin unique (avec ou sans solution)
    Fait.

Question 2 - parcours d'un labyrinthe à plusieurs chemins (avec ou sans solution)
    Non fini (impossible de faire le CTP en 2h).
    Ajout de la structure T_Direction.
    Ajout des fonctions trouverDirectionSuivante(), trouverNbPossibilites(), afficherElement().
    Modification de toutes les macrofonctions, sauf passerAuFrereSuivant() et naPlusDeFrere().
    Modification de la fonction afficher().
